#pragma once

#include <cstdint>
#include <string>
#include <memory>

namespace osiris {

// Core types
using BlockNumber = uint64_t;
using Timestamp = uint64_t;
using Difficulty = uint64_t;

// Consensus interface forward declaration
namespace consensus {
class IConsensus;
}

// Smart pointer aliases
template<typename T>
using UniquePtr = std::unique_ptr<T>;

} // namespace osiris
