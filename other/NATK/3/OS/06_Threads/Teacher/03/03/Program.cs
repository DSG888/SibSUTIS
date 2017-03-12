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
        BackgroundTest shortTest = new BackgroundTest(10, " - основной поток",
			null);
        Thread foregroundThread =
            new Thread(new ThreadStart(shortTest.RunLoop));
        foregroundThread.Name = "ForegroundThread";

        BackgroundTest longTest = new BackgroundTest(50, " - фоновый поток",
			new ExampleCallback(ResultCallback));
        Thread backgroundThread =
            new Thread(new ThreadStart(longTest.RunLoop));
        backgroundThread.Name = "BackgroundThread";
        backgroundThread.IsBackground = true;

        foregroundThread.Start();
        backgroundThread.Start();
    }
    // The callback method must match the signature of the
    // callback delegate.
    //
    public static void ResultCallback(int lineCount) 
    {
        Console.WriteLine(
            "Independent task returned value {0}.", lineCount);
    }
}

// Delegate that defines the signature for the callback method.
//
public delegate void ExampleCallback(int lineCount);

class BackgroundTest
{
    int maxIterations;
    string msg;

    private ExampleCallback callback;

    public BackgroundTest(int maxIterations, string message, 
		ExampleCallback callbackDelegate)
    {
        this.maxIterations = maxIterations;
        this.msg = message;
        callback = callbackDelegate;
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
        if (callback != null)
            callback(maxIterations);
        else
            Console.WriteLine("No callback");
        Console.WriteLine("{0} finished counting(завершил счёт).", threadName);
        Console.ReadLine();
    }
}
