/*
Thread.IsBackground – свойство
Получает или задает значение, показывающее, является ли поток фоновым.
Значение true, если этот поток является или станет фоновым потоком; в противном случае — false.
Поток является либо фоновым, либо основным. Фоновые потоки идентичны основным за тем исключением, 
 что фоновые потоки не предотвращают завершение процесса. Поскольку все основные потоки, принадлежащие 
 процессу, завершились, общеязыковая среда выполнения завершает процесс. Все оставшиеся фоновые потоки 
 останавливаются и не завершаются.

В приведенном примере кода показана работа основных и фоновых процессов. Создаются основной и 
 фоновый процессы. Основной поток удерживает процесс до завершения его цикла while. После завершения 
 основного процесса он закрывается до того, как фоновый процесс завершит свой цикл while.
 */

using System;
using System.Threading;

class Test
{
    static void Main()
    {
        BackgroundTest shortTest = new BackgroundTest(10, " - основной поток");
        Thread foregroundThread =
            new Thread(new ThreadStart(shortTest.RunLoop));
        foregroundThread.Name = "ForegroundThread";

        BackgroundTest longTest = new BackgroundTest(50, " - фоновый поток");
        Thread backgroundThread =
            new Thread(new ThreadStart(longTest.RunLoop));
        backgroundThread.Name = "BackgroundThread";
        backgroundThread.IsBackground = true;

        foregroundThread.Start();
        backgroundThread.Start();
    }
}

class BackgroundTest
{
    int maxIterations;
    string msg;

    public BackgroundTest(int maxIterations, string message)
    {
        this.maxIterations = maxIterations;
        this.msg = message;
    }

    public void RunLoop()
    {
        String threadName = Thread.CurrentThread.Name;

        for (int i = 0; i < maxIterations; i++)
        {
            Console.WriteLine("{0} count{2}: {1}",
                threadName, i.ToString(), msg);
            Thread.Sleep(250);
        }
        Console.WriteLine("{0} finished counting(завершил счёт).", threadName);
        Console.ReadLine();
    }
}
