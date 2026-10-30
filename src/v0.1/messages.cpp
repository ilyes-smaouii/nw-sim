#include "messages.hpp"

namespace common_ns {

Message::Message(std::size_t capacity) : m_payload() {
  m_payload.reserve(capacity);
}

const byte_t *Message::data() const { return m_payload.data(); }
byte_t *Message::data() { return m_payload.data(); }

std::size_t Message::size() const { return m_payload.size(); }

le_return_t Message::clear() {
  m_payload.clear();
  return RETURN_CODE::SUCCESS;
}

le_return_t Message::assign(const byte_t *data, std::size_t size) {
  // m_payload.clear(); // ?
  m_payload.assign(data, data + size);
  return RETURN_CODE::SUCCESS;
}

le_return_t Message::appendData(const byte_t *data, std::size_t size) {
  m_payload.insert(m_payload.end(), data, data + size);
  return RETURN_CODE::SUCCESS;
}

le_return_t Message::appendDataFromMsg(const Message &msg) {
  m_payload.insert(m_payload.end(), msg.data(), msg.data() + msg.size());
  return RETURN_CODE::SUCCESS;
}

std::string Message::toString() const {
  std::string result;
  for (const auto &byte : m_payload) {
    result += std::to_string(byte) + " ";
  }
  return result;
}

} // namespace common_ns
