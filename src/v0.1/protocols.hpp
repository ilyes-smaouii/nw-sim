#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>

#include "common.hpp"
#include "messages.hpp"

/*
  The idea, here, is to define two protocols, NwProtocol and DLProtocol
  that are very simple versions of a network and datalink protocols.
  NwProtocol takes care of routing data through a network of NwProtocol
  entities, and DLProtcol has to dis-assemble and re-assemble messages which it
  can send to other DLProtocol entities, as it has the constraint of a maximum
  packet size
  */

namespace protocols {

namespace cns = common_ns;

/*
  NwProtocol is some sort of IP-like protocol : each entity has an address,
  and messages get routed through other NwProtocol entities to reach their
  destination. Other than that, no particular constraints.
 */
// TO-DO : implement
class NwProtocol {
public:
  using address_t = std::uint32_t;
  using return_t = cns::le_return_t;
  using entity_id_t = cns::entity_id_t;

  struct MessageHeader {
    // TO-DO : clarify header content
    address_t sender_addr;
    address_t receiver_addr;
  };

  NwProtocol(const address_t addr); // TO-DO : implement

  return_t setDLEntity(entity_id_t entity_id);

  /*
    Checks whether addr is a valid NwProtocol address
   */
  static bool isValidAddress(address_t const &addr);

  /*
    Returns the gateway address for the given destination address. For v0.1,
    I'll just assume all networds are of type A.B.C.D/16, and that the gateway
    is always A.B.0.1
  */
  address_t getGateway(address_t const &dest) const;

  /*
    Send message msg to destination dest, identified by its NwProtocol address
   */
  std::shared_ptr<cns::Message>
  sendMessage(std::shared_ptr<cns::Message> msg_ptr,
              address_t const &dest); // TO-DO : implement

  /*
    Process received message
    Message payload data should contain sender and receiver address, so no need
    to specify an address in the function call
   */
  std::shared_ptr<cns::Message>
  receiveMessage(std::shared_ptr<cns::Message> msg_ptr); // TO-DO : implement

protected:
  address_t m_addr{};
  entity_id_t m_dl_entity_id{};
};

/*
  DLProtocol is some sort of datalink protocol : there's a limit on to how
  much data a single DLProtocol packet can carry.
 */
// TO-DO : implement
template <std::size_t MAX_PACKET_SZ> class DLProtocol {
public:
  using address_t = std::uint32_t;
  using return_t = cns::le_return_t;

  static constexpr std::size_t MAX_PACKET_SIZE{MAX_PACKET_SZ};

  DLProtocol();

  /*
    Checks whether addr is a valid DLProtocol address
   */
  static bool isValidAddress(address_t const &addr); // TO-DO : implement

  /*
    Send message msg to destination dest, identified by its DLProtocol address
   */
  return_t sendMessage(std::shared_ptr<cns::Message> msg,
                       address_t const &dest); // TO-DO : implement

  /*
    Process received message
    Message payload data should contain sender and receiver address, so no need
    to specify an address in the function call
    Message received here is actually only a fragment, which the DLProtocol
    entity can use to re-assemble a message detined for the higher layer
    NwProtocol entity
  */
  return_t
  receiveMessage(std::shared_ptr<cns::Message> msg); // TO-DO : implement

protected:
  address_t m_addr{};
};

} // namespace protocols
