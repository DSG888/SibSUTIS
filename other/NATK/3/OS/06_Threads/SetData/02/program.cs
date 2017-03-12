using System;
using System.Threading;

class Test
{
    static void Main()
    {
        Thread[] newThreads = new Thread[4];
        for(int i = 0; i < newThreads.Length; i++)
        {
            newThreads[i] = 
                new Thread(new ThreadStart(Slot.SlotTest));
            newThreads[i].Start();
        }
    }
}

class Slot
{
    static Random randomGenerator = new Random();

    public static void SlotTest()
    {
        // Set different data in each thread's data slot.
        Thread.SetData(
            Thread.GetNamedDataSlot("Random"), 
            randomGenerator.Next(1, 200));

        // Write the data from each thread's data slot.
        Console.WriteLine("Data in thread_{0}'s data slot: {1,3}", 
//            AppDomain.GetCurrentThreadId().ToString(),
            Thread.CurrentThread.ManagedThreadId.ToString(),
            Thread.GetData(
            Thread.GetNamedDataSlot("Random")).ToString());

        // Allow other threads time to execute SetData to show
        // that a thread's data slot is unique to the thread.
        Thread.Sleep(1000);

        Console.WriteLine("Data in thread_{0}'s data slot is still: {1,3}", 
//            AppDomain.GetCurrentThreadId().ToString(),
            Thread.CurrentThread.ManagedThreadId.ToString(),
            Thread.GetData(
            Thread.GetNamedDataSlot("Random")).ToString());

        // Allow time for other threads to show their data,
        // then demonstrate that any code a thread executes
        // has access to the thread's named data slot.        
        Thread.Sleep(1000);

        Other o = new Other();
        o.ShowSlotData();
    }
}

public class Other
{
    public void ShowSlotData()
    {
        // This method has no access to the data in the Slot
        // class, but when executed by a thread it can obtain
        // the thread's data from a named slot.
        Console.WriteLine("Other code displays data in thread_{0}'s data slot: {1,3}", 
//            AppDomain.GetCurrentThreadId().ToString(), 
            Thread.CurrentThread.ManagedThreadId.ToString(),
            Thread.GetData( 
            Thread.GetNamedDataSlot("Random")).ToString());
    }
}