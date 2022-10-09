#pragma once
#include <ws2tcpip.h>
#include <thread>
#include <iostream>
#include <WinSock2.h>
#include "NetworkMessage.h"
#include "NetworkDataQueues.h"
#include <deque>
#include "NetworkEvents.h"
#include <thread>

#define DEFAULT_BUFFER_LENGTH 8192

namespace ShibaNetLib {
	class NetworkConnection {
	public:
		SOCKET connection;
		unsigned int netId;
		bool isServer;
		char buffer[DEFAULT_BUFFER_LENGTH];
		bool showDebugMessages = false;

		void Send(NetworkMessage* message, int size = DEFAULT_BUFFER_LENGTH);
		void SendThread();
		void Receive();
	};
}