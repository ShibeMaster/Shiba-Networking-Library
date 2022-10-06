#include "Network.h"
namespace ShibaNetLib {
	int Network::clientCount = 0;
	NetworkState Network::state = NetworkState::netstate_offline;
	NetworkConnection Network::conn;
}