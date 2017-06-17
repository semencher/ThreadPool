#include "threadpool.h"

pt::ThreadPool::ThreadPool(size_t nThread) : threads_(nThread > 0 ? nThread : 2)
{
	// TODO: ChernyshovSV - такой метод заполнени€ необходимо сделать в самой очереди дл€ быстродействи€.
	// TODO: ChernyshovSV - узнать можно ли это сделать через библиотечные функции.
	size_t size = threads_.size();
	for (size_t i = 0; i < size; ++i) {
		freeThreads_.push(static_cast<unsigned int>(i));
	}
}

pt::ThreadPool::~ThreadPool()
{
	// TODO: ChernyshovSV - необходимо добавить метод clear дл€ очереди и вызывать его здесь.
	// TODO: ChernyshovSV - необходимо оп€ть же сделать метод у очереди который это делает, иначе будет медленно.
	std::vector<bool> flags(threads_.size(), true);
	unsigned int nThread;
	while (freeThreads_.pop(nThread)) {
		flags.at(nThread) = false;
	}
	size_t size = threads_.size();
	for (size_t i = 0; i < size; ++i) {
		// TODO: ChernyshovSV - везде провер€ют joinable, не очень пон€тно зачем. ”знать.
		if (flags.at(i) && threads_.at(i)->joinable()) {
			threads_.at(i)->join();
		}
	}
}