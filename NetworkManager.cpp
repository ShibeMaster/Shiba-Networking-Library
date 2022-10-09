#include "NetworkManager.h"
#include "NetworkException.h"

namespace ShibaNetLib {
	WSAData NetworkManager::wsaData;
	std::thread NetworkManager::networkThread;
	std::thread NetworkManager::incomingData;

	void NetworkManager::StartHost() {
		networkThread = std::thread([] { HostThread(); });
		incomingData = std::thread([] {	NetworkChannelManager::IncomingData(); });
	}
	void NetworkManager::HostThread() {
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
			throw NetworkException("Getting address info failed", addressResult);
			return;
		}

		listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (listenSocket == INVALID_SOCKET) {
			freeaddrinfo(result);
			throw NetworkException("Getting address info failed", WSAGetLastError());
			return;
		}

		int bindResult = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);
		if (bindResult == SOCKET_ERROR) {
			freeaddrinfo(result);
			closesocket(listenSocket);
			throw NetworkException("Bind failed", WSAGetLastError());
			return;
		}

		freeaddrinfo(result);

		int listenResult = listen(listenSocket, SOMAXCONN);
		if (listenResult == SOCKET_ERROR) {
			closesocket(listenSocket);
			throw NetworkException("Listen failed", WSAGetLastError());
			return;
		}

		Network::conn.connection = accept(listenSocket, NULL, NULL);
		if (Network::conn.connection == INVALID_SOCKET) {
			closesocket(listenSocket);
			throw NetworkException("Accept failed", WSAGetLastError());
			return;
		}

		closesocket(listenSocket);

		Network::conn.isServer = true;
		Network::clientCount = 1;
		Network::state = NetworkState::netstate_connected;
		Network::conn.Receive();
	}
	void NetworkManager::StartClient() {
		networkThread = std::thread([] { ClientThread(); });
		incomingData = std::thread([] {	NetworkChannelManager::IncomingData(); });
	}
	void NetworkManager::ClientThread() {
		struct addrinfo* result = NULL, * ptr = NULL, hints;

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		int addressResult = getaddrinfo("127.0.0.1", "10294", &hints, &result);
		if (addressResult != 0) {
			WSACleanup();
			throw NetworkException("Getting address info failed", addressResult);
			return;
		}

		for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
			Network::conn.connection = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
			if (Network::conn.connection == INVALID_SOCKET) {
				throw NetworkException("Failed to create a socket info failed", WSAGetLastError());
				return;
			}

			int connectResult = connect(Network::conn.connection, ptr->ai_addr, (int)ptr->ai_addrlen);
			if (connectResult == SOCKET_ERROR) {
				std::cout << "Connecting failed with error: " << WSAGetLastError() << std::endl;
				closesocket(Network::conn.connection);
				Network::conn.connection = INVALID_SOCKET;
				continue;
			}
			break;
		}

		freeaddrinfo(result);

		if (Network::conn.connection == INVALID_SOCKET) {
			WSACleanup();
			throw NetworkException("Unable to connect to the server", WSAGetLastError());
			return;
		}

		Network::conn.isServer = false;

		ClientConnectMessage connectMessage;
		connectMessage.channelid = 1;
		connectMessage.senderid = 0;
		connectMessage.response = false;

		Network::conn.Send(&connectMessage, sizeof(ClientConnectMessage));
		Network::conn.Receive();
	}
	void NetworkManager::Initialize() {
		int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (result != 0) {
			Network::state = NetworkState::netstate_failed;
			std::cout << "Startup Failed: " << result << std::endl;
		}
	}
}