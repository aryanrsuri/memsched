#include "../include/scheduler.hpp"
#include "../include/resources.hpp"
#include <chrono>
#include <cstdio>
#include <ctime>
#include <mutex>

namespace sched {

void submit(Scheduler &s, Job &j) {
  scoped_lock lock(s.mu);

  if (!allocate(s.resources, j)) {
    printf("[ERR] Could not allocate for %s\n", j.label.c_str());
    /*
    printf("[ERR] Could not allocate (%d CPUS, %d MB RAM) for %s "
           "\n\tScheduler "
           "view: %s "
           "(%d/%d "
           "MB RAM left)\n",
           j.cpus_req, j.ram_req, j.label.c_str(),
           s.resources.cpus.to_string().c_str(), s.resources.free_ram(),
           s.resources.total_ram_mb);
           */
    return;
  }
  j.id = s.next_job_id++;
  const auto now = chrono::system_clock::now();
  j.allocated_at = chrono::system_clock::to_time_t(now);
  printf("[OK] Allocated job %llu (%s)\n", j.id, j.label.c_str());
  /*
  printf("[INFO] Allocated (%lu CPUS, %d MB RAM) for (%llu) %s \n\tScheduler "
         "view: %s "
         "(%d/%d "
         "MB RAM left)\n",
         j.cpu_slots.size(), j.ram_req, j.id, j.label.c_str(),
         s.resources.cpus.to_string().c_str(), s.resources.free_ram(),
         s.resources.total_ram_mb);
         */
};

// bool dispatch_one(Scheduler &s) {}

} // namespace sched
