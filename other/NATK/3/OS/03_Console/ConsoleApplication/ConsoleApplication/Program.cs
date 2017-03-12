using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;

namespace ConsoleApplication
{
    class Program
    {
        private static int Check(string s)
        {
            char ch;
            int cnt = 0;
            for (int i = 0; i < s.Length; i++)
            {
                ch = s[i];
                if (ch < '0' || ch > '9')
                {
                    cnt++;
                }
            }
            if (cnt == 0)
                return Convert.ToInt32(s);
            else
                return -1;
        }
        private static void Print(string s)
        {
            int val = Check(s);
            if (val != -1 && val != 0)
            {
                if (val > 9) val = 9;
                for (int i = 0; i < val; i++)
                    Console.WriteLine("Значение: {0}", i);
            }
            else
                Console.WriteLine("Ошибочное значение: {0}", s);
        }
        static void Main(string[] args)
        {
            if (args.Length == 0) Console.WriteLine("Не заданы параметры");
            else
            {
                Console.WriteLine("Введены следующие параметры:");
                for (int i = 0; i < args.LongLength; i++)
                    Console.WriteLine("Параметр {0} - {1}", i, args[i]);
                Print(args[0]);
            }
            string s;
            for (; ; )
            {
                Console.Write("Введите число(>0, но <10): ");
                s = Console.ReadLine();
                if (s == "") break;
                Print(s);
            }
        }
    }
}
