#pragma once
#include <vector>
#include <functional>

namespace ShibaNetLib {
	template<class T>
	class Event {
	public:
		std::vector<std::function<void(T)>> subscribers;

		void operator+=(std::function<void(T)> rhs) {
			subscribers.push_back(rhs);
		}
		void Invoke(T value) {
			for (std::function<void(T)> action : subscribers) {
				action(value);
			}
		}
	};
}