#include "../include/scheduler.hpp"
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <ctime>
#include <mutex>
#include <vector>

const bool DEBUG = 0;
namespace sched {
/**
 * Sort jobs by effective priority
 * This is On^2? Better way to do This
 */
bool comp(Job &j1, Job &j2) { return j1.eff() > j2.eff(); };

void submit(Scheduler &s, Job &j) {
  scoped_lock lock(s.mu);
  const auto now = chrono::system_clock::now();

  j.id = s.next_job_id++;
  j.scheduled_at = chrono::system_clock::to_time_t(now);
  j.status = Status::WAITING;
  s.waiting.push_back(j);
  sort(s.waiting.begin(), s.waiting.end(), comp);

  if (DEBUG == true) {
    printf("[OK] Scheduled job %llu (%s)\n", j.id, j.label.c_str());
  }
};

void squeue(Scheduler &s) {
  scoped_lock lock(s.mu);
  printf("\033[H\033[J");
  printf("%-8s %-8s %-8s %-20s %-4s %-6s %-6s %-10s\n", "JOBID", "ST",
         "PRIORITY", "LABEL", "CPUs", "RAM", "WALTIME", "STARTED AT");

  for (const auto &j : s.waiting) {
    j.repr();
  }
  for (const auto &j : s.running) {
    j.repr();
  }
  for (const auto &j : s.finished) {
    j.repr();
  }
  fflush(stdout);
}

bool dispatch_one(Scheduler &s) {
  scoped_lock lock(s.mu);
  auto it = find_if(s.waiting.begin(), s.waiting.end(),
                    [&](const Job &j) { return fit(s.resources, j); });
  if (it == s.waiting.end()) {
    return false;
  }

  Job j = *it;
  s.waiting.erase(it);

  if (!allocate(s.resources, j)) {
    if (DEBUG == true) {
      printf("[ERR] Could not allocate for %s\n", j.label.c_str());
    }
    return false;
  }

  const auto now = chrono::system_clock::now();
  j.started_at = chrono::system_clock::to_time_t(now);
  j.running_at = j.started_at;
  j.status = Status::RUNNING;
  s.running.push_back(j);

  if (DEBUG == true) {
    printf("[OK] Dispatched job %llu (%s)\n", j.id, j.label.c_str());
  }
  return true;
}

void tick(Scheduler &s) {
  {
    scoped_lock lock(s.mu);
    if (s.stop) {
      return;
    }

    const auto now = chrono::system_clock::now();
    const auto now_ts = chrono::system_clock::to_time_t(now);

    size_t i = 0;
    while (i < s.running.size()) {
      Job &running_job = s.running[i];
      const bool finished =
          (now_ts - running_job.running_at) >= running_job.duration;
      if (!finished) {
        ++i;
        continue;
      }

      Job completed = running_job;
      release(s.resources, completed);
      completed.status = Status::COMPLETED;
      completed.completed_at = now_ts;
      s.finished.push_back(completed);
      s.running.erase(s.running.begin() + i);
    }
  }

  while (dispatch_one(s)) {
  }
}
} // namespace sched
