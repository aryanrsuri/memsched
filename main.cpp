#include "include/scheduler.hpp"
#include <cmath>
#include <cstdio>
using namespace sched;
using namespace std;
int main(void) {
  Scheduler s{.resources = {.total_ram_mb = 16000, .used_ram_mb = 0}};
  for (auto i = 1; i < 10; ++i) {
    char buffer[100];
    sprintf(buffer, "job-00%d", i);
    Job job = create_job(buffer, "echo 1", 10, 1024 * i, 30, 100);
    if (!allocate(s.resources, job)) {
      printf("Could not allocate (%d CPUS, %d MB RAM) for job=%s \n\tScheduler "
             "view: %s "
             "(%d/%d "
             "MB RAM left)\n",
             job.cpus_req, job.ram_req, job.label.c_str(),
             s.resources.cpus.to_string().c_str(), s.resources.total_ram_mb,
             s.resources.total_ram_mb + s.resources.used_ram_mb);

      return 1;
    }
    printf("Allocated (%lu CPUS, %d MB RAM) for job=%s \n\tScheduler view: %s "
           "(%d/%d "
           "MB RAM left)\n",
           job.cpu_slots.size(), job.ram_req, job.label.c_str(),
           s.resources.cpus.to_string().c_str(), s.resources.total_ram_mb,
           s.resources.total_ram_mb + s.resources.used_ram_mb);
    printf("\tCPU SLOTS=");
    for (auto v : job.cpu_slots) {
      printf("%d ", v);
    }
    printf("\n");
  }

  return 0;
}
