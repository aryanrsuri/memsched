#include "include/scheduler.hpp"
#include <cstdio>
using namespace sched;
using namespace std;
int main(void) {
  Scheduler s{.resources = {.total_ram_mb = 16000, .used_ram_mb = 0}};
  for (auto i = 1; i < 5; ++i) {
    char buffer[100];
    snprintf(buffer, size(buffer), "job-00%d", i);
    Job job = create_job(buffer, "echo 1", 10, 1024 * i, 30, 100);
    submit(s, job);
  }
  for (auto i = 5; i < 11; ++i) {
    char buffer[100];
    snprintf(buffer, size(buffer), "job-00%d", i);
    Job job = create_job(buffer, "echo 3", 3, 2048, 30, 100);
    submit(s, job);
  }
  char buffer[100];
  snprintf(buffer, size(buffer), "pass_scan_through");
  Job job = create_job(buffer, "echo 3", 3, 1024, 30, 100);
  submit(s, job);

  squeue(s);

  return 0;
}
