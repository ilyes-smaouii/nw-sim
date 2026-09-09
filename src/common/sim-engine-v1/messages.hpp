#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace common_ns {

class Message {
public:
  using payload_t = std::vector<uint8_t>;

  Message(std::size_t size);

  std::string toString() const;

protected:
  payload_t m_payload;
};

} // namespace common_ns