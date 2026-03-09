#include "../include/scheduler.hpp"
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <ctime>
#include <mutex>

namespace sched {
/**
 * Sort jobs be effective priority
 * This is On^2? Better way to do This
 */
bool comp(Job &j1, Job &j2) { return j1.eff() > j2.eff(); };

void submit(Scheduler &s, Job &j) {
  scoped_lock lock(s.mu);

  j.id = s.next_job_id++;
  s.waiting.push_back(j);
  sort(s.waiting.begin(), s.waiting.end(), comp);
  const auto now = chrono::system_clock::now();
  j.scheduled_at = chrono::system_clock::to_time_t(now);
  printf("[OK] Scheduled job %llu (%s)\n", j.id, j.label.c_str());
};

void squeue(Scheduler &s) {
  printf("%-8s %-8s %-20s %-4s %-6s %-6s\n", "JOBID", "PRIORITY", "LABEL",
         "CPUs", "RAM", "WALTIME");

  for (const auto &j : s.waiting) {
    j.repr();
  }
  for (const auto &j : s.running) {
    j.repr();
  }
  for (const auto &j : s.finished) {
    j.repr();
  }
}

/*
bool dispatch_one(Scheduler &s) {
  const auto j = s.waiting.front();
  if (!allocate(s.resources, s.waiting.front())) {
    printf("[ERR] Could not allocate for %s\n", j.label.c_str());
    return false;
  }
  return true;
}
*/
} // namespace sched
