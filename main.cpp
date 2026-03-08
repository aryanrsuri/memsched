#include "include/scheduler.hpp"
#include <cstdio>
#include <iostream>
using namespace sched;
using namespace std;
int main(void) {
  Scheduler s{.resources = {.total_ram_mb = 160000, .used_ram_mb = 0}};
  Job job = create_job("job-001", "echo 1", 10, 1024, 30, 100);

  cout << job.label << " " << job.priority << '\n';
  cout << s.resources.cpus << '\n';

  return 0;
}
