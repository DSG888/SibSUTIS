#include <iostream>
#include <thread>

void hello()
{
	std::cout << "Hello, Multithreaded World!\n";
}

int main()
{
	// Создаем и запускаем новый поток выполнения
	std::thread mythread(hello);
	// Продолжаем вычисления в главном потоке
	// Ожидаем завершения потока mythread
	mythread.join();
	return 0;
}
