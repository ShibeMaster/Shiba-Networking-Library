#pragma once
namespace ShibaNetLib {
	struct NetworkMessage {
		int channelid;
		int senderid;
	};

	// since c++ doesn't have reflection and can't iterate through each of the fields in a class, we'll need to manually make a serialize method for each networkmessage
}