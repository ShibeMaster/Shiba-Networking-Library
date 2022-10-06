#pragma once
#include <exception>
#include <iostream>
#include "Network.h"

namespace ShibaNetLib {
	class NetworkException : public std::exception {
	public:
		const char* message;
		int error;
		NetworkException(const char* message, int error) {
			this->message = message;
			this->error = error;
			WSACleanup();
			Network::state = NetworkState::netstate_failed;
			std::cout << "Network Exception: " << message << " with error " << error << std::endl;
		}
	};
}