using System;
using System.Threading;
/*
The CLR assigns each thread its own memory stack so that local variables
 are kept separate. In the next example, we define a method with a local
 variable, then call the method simultaneously on the main thread and a
 newly created thread:
*/
class ThreadTest
{
  static void Main() 
  {
//     new Thread (Go).Start();      // Call Go() on a new thread
//     Go();                         // Call Go() on the main thread
    ParameterizedThreadStart ts = new ParameterizedThreadStart(Go);
    Thread t1 = new Thread(ts);
    t1.Start(3);
    Go(5);
  }
 
//static void Go()
  static void Go(object obj)
  {
  // Declare and use a local variable - 'cycles'
  //  for (int cycles = 0; cycles < 5; cycles++) Console.Write ('?');
     int cnt = (int)obj;
     for (int i=0; i<cnt; i++)
     {
//	Console.WriteLine("Working "+Thread.CurrentThread.ManagedThreadId.ToString()+" - ", Convert.ToString(i));
	Console.WriteLine("Working {0} - {1}",Thread.CurrentThread.ManagedThreadId.ToString(), i);
	Thread.Sleep(1000);
     }
  }
}
/*
A separate copy of the cycles variable is created on each thread's memory
 stack, and so the output is, predictably, ten question marks.
*/