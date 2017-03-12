
using System;
using System.Threading;

public class Test
{
    public static void Main()
    {
//>My
        int workerThreads;
        int portThreads;

             ThreadPool.GetAvailableThreads(out workerThreads, 
                out portThreads);
            Console.WriteLine("\nAvailable worker threads: \t{0}" +
                "\nAvailable completion port threads: {1}\n",
                workerThreads, portThreads);

//<My
        int minWorker, minIOC;
        // Get the current settings.
        ThreadPool.GetMinThreads(out minWorker, out minIOC);
        // Change the minimum number of worker threads to four, but
        // keep the old setting for minimum asynchronous I/O 
        // completion threads.
        if (ThreadPool.SetMinThreads(4, minIOC))
        {
            // The minimum number of threads was set successfully.
//>My
	    Console.WriteLine("Set");	
             ThreadPool.GetAvailableThreads(out workerThreads, 
                out portThreads);
            Console.WriteLine("\nAvailable worker threads: \t{0}" +
                "\nAvailable completion port threads: {1}\n",
                workerThreads, portThreads);
//<My
        }
        else
        {
            // The minimum number of threads was not changed.
//>My
	    Console.WriteLine("Not set");
//<My	
        }
    }
}