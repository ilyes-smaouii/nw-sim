#pragma once

#include <cstdint>

namespace common_ns {

using byte_t = std::uint8_t;
using le_return_t = std::int8_t;
using entity_id_t = std::uint32_t;

enum RETURN_CODE : le_return_t {
  SUCCESS = 0,
  FAILURE = -1,
};

} // namespace common_ns