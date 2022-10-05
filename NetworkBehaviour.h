#pragma once
#include "NetworkConnection.h"
#include "NetworkStats.h"

namespace ShibaNetLib {
	class NetworkBehaviour {
	public:
		unsigned int netId;
		NetworkConnection* conn = NetworkStats::conn;
		bool isServer = conn->isServer;
	};
}