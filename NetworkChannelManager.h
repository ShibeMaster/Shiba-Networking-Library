#pragma once
#include "NetworkChannel.h"
#include <map>
#include <thread>
#include "ClientConnectionChannel.h"
#include "ChannelCreationQueue.h"

namespace ShibaNetLib {
	class NetworkChannelManager {
	public:
		static std::map<int, NetworkChannel*> channels;
		
		static void IncomingData() {


			ClientConnectionChannel clientConnection = ClientConnectionChannel(1);
			ClientConnectCallbackChannel clientConnectionCallback = ClientConnectCallbackChannel(2);


			AddNetworkChannel(&clientConnection);
			AddNetworkChannel(&clientConnectionCallback);

			while (true) {
				while (!ChannelCreationQueue::newChannelQueue.empty()) {
					NetworkChannel* channel = ChannelCreationQueue::newChannelQueue.top();
					if (channels.find(channel->channelIndex) != channels.end()) {
						if (channels[channel->channelIndex]->enabled) {
							std::cout << "a channel already exists on this index, try another!" << std::endl;
							continue;
						}
					}

					channels[channel->channelIndex] = channel;
					ChannelCreationQueue::newChannelQueue.pop();
				}
				while (!NetworkDataQueues::dataQueue.empty() && ChannelCreationQueue::newChannelQueue.empty()) {
					char* data = NetworkDataQueues::dataQueue.top();
					NetworkMessage* message = (NetworkMessage*)data;
					if (channels.find(message->channelid) == channels.end()) {
						std::cout << "received invalid channel id: " << message->channelid << std::endl;
						return;
					}
					channels[message->channelid]->Incoming(data);
					NetworkDataQueues::dataQueue.pop();
				}
			}
		}
		static void AddNetworkChannel(NetworkChannel* channel) {
			ChannelCreationQueue::newChannelQueue.push(channel);
		}
		static void RemoveNetworkChannel(int index) {
			if (channels.find(index) == channels.end()) {
				std::cout << "no channel already exists on this index" << std::endl;
				return;
			}

			channels[index]->enabled = false; // allows it to be replaced with new channels
		}
	};
}