/*
В следующем примере кода показано, как использовать имя потока.
*/
using System;
using System.Threading;

class Name
{
    static void Main()
    {
        //Thread.CurrentThread.Name = "Thread_Name";
        // Check whether the thread has previously been named
        // to avoid a possible InvalidOperationException.
        if(Thread.CurrentThread.Name == null)
        {
            Thread.CurrentThread.Name = "MainThread";
            Console.WriteLine("Thread name is(имя потока) {0}", Thread.CurrentThread.Name);
        }
        else
        {
//            Console.WriteLine("Unable to name a previously " + 
//                "named thread .");
            Console.WriteLine("The thread has previously been named(Потоку ранее было дано имя) " +
                 Thread.CurrentThread.Name);
        }
        Console.ReadLine();
    }
}
