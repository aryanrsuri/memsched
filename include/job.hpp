#pragma once
#include "types.hpp"
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
  std::time_t created_at;
  std::time_t started_at;
  std::time_t scheduled_at;
  std::time_t running_at;
  std::time_t completed_at;
  std::time_t failed_at;
  int cpus_req;
  int ram_req;
  int duration;
  int priority;
  Status status = Status::WAITING;

  void repr() const {
    printf("%-8llu %-8d %-20s %-4d %-6d %-6d\n", id, priority, label.c_str(),
           cpus_req, ram_req, duration);
  }

  int eff() const { return priority * (created_at / 10000); }
};
} // namespace sched
