#pragma once

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
				std::lock_guard<std::mutex> lock(mutexQueue_);
				queue_.push(val);
			}
			bool pop(T &val) {
				std::lock_guard<std::mutex> lock(mutexQueue_);
				if (queue_.empty()) {
					return false;
				}
				val = queue_.front();
				queue_.pop();
				return true;
			}
			bool empty() {
				std::lock_guard<std::mutex> lock(mutexQueue_);
				return queue_.empty();
			}
		private:
			std::queue<T> queue_;
			std::mutex mutexQueue_;
		};
	}

	class ThreadPool
	{
		ThreadPool(const ThreadPool &) = delete;
		ThreadPool(ThreadPool &&) = delete;
		ThreadPool & operator=(const ThreadPool &) = delete;
		ThreadPool & operator=(ThreadPool &&) = delete;

	public:
		ThreadPool(size_t nThread = 2);

		template<typename F> void addTask(F &&f)
		{
			unsigned int nFreeThread;
			if (freeThreads_.pop(nFreeThread)) {
				threads_.at(nFreeThread) = std::make_unique<std::thread>(f);
			}
			else {
				tasks_.push(f);
			}
		}

		~ThreadPool();

	private:
		std::vector<std::unique_ptr<std::thread>> threads_;
		squeue::SafeQueue<std::function<void()>> tasks_;
		squeue::SafeQueue<unsigned int> freeThreads_;
	};
}