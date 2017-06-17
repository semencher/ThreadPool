#pragma once

#include <mutex>
#include <queue>
#include <future>

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

		template<typename F, typename... Args> auto addTask(F &&f, Args&&... args) -> std::future<decltype(f(args...))>
		{
			auto packTask = std::make_shared<std::packaged_task<decltype(f(args...))()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
			std::function<void()> fw([this, packTask]() {
				(*packTask)();
				std::function<void()> fn;
				// Здесь возникает проблема с необходимостью запрета добавления номера в очередь свободных потоков при прикращении
				// цикла, его можно решить если избавиться от безопасной очереди и управлять ей вручную.
				// TODO: ChernyshovSV - решить проблему описанную выше.
				while (this->tasks_.pop(fn)) {
					fn();
				}
			});
			unsigned int nFreeThread;
			if (freeThreads_.pop(nFreeThread)) {
				if (threads_.at(nFreeThread) && threads_.at(nFreeThread)->joinable()) {
					threads_.at(nFreeThread)->join();
				}
				// TODO: ChernyshovSV - здесь создается поток, проверить, может можно как то устанавливать в старый.
				threads_.at(nFreeThread) = std::make_unique<std::thread>(fw);
			}
			else {
				tasks_.push(fw);
			}
			return packTask->get_future();
		}

		~ThreadPool();

	private:
		std::vector<std::unique_ptr<std::thread>> threads_;
		squeue::SafeQueue<std::function<void()>> tasks_;
		squeue::SafeQueue<unsigned int> freeThreads_;
	};
}