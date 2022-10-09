#pragma once
#include "Event.h"

namespace ShibaNetLib {
	class NetworkEvents {
	public:
		static Event<int> OnClientStart;
		static Event<int> OnServerStart;
		static Event<int> OnClientJoin;
		static Event<int> OnConnectionEnded;
	};
}