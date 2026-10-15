#pragma once

#include <cstddef>
#include <cstdint>

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

  NwProtocol(const address_t addr); // TO-DO : implement

  /*
    Checks whether addr is a valid NwProtocol address
   */
  static bool isValidAddress(address_t const &addr); // TO-DO : implement

  /*
    Send message msg to destination dest, identified by its NwProtocol address
   */
  cns::le_return_t sendMessage(cns::Message const &msg,
                               address_t dest); // TO-DO : implement

protected:
};

/*
  DLProtocol is some sort of datalink protocol : there's a limit on to how
  much data a single DLProtocol packet can carry.
 */
// TO-DO : implement
template<std::size_t MAX_PACKET_SZ>
class DLProtocol {
public:
  using address_t = std::uint32_t;
  static constexpr std::size_t MAX_PACKET_SIZE{MAX_PACKET_SZ};

  DLProtocol();

protected:
};

} // namespace protocols
