#include <iostream>

#include "threadpool.h"

void one()
{
	std::cout << "One\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "One\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "One\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "One\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "One\n";
}

void two()
{
	std::cout << "Two\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Two\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Two\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Two\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Two\n";
}

void three()
{
	std::cout << "Three\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Three\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Three\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Three\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Three\n";
}

void four()
{
	std::cout << "Four\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Four\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Four\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Four\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Four\n";
}

void five()
{
	std::cout << "Five\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Five\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Five\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Five\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Five\n";
}

int main(int argc, char* argv[])
{
	pt::ThreadPool threadPool(2);
	threadPool.addTask(one);
	threadPool.addTask(two);
	threadPool.addTask(three);

	return 0;
}