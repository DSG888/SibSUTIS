using System;
using System.Threading;
class ThreadTest
{
    static bool done;    // Static fields are shared between all threads

    static void Main()
    {
//        new Thread(Go).Start();
//        Go();
        Thread t1 = new Thread(Go);
        Console.ReadLine();
    }

    static void Go(object o)
    {
        if (!done)
        {
            done = true;
            Console.WriteLine("Done");
            //            done = true;
        }
    }
}
