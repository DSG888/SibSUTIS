//(C) Корпорация Майкрософт (Microsoft Corporation). Все права защищены.

using System;
using System.Threading;

public class Worker
{
//    private int cnt;

//    public Worker(int count)
//    {
//	this.cnt = count;
//    }

    // Этот метод будет вызван при запуске потока.
    public void DoWork(object o)
    {
//      lock(this)
//      {
	int cnt = Convert.ToInt32(o);
//        while (!_shouldStop)
	for (int i=0; i<cnt; i++)
        {
//            Console.WriteLine("worker thread {0}: working...", Thread.CurrentThread.ManagedThreadId, i);
            Console.WriteLine("worker thread "+Thread.CurrentThread.Name+" : working..."+ i);
	    Thread.Sleep(1000);
        }
        Console.WriteLine("worker thread "+Thread.CurrentThread.Name+" : terminating gracefully.");
//      }
    }
//    public void RequestStop()
//    {
//        _shouldStop = true;
//    }
    // Ключевое слово "volatile" используется как подсказка компилятору, что указанный член данных
    // будет доступен множеству потоков.
//    private volatile bool _shouldStop;
}

public class WorkerThreadExample
{
    static void Main()
    {
        // Создание объекта потока. Это не приводит к запуску потока.
//        Worker workerObject1 = new Worker(4);
//        Thread workerThread1 = new Thread(workerObject1.DoWork);
//        workerThread1.Start();

	Worker w = new Worker();

	ParameterizedThreadStart starter = new ParameterizedThreadStart(w.DoWork);
	Thread first = new Thread(starter);
	Thread second = new Thread(starter);

	first.Name = "Work1";
	second.Name = "Work2";

	first.Start(4);
	second.Start(5);
             
//        Worker workerObject2 = new Worker(6);
//        Thread workerThread2 = new Thread(workerObject2.DoWork);

        // Запуск рабочего потока.
//        workerThread2.Start();
        Console.WriteLine("main thread: Starting worker thread...");

        // Цикл, пока рабочий поток активен.
//        while (!workerThread1.IsAlive);

        // Перевод главного потока в спящий режим в течение 1 миллисекунды, чтобы
        // дать рабочему процессу возможность выполнить часть работы:
//        Thread.Sleep(1);

        // Запрос на самостоятельную остановку рабочего процесса:
//        workerObject1.RequestStop();
//        workerObject2.RequestStop();

        // Применение метода Join для блокирования текущего потока, 
        // пока не будет завершен поток объекта.
//        workerThread1.Join();
//        workerThread2.Join();
                first.Join();
                second.Join();
        Console.WriteLine("main thread: Worker thread has terminated.");
    }
}