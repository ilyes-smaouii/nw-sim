#pragma once

// #include "common.hpp"
// #include "messages.hpp"
#include "protocols.hpp"
#include "common.hpp"
#include "messages.hpp"
#include <memory>

namespace protocols {

namespace cns = common_ns;

NwProtocol::NwProtocol(const address_t addr) : m_addr{addr} {
  // TO-DO : implement
}

NwProtocol::return_t NwProtocol::setDLEntity(entity_id_t entity_id) {
  m_dl_entity_id = entity_id;
  return cns::RETURN_CODE::SUCCESS;
}

bool NwProtocol::isValidAddress(address_t const &addr) {
  return (addr & 0xFFFF0000) > 0;
}

NwProtocol::address_t NwProtocol::getGateway(address_t const &dest) const {
  return (dest & 0xFFFF0000) | 0x00000001;
}

std::shared_ptr<cns::Message>
NwProtocol::sendMessage(std::shared_ptr<cns::Message> msg_ptr,
                        address_t const &dest) {
  // TO-DO : finish implementation (metadata about DL entity, etc.)

  address_t const &next_hop_addr = getGateway(dest);
  std::size_t res_size = sizeof(MessageHeader) + msg_ptr->size();
  auto res_msg_ptr = std::make_shared<cns::Message>(res_size);
  res_msg_ptr->appendData(MessageHeader{m_addr, next_hop_addr});
  res_msg_ptr->appendMessageData(
      *msg_ptr); // append original message payload data
  return res_msg_ptr;
}

std::shared_ptr<cns::Message>
NwProtocol::receiveMessage(std::shared_ptr<cns::Message> msg_ptr) {
  // TO-DO : implement
  // sender addr | receiver addr | payload data
  const MessageHeader *header =
      reinterpret_cast<MessageHeader *>(msg_ptr->data());
  address_t const &sender_addr = header->sender_addr;
  address_t const &receiver_addr = header->receiver_addr;
  if (receiver_addr != m_addr) [[unlikely]] { // TO-DO : unlikely ?
    address_t const next_hop = getGateway(receiver_addr);
    // Message not intended for this entity, drop it
    return {};
  }
  return {};
}

} // namespace protocols