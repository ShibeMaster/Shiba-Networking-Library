#include "ClientConnection.h"
#include "ClientConnectionChannel.h"
namespace ShibaNetLib {

	void ClientConnection::Connect() {
		struct addrinfo* result = NULL, * ptr = NULL, hints;		

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		int addressResult = getaddrinfo("127.0.0.1", "10294", &hints, &result);
		if (addressResult != 0) {
			std::cout << "Getting address info failed with error: " << addressResult << std::endl;
			WSACleanup();
			return;
		}

		for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
			connection = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
			if (connection == INVALID_SOCKET) {
				std::cout << "Failed to create a socket with error " << WSAGetLastError() << std::endl;
				WSACleanup();
				return;
			}

			int connectResult = connect(connection, ptr->ai_addr, (int)ptr->ai_addrlen);
			if (connectResult == SOCKET_ERROR) {
				std::cout << "Connecting failed with error: " << WSAGetLastError() << std::endl;
				closesocket(connection);
				connection = INVALID_SOCKET;
				continue;
			}
			break;
		}

		freeaddrinfo(result);

		if (connection == INVALID_SOCKET) {
			std::cout << "Unable to connect to the server with error: " << WSAGetLastError() << std::endl;
			WSACleanup();
			return;
		}

		isServer = false;
		
		ClientConnectMessage connectMessage;
		connectMessage.channelid = 1;
		connectMessage.senderid = 0;

		Send(&connectMessage, sizeof(ClientConnectMessage));
		Receive();
	}
}