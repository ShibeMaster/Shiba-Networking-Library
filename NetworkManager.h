#pragma once
#include <WinSock2.h>
#include <iostream>
#include "NetworkConnection.h"
#include "ClientConnection.h"
#include "HostConnection.h"
#include "NetworkChannelManager.h"

namespace ShibaNetLib {
	class NetworkManager {
	public:
		static WSAData wsaData;
		static std::thread networkThread;
		static std::thread incomingData;

		static void StartHost();
		static void StartClient();
		static void Initialize();
	};
}