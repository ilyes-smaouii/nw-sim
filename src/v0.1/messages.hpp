#pragma once

#include <cstddef>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

#include "common.hpp"

namespace common_ns {

// TO-DO : desc + implementation
class Message {
public:
  using payload_t = std::vector<byte_t>;

  /*
   * Constructs a new Message with the specified capacity.
   */
  Message(std::size_t capacity = 0);

  const byte_t *data() const;
  byte_t *data();

  /*
    Returns payload size
  */
  std::size_t size() const;

  /*
    Returns string of hex values contained in payload interpreted as binary
    stream, dividing it into blocks of four bits each
   */
  std::string toHexString() const; // TO-DO : implement
  /*
    Returns string contained in payload, assuming the binary data of the payload
    can be interpreted as a string
   */
  std::string toString() const; // TO-DO : implement

  /*
    Clears all payload data
   */
  le_return_t clear(); // TO-DO : implement

  /*
    Overwrites payload data
   */
  le_return_t assign(const byte_t *data,
                     std::size_t size); // TO-DO : implement

  template <typename T> T const &getDataAs(std::size_t offset) const {
    auto _size = size();
    if (offset >= _size) [[unlikely]] {
      throw std::runtime_error("Message::getDataAs() error : offset (" +
                               std::to_string(offset) + ") >= size (" +
                               std::to_string(_size) + ") !");
    }
    return *reinterpret_cast<T *>(m_payload.data() + offset);
  }

  // TO-DO : check proper overloading for appendData() (mixing templates and
  // non-templates --> ?)

  /*
    Appends data to the end of the payload
  */
  le_return_t appendData(const byte_t *data, std::size_t size);
  le_return_t appendDataFromMsg(const Message &msg);

  /*
    Appends data to the end of the payload
  */
  template <typename T>
  le_return_t appendData(const T &data, std::size_t size) {
    if (size > sizeof(T)) [[unlikely]] {
      return RETURN_CODE::FAILURE; // Size exceeds the size of the data type
    }
    const byte_t *byte_data = reinterpret_cast<const byte_t *>(&data);
    m_payload.insert(m_payload.end(), byte_data, byte_data + size);
    return RETURN_CODE::SUCCESS;
  }

  /*
    Appends data to the end of the payload
  */
  template <typename T> le_return_t appendData(const T &data) {
    return appendData(data, sizeof(T));
  }

protected:
  payload_t m_payload;
};

} // namespace common_ns