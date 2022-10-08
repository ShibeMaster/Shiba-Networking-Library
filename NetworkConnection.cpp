#include "NetworkConnection.h"

namespace ShibaNetLib {
	void NetworkConnection::Send(NetworkMessage* message, int size) {
		int result = send(connection, (char*)message, size, 0);
		if (result == SOCKET_ERROR) {
			std::cout << "failed to send with error: " << WSAGetLastError() << std::endl;
			closesocket(connection);
			WSACleanup();
			return;
		}
		else if(showDebugMessages) {
			std::cout << "bytes sent: " << result << std::endl;
		}
	}
	void NetworkConnection::Receive() {
		int receivingResult = 1;
		while (receivingResult > 0) {
			int result = recv(connection, buffer, DEFAULT_BUFFER_LENGTH, 0);
			if (result > 0) {
				if(showDebugMessages)
					std::cout << "bytes received: " << result << std::endl;
				NetworkDataQueues::dataQueue.push_front(buffer);
			}
		}
		if (showDebugMessages)
			std::cout << "connection ended" << std::endl;

	}
}