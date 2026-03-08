#pragma once

#include "job.hpp"
#include "resources.hpp"
#include <deque>
#include <mutex>
#include <string>

namespace sched {
struct Scheduler {
  Resources resources;
  int next_job_id = 1;
  std::deque<Job> waiting;
  std::vector<Job> running;
  std::vector<Job> finished;
  std::mutex mu;
  // TODO: Add cv
  // std::condition_variable cv;
  bool stop = false;
};

/**
 * Create a job without an id
 */
Job create_job(const std::string &label, const std::string command,
               int cpus_req, int ram_req, int duration = 30, int priority = 40);

/**
 * Can we fit job given resources?
 */
bool fit(const Resources &r, const Job &j);

/**
 * Allocate resources for a given Job
 */
bool allocate(Resources &r, Job &j);

/**
 * Release resources from a given Job
 */
void release(Resources &r, Job &j);

/**
 * Submit job to the queue
 */
void submit(Scheduler &s, Job &j);

/**
 * Try to dispatch a scheduled job to a thread
 */
bool dispatch_one(Scheduler &s);

/**
 * One worker loop
 */
void tick(Scheduler &s);
}; // namespace sched
