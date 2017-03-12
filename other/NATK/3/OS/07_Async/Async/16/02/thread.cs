using System;
using System.Threading;
class ThreadTest 
{
  static bool done;    // Static fields are shared between all threads
  static public Object thisLock = new Object();
 
  static void Main()
  {
//    new Thread (Go).Start();
    ParameterizedThreadStart ts = new ParameterizedThreadStart(Go);
    Thread t1 = new Thread(ts);
    t1.Name = "Work ";
    t1.Start(1);
    
    Thread.CurrentThread.Name = "Main ";
    Go(2);
  }
 
  static void Go(object o)
  {
//    lock(thisLock)
//    {
	int num = (int)o;
//	if (!done) { done = true; Console.WriteLine ("Done {0}", num); }
	if (!done)
        { 
	   Console.WriteLine ("Done "+Thread.CurrentThread.Name+ num); 
	   done = true; 
	}
//    }
  }
}
