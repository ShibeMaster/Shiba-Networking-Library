#include "ChannelCreationQueue.h"
namespace ShibaNetLib {
	std::stack<NetworkChannel*> ChannelCreationQueue::newChannelQueue;
}
