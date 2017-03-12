using System;
using System.Threading;
class ThreadSafe 
{
  static bool done;
  static readonly object locker = new object();
 
  static void Main()
  {
    new Thread (Go).Start();
    Go();
  }
 
  static void Go()
  {
      if (!done) { Console.WriteLine ("Done"); done = true; }
  }
}
