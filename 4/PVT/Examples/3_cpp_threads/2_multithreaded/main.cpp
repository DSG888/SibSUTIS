#include <algorithm>
#include <iostream>
#include <thread>
#include <vector>

void handler(unsigned int id)
{
	std::cout << id << ": Hello, Multithreaded World!\n";
}

int main()
{
	unsigned int nthreads = std::thread::hardware_concurrency();
	std::cout << "Logical processors: " << nthreads << "\n";
	std::vector<std::thread> threads;
	for (size_t i = 0; i < nthreads; ++i)
	{
		threads.push_back(std::thread(handler, i));
	}
	std::for_each(threads.begin(), threads.end(),
	std::mem_fn(&std::thread::join));
	return 0;
}
