#pragma once

#include <cstddef>
namespace sched {
constexpr std::size_t MAX_CPUS = 64;
enum class Status { WAITING, RUNNING, COMPLETED, FAILED };
}; // namespace sched
