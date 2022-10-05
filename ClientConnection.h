#pragma once
#include <iostream>
#include "NetworkConnection.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

namespace ShibaNetLib {
	class ClientConnection : public NetworkConnection {
	public:
		void Connect();
	};
}