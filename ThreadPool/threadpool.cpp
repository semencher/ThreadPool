#include "threadpool.h"

pt::ThreadPool::ThreadPool(size_t nThread) : threads_(nThread > 0 ? nThread : 2)
{
	// TODO: ChernyshovSV - ����� ����� ���������� ���������� ������� � ����� ������� ��� ��������������.
	// TODO: ChernyshovSV - ������ ����� �� ��� ������� ����� ������������ �������.
	size_t size = threads_.size();
	for (size_t i = 0; i < size; ++i) {
		freeThreads_.push(static_cast<unsigned int>(i));
	}
}

pt::ThreadPool::~ThreadPool()
{
	// TODO: ChernyshovSV - ���������� �������� ����� clear ��� ������� � �������� ��� �����.
	// TODO: ChernyshovSV - ���������� ����� �� ������� ����� � ������� ������� ��� ������, ����� ����� ��������.
	std::vector<bool> flags(threads_.size(), true);
	unsigned int nThread;
	while (freeThreads_.pop(nThread)) {
		flags.at(nThread) = false;
	}
	size_t size = threads_.size();
	for (size_t i = 0; i < size; ++i) {
		// TODO: ChernyshovSV - ����� ��������� joinable, �� ����� ������� �����. ������.
		if (flags.at(i) && threads_.at(i)->joinable()) {
			threads_.at(i)->join();
		}
	}
}