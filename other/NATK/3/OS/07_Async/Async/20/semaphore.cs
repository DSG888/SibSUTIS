/*
Semaphores can be useful in limiting concurrency - preventing too many
 threads from executing a particular piece of code at once. In the
 following example, five threads try to enter a nightclub that allows
 only three threads in at once:
*/
using System;
using System.Threading;
class TheClub      // No door lists!
{
//  static Semaphore _sem = new Semaphore (1,1);    // Capacity of 3
 
  static void Main()
  {
//    for (int i = 1; i <= 5; i++) new Thread (Enter).Start (i);
    new Thread (Enter).Start(1);
  }
 
  static void Enter (object id)
  {
    Console.WriteLine (id + " wants to enter");
//    _sem.WaitOne();
    Console.WriteLine (id + " is in!");           // Only three threads
    Thread.Sleep (1000 * (int) id);               // can be here at
    Console.WriteLine (id + " is leaving");       // a time.
//    _sem.Release();
  }
}
