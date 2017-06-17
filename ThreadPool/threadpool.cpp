#include "threadpool.h"

pt::ThreadPool::ThreadPool(size_t nThread) : threads_(nThread > 0 ? nThread : 2)
{
	freeThreads_ = static_cast<unsigned int>(threads_.size());
	stop_ = false;
}

pt::ThreadPool::~ThreadPool()
{
	stop_ = true;
	cvNewTask_.notify_all();

	size_t size = threads_.size();
	for (size_t i = 0; i < size; ++i) {
		if (threads_.at(i) && threads_.at(i)->joinable()) {
			threads_.at(i)->join();
		}
	}
}