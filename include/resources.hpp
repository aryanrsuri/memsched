#pragma once
#include "types.hpp"
#include <bitset>
#include <ctime>

using namespace std;
namespace sched {
struct Resources {
  int total_ram_mb;
  int used_ram_mb;
  // 1 means free CPU
  bitset<MAX_CPUS> cpus = cpus.set();

  int free_ram() const { return total_ram_mb - used_ram_mb; }
};
} // namespace sched
