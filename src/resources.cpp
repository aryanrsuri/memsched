#include "../include/resources.hpp"
#include "../include/job.hpp"
#include <cstdio>
#include <iostream>

using namespace std;
namespace sched {
Job create_job(const string &label, const string command, int cpus_req,
               int ram_req, int duration = 30, int priority = 40) {
  return Job{
      .label = label,
      .command = command,
      .cpus_req = cpus_req,
      .ram_req = ram_req,
      .duration = duration,
      .priority = priority,
  };
};

bool fit(const Resources &r, const Job &j) {
  if (j.cpus_req <= int(r.cpus.count()) && j.ram_req <= r.free_ram())
    return true;
  return false;
}

bool allocate(Resources &r, Job &j) {
  if (!fit(r, j)) {
    return false;
  }
  r.used_ram_mb += j.ram_req;
  int i = 0;
  while (j.cpu_slots.size() < j.cpus_req) {
    if (r.cpus[i] == 1) {
      r.cpus.flip(i);
      j.cpu_slots.push_back(i);
    };
    ++i;
  };

  if (j.cpu_slots.size() != j.cpus_req)
    return false;

  return true;
}

bool release(Resources &r, Job &j) {
  r.used_ram_mb -= j.ram_req;

  for (int i : j.cpu_slots) {
    r.cpus.flip(i);
  };

  return true;
}

} // namespace sched
