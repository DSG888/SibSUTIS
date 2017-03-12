//(C) Корпорация Майкрософт (Microsoft Corporation). Все права защищены.

using System;
using System.Threading;

public class Worker
{
    // Этот метод будет вызван при запуске потока.
    public void DoWork()
    {
        while (!_shouldStop)
        {
            Console.WriteLine("worker thread: working...");
        }
        Console.WriteLine("worker thread: terminating gracefully.");
    }
    public void RequestStop()
    {
        _shouldStop = true;
    }
    // Ключевое слово "volatile" используется как подсказка компилятору, что указанный член данных
    // будет доступен множеству потоков.
    private volatile bool _shouldStop;
}

public class WorkerThreadExample
{
    static void Main()
    {
        // Создание объекта потока. Это не приводит к запуску потока.
        Worker workerObject = new Worker();
        Thread workerThread = new Thread(workerObject.DoWork);

        // Запуск рабочего потока.
        workerThread.Start();
        Console.WriteLine("main thread: Starting worker thread...");

        // Цикл, пока рабочий поток активен.
        while (!workerThread.IsAlive);

        // Перевод главного потока в спящий режим в течение 1 миллисекунды, чтобы
        // дать рабочему процессу возможность выполнить часть работы:
        Thread.Sleep(1);

        // Запрос на самостоятельную остановку рабочего процесса:
        workerObject.RequestStop();

        // Применение метода Join для блокирования текущего потока, 
        // пока не будет завершен поток объекта.
        workerThread.Join();
        Console.WriteLine("main thread: Worker thread has terminated.");
    }
}