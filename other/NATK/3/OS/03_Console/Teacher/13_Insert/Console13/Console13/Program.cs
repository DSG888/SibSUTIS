using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Console13
{
    class Program
    {
        private static string Insert(string s)
        {
            string s1 = "";
            for (int i = 0; i < s.Length; i++)
                s1 = s1 + s[i] + ' ';
            return s1;
        }
        private static void Print(string s)
        {
            //if (s.Length > 40)
            //{
                //Console.WriteLine("Слишком большая длина введённой строки(>40): {0}", s);
                //return;
            //}
            string val = Insert(s);
            Console.WriteLine("Результат чередования введённых символов: {0}", val);
        }
        static void Main(string[] args)
        {
            if (args.Length == 0) Console.WriteLine("Не заданы параметры");
            else
            {
                Console.WriteLine("Введены следующие параметры:");
                for (int i = 0; i < args.LongLength; i++)
                    Console.WriteLine("Параметр {0} - {1}", i, args[i]);
                if (args.Length >= 1)
                    Print(args[0]);
            }
            string s;
            for (; ; )
            {
                Console.Write("Введите любую строку(Enter - выход): ");
                s = Console.ReadLine();
                if (s == "") break;
                Print(s);
            }
        }
    }
}
