#include "NetworkEvents.h"

namespace ShibaNetLib {
	Event<int> NetworkEvents::OnClientStart;
	Event<int> NetworkEvents::OnServerStart;
	Event<int> NetworkEvents::OnClientJoin;
	Event<int> NetworkEvents::OnConnectionEnded;
}