#include <iostream>
#include <string>

#include "threadpool.h"

int one(int val)
{
	std::cout << "One " + std::to_string(val) + "\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "One " + std::to_string(val) + "\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "One " + std::to_string(val) + "\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "One " + std::to_string(val) + "\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "One " + std::to_string(val) + "\n";
	return val;
}

int two(int val)
{
	std::cout << "Two " + std::to_string(val) + "\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Two " + std::to_string(val) + "\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Two " + std::to_string(val) + "\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Two " + std::to_string(val) + "\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Two " + std::to_string(val) + "\n";
	return val;
}

int three(int val)
{
	std::cout << "Three " + std::to_string(val) + "\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Three " + std::to_string(val) + "\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Three " + std::to_string(val) + "\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Three " + std::to_string(val) + "\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Three " + std::to_string(val) + "\n";
	return val;
}

int four(int val)
{
	std::cout << "Four " + std::to_string(val) + "\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Four " + std::to_string(val) + "\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Four " + std::to_string(val) + "\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Four " + std::to_string(val) + "\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Four " + std::to_string(val) + "\n";
	return val;
}

int five(int val)
{
	std::cout << "Five " + std::to_string(val) + "\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Five " + std::to_string(val) + "\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Five " + std::to_string(val) + "\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Five " + std::to_string(val) + "\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Five " + std::to_string(val) + "\n";
	return val;
}

int main(int argc, char* argv[])
{
	pt::ThreadPool threadPool(2);
	auto val1 = threadPool.addTask(one, 1);
	auto val2 = threadPool.addTask(two, 2);
	auto val3 = threadPool.addTask(three, 3);
	auto val4 = threadPool.addTask(four, 4);
	auto val5 = threadPool.addTask(five, 5);

	std::cout << std::to_string(val1.get()) + "\n";
	std::cout << std::to_string(val2.get()) + "\n";
	std::cout << std::to_string(val3.get()) + "\n";
	std::cout << std::to_string(val4.get()) + "\n";
	std::cout << std::to_string(val5.get()) + "\n";

	return 0;
}