
using System;
using System.Threading;

class Test
{
	static EventWaitHandle ewh1 = new AutoResetEvent (false);
	static EventWaitHandle ewh2 = new AutoResetEvent (false);
	static EventWaitHandle ewh3 = new AutoResetEvent (false);
	static EventWaitHandle ewh4 = new AutoResetEvent (false);
	static int number;
	static Random rand = new Random();
	private static Mutex mut = new Mutex();

	static void Main()
	{
	   new Thread(Write).Start("W");
	   new Thread(Read1).Start("R1");
	   new Thread(Read2).Start("R2");
	   new Thread(Read3).Start("R3");

	}

	static void Read1(object threadID)
	{
	   for (int i=0; i<5; i++)
	   {
		ewh1.WaitOne();
		Console.WriteLine("Thread " + threadID + " reading " + number);
		Thread.Sleep(0);
		ewh2.Set();
	   }
	}

       	static void Read2(object threadID)
	{
	   for (int i=0; i<5; i++)
	   {
		ewh2.WaitOne();
		Console.WriteLine("Thread " + threadID + " reading " + number);
		Thread.Sleep(2);
		ewh3.Set();
	   }
	}

       	static void Read3(object threadID)
	{
	   for (int i=0; i<5; i++)
	   {
		ewh3.WaitOne();
		Console.WriteLine("Thread " + threadID + " reading " + number);
		Thread.Sleep(2);
		ewh4.Set();
	   }
	}

	static void Write(object threadID)
	{
	   for (int i=0; i<5; i++)
	   {
		number = GetRandNum(100);
		Console.WriteLine("Thread " + threadID + " writing " + number);
		ewh1.Set();
		Thread.Sleep(200);
		ewh4.WaitOne();
	   }
	}

	static int GetRandNum(int max) 
	{ 
	   lock (rand) return rand.Next(max); 
	}
}