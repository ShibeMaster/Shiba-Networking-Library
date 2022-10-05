#pragma once
#include "NetworkChannel.h"
#include "NetworkMessage.h"
#include "NetworkStats.h"

namespace ShibaNetLib {

	struct ClientConnectMessage : NetworkMessage {};

	struct ClientConnectCallbackMessage : NetworkMessage {
		int newNetId;
		int clientCount;
	};

	class ClientConnectionChannel : public NetworkChannel {
	public:
		using NetworkChannel::NetworkChannel;
		void Incoming(char* newData) {
			if (isServer) {
				ClientConnectMessage* message = (ClientConnectMessage*)newData;

				ClientConnectCallbackMessage callbackMessage;
				callbackMessage.channelid = 2;
				callbackMessage.senderid = conn->netId;
				callbackMessage.newNetId = ++NetworkStats::clientCount;
				callbackMessage.clientCount = NetworkStats::clientCount;

				conn->Send(&callbackMessage, sizeof(ClientConnectCallbackMessage));
			}
		}
	};
	class ClientConnectCallbackChannel : public NetworkChannel {
		using NetworkChannel::NetworkChannel;
		void Incoming(char* newData) {
			ClientConnectCallbackMessage* message = (ClientConnectCallbackMessage*)newData;
			conn->netId = message->newNetId;
			NetworkStats::clientCount = message->clientCount;
			std::cout << "successfully joined server - id: " << message->newNetId << std::endl;;
			NetworkStats::state = NetworkState::netstate_connected;
		}
	};
}