using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Console14
{
    class Program
    {
        private static void Print(string s)
        {
            if (s.Length > 40)
            {
                Console.WriteLine("Слишком большая длина введённой строки(>40): {0}", s);
                return;
            }
            Console.WriteLine("Введены следующие элементы массива:");
            int count = s.Length;
            int i = 0;
            for (; ; )
            {
                if (i >= count)
                    break;
                string s1 = "";
                while ((s[i] != ' ') && (i < count))
                {
                  	s1=s1+s[i];
      	            ++i;
                    if (i == count)
                        break;
                }
                Console.WriteLine(s1);
                ++i;
            }
        }
        static void Main(string[] args)
        {
            string s;
            if (args.Length == 0) Console.WriteLine("Не заданы параметры");
            else
            {
                s = "";
                Console.WriteLine("Введены следующие параметры:");
                for (int i = 0; i < args.LongLength; i++)
                {
                    Console.WriteLine("Параметр {0} - {1}", i, args[i]);
                    s = s + args[i] + ' ';
                }
                if (args.Length >= 1)
                    Print(s);
            }
            for (; ; )
            {
                Console.Write("Введите, через пробел, элементы массива(Enter - выход): ");
                s = Console.ReadLine();
                if (s == "") break;
                Print(s);
            }
        }
    }
}
