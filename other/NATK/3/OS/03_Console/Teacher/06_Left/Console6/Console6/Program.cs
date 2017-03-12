using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Console6
{
    class Program
    {
        private static int Check(string s1)
        {
            char ch;
            int val;
            for (int i = 0; i < s1.Length; i++)
            {
                ch = s1[i];
                if (ch < '0' || ch > '9')
                    return -1;
            }
            return Convert.ToInt32(s1);
        }
        private static string Extract(string s, string s1)
        {
            string t = "";
            int val = Check(s1);
            if (val < 0 || val > s.Length)
                return null;
            return t = s.Substring(0, val);
        }
        private static void Print(string s, string s1)
        {
            string t;
            if (s1 != "")
            {
                t = Extract(s, s1);
                if (t != null)
                    Console.WriteLine("Из строки {0} слева выделена подстрока {1}", s, t);
                else
                    Console.WriteLine("Ошибочное значение {0}", s1);
            }
            else
                Console.WriteLine("Не задан размер подстроки");
        }
        static void Main(string[] args)
        {
            if (args.Length == 0) Console.WriteLine("Не заданы параметры");
            else
            {
                Console.WriteLine("Введены следующие параметры:");
                for (int i = 0; i < args.LongLength; i++)
                    Console.WriteLine("Параметр {0} - {1}", i, args[i]);
                if (args.Length==1)
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
                Console.Write("Введите размер подстроки выделяемой слева: ");
                s1 = Console.ReadLine();
                Print(s, s1);
            }
            //            MessageBox.Show("Конец работы");
        }
    }
}
