#pragma once
#include <ws2tcpip.h>
#include <thread>
#include <iostream>
#include <WinSock2.h>
#include "NetworkMessage.h"
#include "NetworkDataQueues.h"

#define DEFAULT_BUFFER_LENGTH 512

namespace ShibaNetLib {
	class NetworkConnection {
	public:
		SOCKET connection;
		unsigned int netId;
		bool isServer;
		char buffer[DEFAULT_BUFFER_LENGTH];

		void Send(NetworkMessage* message, int size = DEFAULT_BUFFER_LENGTH);
		void Receive();
	};
}