#pragma once

#include <cstddef>
#include <cstdint>

namespace common_ns {

using byte_t = std::uint8_t;
using le_return_t = std::int8_t;
using entity_id_t = std::uint32_t;

enum RETURN_CODE : le_return_t {
  SUCCESS = 0,
  FAILURE = -1,
};

constexpr std::size_t MAX_EVENT_QUEUE_SIZE{1024};

} // namespace common_ns