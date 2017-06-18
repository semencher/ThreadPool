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
			void clear() {
				std::lock_guard<std::mutex> lock(mutexQueue_);
				while (!queue_.empty()) {
					queue_.pop();
				}
			}
		private:
			std::queue<T> queue_;
			std::mutex mutexQueue_;
		};
	}

	class ThreadPool
	{
	public:
		ThreadPool(const ThreadPool &) = delete;
		ThreadPool(ThreadPool &&) = delete;
		ThreadPool & operator=(const ThreadPool &) = delete;
		ThreadPool & operator=(ThreadPool &&) = delete;

		ThreadPool(size_t nThread = 2);
		~ThreadPool();

		template<typename F, typename... Args> auto addTask(F &&f, Args&&... args) -> std::future<decltype(f(args...))>
		{
			auto packTask = std::make_shared<std::packaged_task<decltype(f(args...))()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
			int nFreeThread = -1;
			{
				// Проверяем есть ли не разу не использованные потоки.
				std::lock_guard<std::mutex> lock(freeThreadsMutex_);
				if (freeThreads_) {
					waitingThreads_--;
					nFreeThread = --freeThreads_;
				}
			}
			if (nFreeThread != -1) {
				std::function<void()> fw([this, packTask]() {
					(*packTask)();
					std::function<void()> waitingTask;
					while (!this->stop_) {
						if (this->tasks_.pop(waitingTask)) {
							waitingTask();
						}
						else {
							{
								std::unique_lock<std::mutex> lock(this->cvMutex_);
								this->waitingThreads_++;
								this->cvNewTask_.wait(lock, [this]() { return this->stop_ || !this->tasks_.empty();	});
								this->waitingThreads_--;
							}
							if (!this->stop_ && this->tasks_.pop(waitingTask)) {
								waitingTask();
							}
						}
					}
				});
				threads_.at(nFreeThread) = std::make_unique<std::thread>(fw);
			}
			else {
				std::function<void()> fw([packTask]() {(*packTask)(); });
				tasks_.push(fw);
				cvNewTask_.notify_one();
			}
			return packTask->get_future();
		}

		size_t size() { return threads_.size(); }
		void clearTaskQueue() { tasks_.clear(); }
		std::function<void()> popTask();
		size_t idleThreads() { return waitingThreads_; }

	private:
		std::vector<std::unique_ptr<std::thread>> threads_;
		squeue::SafeQueue<std::function<void()>> tasks_;

		// Потоки которые еще не созданы.
		unsigned int freeThreads_;
		std::mutex freeThreadsMutex_;
		// Сумма не созданных и простаивающих потоков.
		unsigned int waitingThreads_;

		// Флаг для сигнализации потокам что надо останвливаться.
		bool stop_;
		// Условная переменная для сигнализации о появлении новых задач.
		std::condition_variable cvNewTask_;
		std::mutex cvMutex_;
	};
}