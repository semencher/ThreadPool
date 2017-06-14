#pragma once

/*
Необходимо будет также написать класс-обертку очереди, тоже что-нибудь простенькое.

*/

#include <mutex>
#include <queue>

namespace pt
{
	namespace squeue
	{
		template<typename T> class SafeQueue
		{
		public:
			void push(const T &val) {
				std::lock_guard<std::mutex> lock(mutexQueue);
				queue.push(val);
			}
			bool pop(T &val) {
				std::lock_guard<std::mutex> lock(mutexQueue);
				if (queue.empty) {
					return false;
				}
				val = queue.front();
				queue.pop();
				return true;
			}
			bool empty() {
				std::lock_guard<std::mutex> lock(mutexQueue);
				return queue.empty();
			}
		private:
			std::queue<T> queue;
			std::mutex mutexQueue;
		};
	}

	template<typename T> class ThreadPool
	{

	};
}