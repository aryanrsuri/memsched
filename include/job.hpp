#pragma once
#include <cstdint>
#include <cstdio>
#include <ctime>
#include <string>
#include <vector>
namespace sched {

/*
struct Task {
  uint64_t id;
  uint64_t index;
  std::string command;
  std::time_t started_at;
  std::time_t running_at;
  std::time_t completed_at;
  std::time_t failed_at;
};*/

struct Job {
  uint64_t id;
  std::string label;
  std::string command;
  // int current_task_index;
  // std::vector<Task> tasks;
  std::vector<int> cpu_slots;
  // std::string fingerprint;
  std::time_t started_at;
  std::time_t allocated_at;
  std::time_t scheduled_at;
  std::time_t running_at;
  std::time_t completed_at;
  std::time_t failed_at;
  int cpus_req;
  int ram_req;
  int duration;
  int priority;

  void repr() {
    printf("%llu\t%s\t(%d)\t%d\t%d\t%d\t%lu\n", id, label.c_str(), priority,
           cpus_req, ram_req, duration, allocated_at);
  };
};
} // namespace sched
