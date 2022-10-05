#pragma once
#include <stack>

namespace ShibaNetLib {
	class NetworkDataQueues {
	public:
		static std::stack<char*> dataQueue;
	};
}