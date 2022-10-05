#pragma once
#include <stack>
#include "NetworkChannel.h"
namespace ShibaNetLib {
	class ChannelCreationQueue {
	public:
		static std::stack<NetworkChannel*> newChannelQueue;
	};
}