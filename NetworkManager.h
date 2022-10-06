#pragma once
#include <ws2tcpip.h>
#include <WinSock2.h>
#include <iostream>
#include "NetworkConnection.h"
#include "NetworkChannelManager.h"

#pragma comment(lib, "Ws2_32.lib")

namespace ShibaNetLib {
	class NetworkManager {
	public:
		static WSAData wsaData;
		static std::thread networkThread;
		static std::thread incomingData;

		static void StartHost();
		static void HostThread();
		static void StartClient();
		static void ClientThread();
		static void Initialize();
	};
}