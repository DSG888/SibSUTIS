using System;
using System.Threading;

class Test
{
    static TimeSpan waitTime = new TimeSpan(0, 0, 1);

    public static void Main() 
    {
/*
        Thread newThread = 
            new Thread(new ThreadStart(Work));
        newThread.Start();
*/
	Work wo = new Work(waitTime);
	Thread newThread = new Thread(wo.DoWork);
	newThread.Start();

        if(newThread.Join(waitTime + waitTime))
        {
            Console.WriteLine("New thread terminated.");
        }
        else
        {
            Console.WriteLine("Join timed out.");
        }
    }
/*
    static void Work()
    {
        Thread.Sleep(waitTime);
    }
*/
}
public class Work
{
   private TimeSpan ts;

   public Work()
   {
	this.ts = new TimeSpan(0,0,1);
   }

   public Work(TimeSpan tmsp)
   {
	this.ts = tmsp;
   }

   public void DoWork()
   {
	Thread.Sleep(ts);	
   }
}