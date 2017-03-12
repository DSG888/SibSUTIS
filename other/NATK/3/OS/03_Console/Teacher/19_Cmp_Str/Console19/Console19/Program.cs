using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Console6
{
    class Program
    {
        private static int Compare(string s, string s1)
        {
            if (s.Length == s1.Length)
                return 0;
            else if (s.Length > s1.Length)
                return 1;
            else return -1;
        }

        private static void Print(string s, string s1)
        {
            int rez;
            if (s1 != "")
            {
                rez = Compare(s, s1);
                switch (rez)
                {
                    case 0:
                        Console.WriteLine("Введённые строки совпадают по длине, те s.Length({0}) = s1.Length({1})", s.Length, s1.Length);
                        break;
                    case 1:
                        Console.WriteLine("Длина первой строки больше длины второй, те s.Length({0}) > s1.Length({1})", s.Length, s1.Length);
                        break;
                    case -1:
                        Console.WriteLine("Длина первой строки меньше длины второй, те s.Length({0}) < s1.Length({1})", s.Length, s1.Length);
                        break;
                }
            }
            else
                Console.WriteLine("Не задана другая строка");
        }
        static void Main(string[] args)
        {
            if (args.Length == 0) Console.WriteLine("Не заданы параметры");
            else
            {
                Console.WriteLine("Введены следующие параметры:");
                for (int i = 0; i < args.LongLength; i++)
                    Console.WriteLine("Параметр {0} - {1}", i, args[i]);
                if (args.Length == 1)
                    Print(args[0], "");
                else
                    Print(args[0], args[1]);
                //    			WorkerClass w = new WorkerClass();
                //                w.DoSomeWork();
                //  
            }
            string s, s1;
            for (; ; )
            {
                Console.Write("Введите любую строку: ");
                s = Console.ReadLine();
                if (s == "") break;
                //                Console.WriteLine("Вы ввели {0}", s);
                Console.Write("Введите другую строку: ");
                s1 = Console.ReadLine();
                Print(s, s1);
            }
        }
    }
}
