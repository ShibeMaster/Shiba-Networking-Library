#include "NetworkManager.h"

namespace ShibaNetLib {
	WSAData NetworkManager::wsaData;
	std::thread NetworkManager::networkThread;
	std::thread NetworkManager::incomingData;

	void NetworkManager::StartHost() {
		HostConnection host;
		NetworkStats::conn = &host;
		networkThread = std::thread([] { ((HostConnection*)NetworkStats::conn)->Host(); });
		incomingData = std::thread([] {	NetworkChannelManager::IncomingData(); });
	}
	void NetworkManager::StartClient() {
		ClientConnection client;
		NetworkStats::conn = &client;
		networkThread = std::thread([] { ((ClientConnection*)NetworkStats::conn)->Connect(); });
		incomingData = std::thread([] {	NetworkChannelManager::IncomingData(); });
	}
	void NetworkManager::Initialize() {
		int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (result != 0) {
			std::cout << "Startup Failed: " << result << std::endl;
		}
	}
}