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
  static private Object o = new Object();

  public void Demo(object obj)
  {
//    lock(o)
//    {
      int cnt = (int)obj;
      for (int i=0; i<cnt; i++)
      {	
//	Console.Write("Start..."+ Thread.CurrentThread.ManagedThreadId.ToString()+" - "+ Convert.ToString(i));
	Console.Write("Start..."+ Thread.CurrentThread.Name+" - "+ Convert.ToString(i));
	Thread.Sleep (1000);
//	Console.WriteLine (" end "+ Thread.CurrentThread.ManagedThreadId.ToString()+" - "+ i);
	Console.WriteLine (" end "+ Thread.CurrentThread.Name+" - "+ i);
      }
//    }
  }
 
  public void Test()
  {
//    new Thread (Demo).Start(1);
//    new Thread (Demo).Start();
//    new Thread (Demo).Start();

//    ParameterizedThreadStart ts = new ParameterizedThreadStart(Demo);
//    Thread t1 = new Thread(ts);
//    t1.Start(3);

//    new Thread (Demo).Start(3); 
//    new Thread (Demo).Start(4); 
//    new Thread (Demo).Start(5); 
     
      Thread w1 = new Thread(Demo);
      w1.Name = "worker1";
      w1.Start(3);
      Thread w2 = new Thread(Demo);
      w2.Name = "worker2";
      w2.Start(3);
      Thread w3 = new Thread(Demo);
      w3.Name = "worker3";
      w3.Start(3);

//    Console.ReadLine();
  }
 
  public static void Main()
  {
    new AutoLock().Test();
//    Console.WriteLine ("Push Enter");
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