#include "NetworkStats.h"
namespace ShibaNetLib {
	int NetworkStats::clientCount = 0;
	NetworkState NetworkStats::state = NetworkState::netstate_offline;
	NetworkConnection* NetworkStats::conn = nullptr;
}