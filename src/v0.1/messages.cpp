#include "messages.hpp"

namespace common_ns {

Message::Message(std::size_t size) : m_payload(size) {}

std::string Message::toString() const {
  std::string result;
  for (const auto &byte : m_payload) {
    result += std::to_string(byte) + " ";
  }
  return result;
}

} // namespace common_ns
