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
        public void PrintNumbers()
        {
//            lock (this)
//            {
                // Display Thread info.
                Console.WriteLine("-> {0} is executing PrintNumbers()",
                    Thread.CurrentThread.Name);

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

            Printer p = new Printer();

            // Make 10 threads which are all pointing to the same
            // method on the same object.
            Thread[] threads = new Thread[5];	//10
            for (int i = 0; i < 5; i++)		//10
            {
                threads[i] =
                    new Thread(new ThreadStart(p.PrintNumbers));
                threads[i].Name = string.Format("Worker thread #{0}", i);
            }

            // Now start each one.
            foreach (Thread t in threads)
                t.Start();
            Console.ReadLine();
        }
    }
}
