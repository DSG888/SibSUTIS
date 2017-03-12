using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Console6
{
    class Program
    {
        private static string Add(string s, string s1)
        {
            string t = "";
            for (int i = 0; i < s.Length; i++)
                t += s[i];
            for (int i = 0; i < s1.Length; i++)
                t += s1[i];
            return t;
        }

        private static void Print(string s, string s1)
        {
            string t;
            if (s1 != "")
            {
                t = Add(s, s1);
                Console.WriteLine("Результат объединения строк = {0}", t);
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
