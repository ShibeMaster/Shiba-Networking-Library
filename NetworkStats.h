#pragma once
#include "NetworkConnection.h"
namespace ShibaNetLib {
	enum NetworkState {
		netstate_offline,
		netstate_connected,
		netstate_failed
	};
	class NetworkStats {
	public:
		static int clientCount;
		static NetworkState state;
		static NetworkConnection* conn;
	};
}