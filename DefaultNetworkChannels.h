#pragma once
#include "NetworkChannel.h"
#include "NetworkMessage.h"
#include "Network.h"

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
			std::cout << conn->isServer << std::endl;
			if (conn->isServer) {
				ClientConnectMessage* message = (ClientConnectMessage*)newData;

				ClientConnectCallbackMessage callbackMessage;
				callbackMessage.channelid = 2;
				callbackMessage.senderid = conn->netId;
				callbackMessage.newNetId = Network::clientCount++;
				callbackMessage.clientCount = Network::clientCount;

				conn->Send(&callbackMessage, sizeof(ClientConnectCallbackMessage));
			}
		}
	};
	class ClientConnectCallbackChannel : public NetworkChannel {
		using NetworkChannel::NetworkChannel;
		void Incoming(char* newData) {
			ClientConnectCallbackMessage* message = (ClientConnectCallbackMessage*)newData;
			conn->netId = message->newNetId;
			Network::clientCount = message->clientCount;
			std::cout << "successfully joined server - id: " << message->newNetId << std::endl;;
			Network::state = NetworkState::netstate_connected;
		}
	};
}