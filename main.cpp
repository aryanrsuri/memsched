#include "include/scheduler.hpp"
#include <cstdio>
#include <iostream>
using namespace sched;
using namespace std;
int main(void) {
  Scheduler s{.resources = {.total_ram_mb = 160000, .used_ram_mb = 0}};
  Job job = create_job("job-001", "echo 1", 10, 1024, 30, 100);

  auto t = s.resources.cpus << 10;
  cout << t << '\n';
  printf("Can we fit %s (%d CPUS , %d MB RAM) given the resources of %lu CPUS "
         "and %d MB "
         "RAM? %d\n",
         job.label.c_str(), job.cpus_req, job.ram_req, s.resources.cpus.count(),
         s.resources.total_ram_mb, fit(s.resources, job));

  return 0;
}
