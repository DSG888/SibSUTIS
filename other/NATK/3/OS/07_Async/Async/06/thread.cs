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
  static private Object o = new Object();
  static void Main() 
  {
     new Thread (Go).Start();      // Call Go() on a new thread
     Go();                         // Call Go() on the main thread
//    ParameterizedThreadStart ts = new ParameterizedThreadStart(Go);
//    Thread t1 = new Thread(ts);
//    t1.Start(3);
//    Go(5);
  }
 
  static void Go()
  {
//   lock(o)
//   {
     // Declare and use a local variable - 'cycles'
     for (int cycles = 0; cycles < 5; cycles++)
     {
	Console.WriteLine("Working {0}", cycles);
	Thread.Sleep(1000);
     }
//   }
  }
}
/*
A separate copy of the cycles variable is created on each thread's memory
 stack, and so the output is, predictably, ten question marks.
*/