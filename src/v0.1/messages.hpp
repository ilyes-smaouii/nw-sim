#pragma once

#include "common.hpp"

#include <cstddef>
#include <string>
#include <vector>

namespace common_ns {

class Message {
public:
  using payload_t = std::vector<byte_t>;

  /*
   * Constructs a new Message with the specified size.
   */
  Message(std::size_t size);

  std::string toString() const;

protected:
  payload_t m_payload;
};

} // namespace common_ns