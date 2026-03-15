#pragma once

#include <cstddef>
#include <map>
#include <string>
using namespace std;
namespace sched {
constexpr std::size_t MAX_CPUS = 64;
enum Status { WAITING, RUNNING, COMPLETED, FAILED };
const map<Status, string> m = {{WAITING, "WAITING"},
                               {RUNNING, "RUNNING"},
                               {COMPLETED, "COMPLETED"},
                               {FAILED, "FAILED"}};
}; // namespace sched
