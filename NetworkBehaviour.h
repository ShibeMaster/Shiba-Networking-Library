#pragma once
#include "NetworkConnection.h"
#include "Network.h"

namespace ShibaNetLib {
	class NetworkBehaviour {
	public:
		unsigned int netId;
		NetworkConnection* conn = &Network::conn;
	};
}