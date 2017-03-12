/*
An alternative to locking manually is to lock declaratively. By deriving
 from ContextBoundObject and applying the Synchronization attribute, you
 instruct the CLR to apply locking automatically. For example:
Альтернативой блокировки вручную является декларативная блокировка.
Используя производный класс от ContextBoundObject и применяя атрибут
 Synchronization, вы указываете CLR обеспечить блокировку автоматически.
*/
using System;
using System.Threading;
using System.Runtime.Remoting.Contexts;
 
//[Synchronization]
//public class AutoLock : ContextBoundObject
public class AutoLock //: ContextBoundObject
{
  static private Object o = new Object();
  private int cnt;

  public AutoLock(int count)
  {
	this.cnt = count;
  }

  public void Demo()
  {
//   lock(o)
//   {
    for (int i=0; i<cnt; i++)
    {
//	Console.Write ("Start...{0} ", i);
//	Console.Write("Start..."+ Thread.CurrentThread.ManagedThreadId.ToString()+" - "+ Convert.ToString(i));
	Console.Write("Start..."+ Thread.CurrentThread.Name+" - "+ Convert.ToString(i));
	Thread.Sleep (1000);           // We can't be preempted here
//	Console.WriteLine ("end {0}", i);     // thanks to automatic locking!
//	Console.WriteLine (" end "+ Thread.CurrentThread.ManagedThreadId.ToString()+" - "+ i);
	Console.WriteLine (" end "+ Thread.CurrentThread.Name+" - "+ i);
    }
//   }
//Мы не можем здесь захватываться другими потоками благодаря
// автоматической блокировке!
  } 
}
 
public class Test
{
  public static void Main()
  {
    AutoLock safeInstance = new AutoLock(4);
//    new Thread (safeInstance.Demo).Start();     // Call the Demo
//    new Thread (safeInstance.Demo).Start();     // method 3 times
//    safeInstance.Demo();                        // concurrently.

    Thread w1 = new Thread(safeInstance.Demo);
    w1.Name = "work1";
    w1.Start();
    Thread w2 = new Thread(safeInstance.Demo);
    w2.Name = "work2";
    w2.Start();
    Thread w3 = new Thread(safeInstance.Demo);
    w3.Name = "work3";
    w3.Start();
//Вызов метода Demo параллельно 3 раза.
  }
}
