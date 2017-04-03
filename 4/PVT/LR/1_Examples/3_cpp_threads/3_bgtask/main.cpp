#include <iostream>
#include <thread>
#include <vector>


class background_task
{
public:
	void operator()() const
	{
		std::cout << "Hello, Multithreaded World!\n";
	}
};

int main()
{
	background_task bgtask;
	std::thread mythread(bgtask);

	std::vector<std::thread> myVector;
	for (int i = 0; i < 8; ++i)
	{
	//	myVector.insert(bgtask);	//TODO
	}





	// Инициализировали поток объектом-функцией
	// Продолжаем вычисления в главном потоке
	mythread.join();
	return 0;
}
