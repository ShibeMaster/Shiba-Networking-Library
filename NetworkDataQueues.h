#pragma once
#include <deque>

namespace ShibaNetLib {
	class NetworkDataQueues {
	public:
		static std::deque<char*> dataQueue;
	};
}