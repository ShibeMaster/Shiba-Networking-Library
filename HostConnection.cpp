#include "HostConnection.h"

namespace ShibaNetLib {
	void HostConnection::Host() {
		SOCKET listenSocket = INVALID_SOCKET;
		
		struct addrinfo* result = NULL;
		struct addrinfo hints;

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;

		int addressResult = getaddrinfo(NULL, "10294", &hints, &result);
		if (addressResult != 0) {
			std::cout << "Getting address info failed with error: " << addressResult << std::endl;
			WSACleanup();
			return;
		}

		listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (listenSocket == INVALID_SOCKET) {
			std::cout << "Socket failed with error: " << WSAGetLastError() << std::endl;
			freeaddrinfo(result);
			WSACleanup();
			return;
		}

		int bindResult = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);
		if (bindResult == SOCKET_ERROR) {
			std::cout << "Bind failed with error: " << WSAGetLastError() << std::endl;
			freeaddrinfo(result);
			closesocket(listenSocket);
			WSACleanup();
			return;
		}

		freeaddrinfo(result);

		int listenResult = listen(listenSocket, SOMAXCONN);
		if (listenResult == SOCKET_ERROR) {
			std::cout << "Listen failed with error: " << WSAGetLastError() << std::endl;
			closesocket(listenSocket);
			WSACleanup();
			return;
		}

		connection = accept(listenSocket, NULL, NULL);
		if (connection == INVALID_SOCKET) {
			std::cout << "Accept failed with error: " << WSAGetLastError() << std::endl;
			closesocket(listenSocket);
			WSACleanup();
			return;
		}

		closesocket(listenSocket);

		isServer = true;
		NetworkStats::clientCount = 1;
		NetworkStats::state = NetworkState::netstate_connected;
		Receive();
	}
}