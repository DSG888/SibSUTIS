/*
В приведенном примере кода демонстрируется использование Join при ожидании завершения потока.
*/
using System;
using System.Threading;

class IsThreadPool
{
    static void Main()
    {
        AutoResetEvent autoEvent = new AutoResetEvent(false);

//        Thread regularThread = 
//            new Thread(new ThreadStart(ThreadMethod));

	Work w = new Work(10);

//        Thread regularThread = 
//            new Thread(new ThreadStart(ThreadMethod));
        Thread regularThread = 
            new Thread(new ThreadStart(w.DoWork));

        regularThread.Start();
        ThreadPool.QueueUserWorkItem(new WaitCallback(WorkMethod), 
            autoEvent);

        // Wait for foreground thread to end.
        regularThread.Join();

        // Wait for background thread to end.
        autoEvent.WaitOne();
        Console.ReadLine();
    }

    static void ThreadMethod()
    {
        Console.WriteLine("ThreadOne, executing ThreadMethod, " +
            "is {0}from the thread pool.", 
            Thread.CurrentThread.IsThreadPoolThread ? "" : "not ");
    }

    static void WorkMethod(object stateInfo)
    {
        Console.WriteLine("ThreadTwo, executing WorkMethod, " +
            "is {0}from the thread pool.", 
            Thread.CurrentThread.IsThreadPoolThread ? "" : "not ");

        // Signal that this thread is finished.
        ((AutoResetEvent)stateInfo).Set();
    }
}

public class Work
{
    private int cnt;

    public Work(int count)
    {
	this.cnt = count;
    }

    public void DoWork()
    {
        Console.WriteLine("ThreadOne, executing DoWork method with param {1}, " +
            "is {0}from the thread pool.", 
            Thread.CurrentThread.IsThreadPoolThread ? "" : "not ", cnt);
    }
}