
using System;
using System.Threading;

class Test
{
	static EventWaitHandle ewh = new AutoResetEvent (false);
	static int number;
	static Random rand = new Random();
	static int cnt = 5;

	static void Main()
	{

	   new Thread(Read).Start("R");
	   for (int i=0; i<cnt; i++)
	   {
		number = GetRandNum(100);
		Console.WriteLine("Main thread writing " + number);
		ewh.Set();
		Thread.Sleep(500);
	   }

	}

	static void Read(object threadID)
	{
	   for (int i=0; i<cnt; i++)
	   {
		ewh.WaitOne();
		Console.WriteLine("Thread " + threadID + " reading " + number);
	   }
	}

	static int GetRandNum(int max) 
	{ 
	   lock (rand) return rand.Next(max); 
	}
}