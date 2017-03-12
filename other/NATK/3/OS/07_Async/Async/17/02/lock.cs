using System;
using System.Threading;
class ThreadSafe 
{
  static bool done = false;
  static readonly object locker = new object();
 
  static void Main()
  {
//    new Thread (Go).Start();
//    Go();
    ParameterizedThreadStart ts = new ParameterizedThreadStart(Go);
    Thread t1 = new Thread(ts);
    t1.Name = "Work ";
    t1.Start(1);
    Thread.CurrentThread.Name = "Main ";
    Go(2);
  }
 
  static void Go(object obj)
//  static void Go()
  {
//    lock(locker)
//    {
      if (!done) 
      { 
	int i = (int)obj;
//	Console.WriteLine ("Current thread {0} - Done", i); 
	Console.WriteLine ("Current thread "+Thread.CurrentThread.Name+ " Done "+ i); 
	done = true; 
      }
//    }
  }

}
