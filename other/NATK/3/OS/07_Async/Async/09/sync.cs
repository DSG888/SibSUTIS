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
  public void Demo()
  {
    Console.Write ("Start...");
    Thread.Sleep (1000);           // We can't be preempted here
    Console.WriteLine ("end");     // thanks to automatic locking!
//Мы не можем здесь захватываться другими потоками благодаря
// автоматической блокировке!
  } 
}
 
public class Test
{
  public static void Main()
  {
    AutoLock safeInstance = new AutoLock();
//    new Thread (safeInstance.Demo).Start();     // Call the Demo
//    new Thread (safeInstance.Demo).Start();     // method 3 times
    Thread t1 = new Thread(safeInstance.Demo);
    t1.Start();
    Thread t2 = new Thread(safeInstance.Demo);
    t2.Start();
    safeInstance.Demo();                        // concurrently.
//Вызов метода Demo параллельно 3 раза.
  }
}
