#pragma once
#include "NetworkBehaviour.h"

namespace ShibaNetLib {
	class NetworkChannel : public NetworkBehaviour {
	public:
		int channelIndex;
		bool enabled = true;

		NetworkChannel(int index) {
			channelIndex = index;
		}
		virtual void Incoming(char* buffer){}
		virtual void IncomingReply(char* buffer){}
	};
}