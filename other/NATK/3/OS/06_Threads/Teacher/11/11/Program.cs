using System;
using System.Threading;

class Test
{
    static void Main()
    {
        Thread[] newThreads = new Thread[4];
        for(int i = 0; i < newThreads.Length; i++)
        {
//            newThreads[i] = new Thread(
//                new ThreadStart(Slot.SlotTest));
            Slot newObject = new Slot(i);
            newThreads[i] = new Thread(new ThreadStart(newObject.SlotTest));
            newThreads[i].Start();
        }
    }
}

class Slot
{
//    static Random randomGenerator;
//    static LocalDataStoreSlot localSlot;
    LocalDataStoreSlot localSlot;

//    static Slot()
//    {
//        randomGenerator = new Random();
//        localSlot = Thread.AllocateDataSlot();
//    }

    private int cnt;

    public Slot(int val)
    {
        this.cnt = val;
        localSlot = Thread.AllocateDataSlot();
    }

//    public static void SlotTest()
    public void SlotTest()
    {
        // Set different data in each thread's data slot.
//        Thread.SetData(localSlot, randomGenerator.Next(1, 200));
        Thread.SetData(localSlot, cnt);

        // Write the data from each thread's data slot.
        Console.WriteLine("Data in thread_{0}'s data slot: {1,3}", 
//            AppDomain.GetCurrentThreadId().ToString(),
	    Thread.CurrentThread.ManagedThreadId.ToString(),
            Thread.GetData(localSlot).ToString());

        // Allow other threads time to execute SetData to show
        // that a thread's data slot is unique to the thread.
        Thread.Sleep(1000);

        Console.WriteLine("Data in thread_{0}'s data slot: {1,3}", 
//            AppDomain.GetCurrentThreadId().ToString(),
	    Thread.CurrentThread.ManagedThreadId.ToString(),
            Thread.GetData(localSlot).ToString());
    }
}