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
//  static SemaphoreSlim _sem = new SemaphoreSlim (3);    // Capacity of 3
  static Semaphore _sem = new Semaphore (1,1);    // Capacity of 3
 
  static void Main()
  {
//    for (int i = 1; i <= 5; i++) new Thread (Enter).Start (i);
    Thread [] ts = new Thread[5];
    for (int i=0; i<5; i++)
    {
	Thread t = new Thread(Enter);
	ts[i] = t;
	switch (i)
	{
	  case 0:
	    ts[i].Name = "Work0";
	    break;
	  case 1:
	    ts[i].Name = "Work1";
	    break;
	  case 2:
	    ts[i].Name = "Work2";
	    break;
	  case 3:
	    ts[i].Name = "Work3";
	    break;
	  case 4:
	    ts[i].Name = "Work4";
	    break;
	}
	ts[i].Start(i);
    }
  }
 
  static void Enter (object id)
  {
//    Console.WriteLine (id + Thread.CurrentThread.Name + " wants to enter");
    Console.WriteLine (Thread.CurrentThread.Name + " wants to enter");
//    _sem.WaitOne();
//    Console.WriteLine (id + Thread.CurrentThread.Name + " is in!");           // Only three threads
    Console.WriteLine (Thread.CurrentThread.Name + " is in!");           // Only three threads
    Thread.Sleep (1000 * (int) id);               // can be here at
//    Console.WriteLine (id + Thread.CurrentThread.Name + " is leaving");       // a time.
    Console.WriteLine (Thread.CurrentThread.Name + " is leaving");       // a time.
//    _sem.Release();
  }
}
