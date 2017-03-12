using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Console12
{
    class Program
    {
        private static int Count(string s)
        {
            int val = 0;
            bool flag = false;
            for (int i = 0; i < s.Length; i++)
            {
                char ch = s[i];
                if ((ch == ' ') && (flag == false)) 
                {
                    ++val;
                    flag=true;
                }
                else if ((ch == ' ') && (flag == true));
                else flag=false;
            }
            if (flag == false) ++val;
            return val;
        }
        private static void Print(string s)
        {
            if (s.Length > 40)
            {
                Console.WriteLine("Слишком большая длина введённой строки(>40): {0}",s);
                return;
            }
            int val = Count(s);
            Console.WriteLine("Количество элементов массива: {0}", val);
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
