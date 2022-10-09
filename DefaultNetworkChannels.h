#pragma once
#include "NetworkChannel.h"
#include "NetworkMessage.h"
#include "Network.h"

namespace ShibaNetLib {

	struct ClientConnectMessage : NetworkMessage {};

	struct ClientConnectReplyMessage : NetworkMessage {
		int newNetId;
		int clientCount;
	};

	class ClientConnectionChannel : public NetworkChannel {
	public:
		using NetworkChannel::NetworkChannel;
		void Incoming(char* buffer) {
			if (conn->isServer) {
				ClientConnectMessage* message = (ClientConnectMessage*)buffer;

				ClientConnectReplyMessage callbackMessage;
				callbackMessage.channelid = 1;
				callbackMessage.senderid = conn->netId;
				callbackMessage.response = true;
				callbackMessage.newNetId = Network::clientCount++;
				callbackMessage.clientCount = Network::clientCount;

				std::cout << "New client connected to server - id: " << callbackMessage.newNetId << std::endl;;
				conn->Send(&callbackMessage, sizeof(ClientConnectReplyMessage));
			}
		}
		void IncomingReply(char* buffer) {
			ClientConnectReplyMessage* message = (ClientConnectReplyMessage*)buffer;
			conn->netId = message->newNetId;
			Network::clientCount = message->clientCount;
			std::cout << "Successfully joined server - id: " << message->newNetId << std::endl;;
			Network::state = NetworkState::netstate_connected;
		}
	};
}