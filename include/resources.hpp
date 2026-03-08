#pragma once
#include "types.hpp"
#include <bitset>
#include <ctime>

namespace sched {
struct Resources {
  int total_ram_mb;
  int used_ram_mb;
  std::bitset<MAX_CPUS> cpus;
};
} // namespace sched
