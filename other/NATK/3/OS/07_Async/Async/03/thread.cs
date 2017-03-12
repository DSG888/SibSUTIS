/*
C# supports parallel execution of code through multithreading. A thread is
 an independent execution path, able to run simultaneously with other threads.
A C# client program (Console, WPF, or Windows Forms) starts in a single
 thread created automatically by the CLR and operating system (the "main"
 thread), and is made multithreaded by creating additional threads. Here's
 a simple example and its output:
All examples assume the following namespaces are imported:
*/
using System;
using System.Threading;
class ThreadTest
{
  static void Main()
  {
    Thread t = new Thread (Work);          // Kick off a new thread
    t.Start();                               // running WriteY()
    Work();
    // Simultaneously, do something on the main thread.
//    for (int i = 0; i < 1000; i++) Console.Write ("x");
  }
 
  static void Work()
  {
    for (int i = 0; i < 5; i++)
    {
	 Console.WriteLine ("Working {0} - {1}", Thread.CurrentThread.ManagedThreadId, i);
	 Thread.Sleep(1000);
    }
  }
}
/*
The main thread creates a new thread ton which it runs a method that
 repeatedly prints the character "y".Simultaneously, the main thread
 repeatedly prints the character "x":
*/