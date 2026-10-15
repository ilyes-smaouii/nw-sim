#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "common.hpp"

namespace common_ns {

// TO-DO : desc + implementation
class Message {
public:
  using payload_t = std::vector<byte_t>;

  /*
   * Constructs a new Message with the specified size.
   */
  Message(std::size_t size);

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

protected:
  payload_t m_payload;
};

} // namespace common_ns