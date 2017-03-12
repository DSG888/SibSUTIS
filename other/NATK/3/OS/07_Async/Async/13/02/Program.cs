#region Using directives

using System;
using System.Collections.Generic;
using System.Text;

#endregion

using System.Threading;

namespace MultiThreadedPrinting
{
    public class Printer
    {
	private string name;
	private int number;

	public Printer(string name, int number)
	{
	   this.name = name;
	   this.number = number;
	}

        public void PrintNumbers(object obj)
        {
//            lock (this)
//            {
		int num = (int)obj;
                // Display Thread info.
                Console.WriteLine("Value.name = {0}, value.number = {1}. -> {2} is executing PrintNumbers({3})",
                    name, number++, Thread.CurrentThread.Name, num);

                // Print out numbers.
                Console.Write("Your numbers: ");
                for (int i = 0; i < 5; i++)	//10
                {
                    Random r = new Random();
                    Thread.Sleep(1000 * r.Next(5));
                    Console.Write(i + ", ");
                }
                Console.WriteLine();
//            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("***** Synchronizing Threads *****\n");

            Printer p = new Printer("Param", 10);

            // Make 10 threads which are all pointing to the same
            // method on the same object.

    ParameterizedThreadStart ts = new ParameterizedThreadStart(p.PrintNumbers);

            Thread[] threads = new Thread[5];	//10
            for (int i = 0; i < 5; i++)		//10
            {
                threads[i] =
                    new Thread(new ParameterizedThreadStart(ts));
//                    new Thread(new ThreadStart(p.PrintNumbers));
                threads[i].Name = string.Format("Worker thread #{0}", i);
            }

            // Now start each one.
            int j = 0;
            foreach (Thread t in threads)
	    {
                t.Start(j);
		j++;
	    }
//            Console.ReadLine();
        }
    }
}
