using System;
using System.Threading;

public class WorkParam
{
    //Закрытый атрибут
    private int cnt;

    // Delegate used to execute the callback method when the
    // task is complete.
    private ExampleCallback callback;


    //Пользовательский конструктор
    public WorkParam(int val, ExampleCallback callbackDelegate)
    {
        this.cnt = val;
        this.callback = callbackDelegate;
    }

    // This method will be called when the thread is started.
    public void DoWork()
    {
        while (!_shouldStop)
        {
            Console.WriteLine("worker thread: working...{0}", cnt++);
        }
        if (callback != null)
            callback(500);
        else
            Console.WriteLine("No callback");
        Console.WriteLine("worker thread: terminating gracefully.");
    }
    public void RequestStop()
    {
        _shouldStop = true;
    }
    // Volatile is used as hint to the compiler that this data
    // member will be accessed by multiple threads.
    private volatile bool _shouldStop;
}

// Delegate that defines the signature for the callback method.
//
public delegate void ExampleCallback(int value);

// Entry point for the example.
//

public class WorkerThreadExample
{
    static void Main()
    {
        // Create the thread object. This does not start the thread.
        WorkParam workerObject = new WorkParam(100, new ExampleCallback(ResultCallback));
        Thread workerThread = new Thread(workerObject.DoWork);

        // Start the worker thread.
        workerThread.Start();
        Console.WriteLine("main thread: Starting worker thread...");

        // Loop until worker thread activates.
        while (!workerThread.IsAlive);

        // Put the main thread to sleep for 1 millisecond to
        // allow the worker thread to do some work:
        Thread.Sleep(1);

        // Request that the worker thread stop itself:
        workerObject.RequestStop();

        // Use the Join method to block the current thread 
        // until the object's thread terminates.
        workerThread.Join();
        Console.WriteLine("main thread: Worker thread has terminated.");
        Console.ReadLine();
    }

    // The callback method must match the signature of the
    // callback delegate.
    //
    public static void ResultCallback(int value) 
    {
        Console.WriteLine(
            "main thread: Worker thread returned value {0}.", value);
    }

}
/*
Ниже приведены выходные данные:

main thread: starting worker thread...
worker thread: working...100
worker thread: working...101
worker thread: working...102
worker thread: working...103
worker thread: working...104
worker thread: working...105
worker thread: working...106
worker thread: working...107
worker thread: working...108
worker thread: working...109
worker thread: working...110
 ...
main thread: Worker thread returned value 500
worker thread: terminating gracefully...
main thread: worker thread has terminated
*/
