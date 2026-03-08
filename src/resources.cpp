#include "../include/resources.hpp"
#include "../include/job.hpp"

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
} // namespace sched
