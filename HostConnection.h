#pragma once
#include <iostream>
#include "NetworkStats.h"
#include "NetworkConnection.h"

#pragma comment (lib, "Ws2_32.lib")

namespace ShibaNetLib {
	class HostConnection : public NetworkConnection {
	public:
		void Host();
	};
}