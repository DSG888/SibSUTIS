using System;
using System.Threading;

class Test
{
    static void Main()
    {
        Thread newThread = new Thread(new ThreadStart(ThreadMethod));
        newThread.Start();
    }

    static void ThreadMethod()
    {
        Console.WriteLine(
            "Thread {0} started in {1} with AppDomainID = {2}.",
//Old method            AppDomain.GetCurrentThreadId().ToString(),
	    Thread.CurrentThread.ManagedThreadId, 
            Thread.GetDomain().FriendlyName, 
            Thread.GetDomainID().ToString());
    }
}