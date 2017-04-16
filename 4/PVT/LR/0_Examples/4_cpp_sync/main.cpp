#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <cstdlib>
#include <queue>
#include <chrono>

template <typename T> class threadsafe_queue
{
	public:
	void put(T val)
	{
		std::lock_guard<std::mutex> lock(mutex);
		queue.push(val);
		cond.notify_one();
		// в очереди появились данные
	}
	T take()
	{
		std::unique_lock<std::mutex> ulock(mutex);
		//while (queue.empty())
		//
		cond.wait(ulock);
		cond.wait(ulock, [this]() { return !queue.empty(); });
		T val = queue.front();
		queue.pop();
		return val;
	}
	private:
		std::queue<T> queue;
		std::mutex mutex;
		std::condition_variable cond;
};

template <typename T>
void producer(int id, threadsafe_queue<T>& queue)
{
	for (size_t i = 0; i < 1000000; ++i)
	{
		queue.put(id + 100 + i);
//		std::cout << "Producer " << id << " put " << id + 100 + i << "\n";
	}
}

template <typename T>
void consumer(int id, threadsafe_queue<T>& queue)
{
	for (size_t i = 0; i < 10; ++i)
	{
		T val = queue.take();
//		std::cout << "Consumer " << id << " take " << val << "\n";
	}
}



int main()
{
	threadsafe_queue<int> queue;
	int nconsumers = 4;
	std::vector<std::thread> consumers;
	for (int i = 0; i < nconsumers; ++i)
		consumers.push_back(std::thread(consumer<int>, i, std::ref(queue)));
	int nproducers = 4;
	std::vector<std::thread> producers;
	for (int i = 0; i < nproducers; ++i)
		producers.push_back(std::thread(producer<int>, i, std::ref(queue)));
	for (std::thread& t : consumers)
		t.join();
	for (std::thread& t : producers)
		t.join();
	return 0;
}
