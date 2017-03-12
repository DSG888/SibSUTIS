using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;


namespace Threading
{
    class Program
    {
        static int Check(string s)
        {
            for (int i = 0; i <= 2; i++)
            {
                if (s[i] < '0' || s[i] > '9')
                    return -1;
                else
                    i++;
            }
            return 1;
        }

        static void Main(string[] args)
        {
            string s, s1;
            for (; ; )
            {
                Console.Write("Enter through space two numerals: ");
                s = Console.ReadLine();
                if (s == "") break;
                if (s.Length > 2)
                {
                    if (Check(s) == 1)
                    {
                        s1 = "";
                        s1 += s[0];
                    }
                    else
                    {
                        Console.WriteLine("Error values: first-{0}, second-{1}", s[0], s[2]);
                        continue;
                    }
                }
                else
                {
                    if (s.Length == 1)
                    {
                        Console.WriteLine("Error values: first value: {0}", s[0]);
                        continue;
                    }
                    else
                    {
                        Console.WriteLine("Error values: first-{0}, second-no", s[0]);
                        continue;
                    }
                }

                Worker w = new Worker();
                Thread first = new Thread(w.Counting);

                first.Start();
                first.Join();
            }
        }
    }
    //    internal class Worker
    public class Worker
    {
        public void Counting()
        {
            Random r = new Random();
            int j;
            for (int i = 0; i < 5; i++)
            {
                j = r.Next(97, 123);
                Console.WriteLine("Count: {0} - Thread: {1}", i, Thread.CurrentThread.ManagedThreadId);
                Thread.Sleep(100);
            }
        }
    }
}
