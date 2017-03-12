/*
The locking is applied internally in the same way. You might expect that
 the following example will yield the same result as the last:
*/
using System;
using System.Threading;
using System.Runtime.Remoting.Contexts;

//[Synchronization]
public class AutoLock //: ContextBoundObject
{
  public void Demo()
  {
    Console.Write ("Start...");
    Thread.Sleep (1000);
    Console.WriteLine ("end");
  }
 
  public void Test()
  {
    new Thread (Demo).Start();
    new Thread (Demo).Start();
    new Thread (Demo).Start();
//    Console.ReadLine();
  }
 
  public static void Main()
  {
//    Console.WriteLine ("Push Enter");
    new AutoLock().Test();
  }
}
/*
(Notice that we've sneaked in a Console.ReadLinestatement). Because only
 one thread can execute code at a time in an object of this class, the
 three new threads will remain blockedat the Demo method until the
 Testmethod finishes - which requires the ReadLine to complete. Hence
 we end up with the same result as before, but only after pressing the
 Enter key. This is a thread-safety hammer almost big enough to preclude
 any useful multithreading within a class!
*/