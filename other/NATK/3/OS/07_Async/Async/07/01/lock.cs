using System;
using System.Threading;
class ThreadUnsafe
{
  static int _val1 = 1, _val2 = 1;
 
//  static void Go()
  public void Go(object obj)
  {
//    lock(this)
//    {
    int num = (int)obj;
    if (_val2 != 0) Console.WriteLine ("Thread {0}, rezult = {1}", num,_val1 / _val2);
    _val2 = 0;
//    }
  }
}
/*
This class is not thread-safe: if Go was called by two threads
 simultaneously, it would be possible to get a division-by-zero error,
 because _val2 could be set to zero in one thread right as the other
 thread was in between executing the if statement and Console.WriteLine.
Here's how lock can fix the problem:
*/
class ThreadSafe
{
//  static readonly object _locker = new object();
  static object _locker = new object();
//  static int _val1, _val2;
/* 
  static void Go()
  {
    lock (_locker)
    {
      if (_val2 != 0) Console.WriteLine ("Value = {0}",_val1 / _val2);
      _val2 = 0;
    }
  }
*/
   public static void Main() 
   {
//	_val1 = 1;
//	_val2 = 1;
	ThreadUnsafe tus = new ThreadUnsafe();
    ParameterizedThreadStart ts = new ParameterizedThreadStart(tus.Go);
    Thread t1 = new Thread(ts);
    Thread t2 = new Thread(ts);
//	Thread t1 = new Thread(new ThreadStart(tus.Go));
//	Thread t2 = new Thread(new ThreadStart(tus.Go));
//	Thread t1 = new Thread(Go);
//	Thread t2 = new Thread(Go);
	t1.Start(1);
	t2.Start(2);
   }
}
/*
Only one thread can lock the synchronizing object (in this case, _locker)
 at a time, and any contending threads are blocked until the
 lock is released. If more than one thread contends the lock, they
 are queued on a "ready queue" and granted the lock on a first-come,
 first-served basis (a caveat is that nuances in the behavior of Windows
 and the CLR mean that the fairness of the queue can sometimes be
 violated). Exclusive locks are sometimes said to enforce serialized
 access to whatever's protected by the lock, because one thread's
 access cannot overlap with that of another. In this case, we're
 protecting the logic inside the Gomethod, as well as the fields _val1
 and _val2.
*/