using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Console11
{
    class Program
    {
        private static int Count(string s, string s1)
        {
            int val = 0;
            for (int i = 0; i < s.Length; i++)
            {
                if (s[i] == s1[0])
                    val++;
            }
            return val;
        }
        private static void Print(string s, string s1)
        {
            if (s1 != "")
            {
                int val = Count(s, s1);
                Console.WriteLine("Символ {0} присутствует в строке {1} {2} раз(а)", s1[0], s, val);
            }
            else
                Console.WriteLine("Не задан символ, присутствующий в строке");
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
                Console.Write("Введите символ, присутствующий в строке: ");
                s1 = Console.ReadLine();
                Print(s, s1);
            }
            //            MessageBox.Show("Конец работы");
        }
    }
}
