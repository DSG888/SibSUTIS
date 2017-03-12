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
            int j = 0;
            if (s1[0] == '-') j = 1; 
            for (int i = j; i < s1.Length; i++)
            {
                ch = s1[i];
                if (ch < '0' || ch > '9')
                    return 9999;
            }
            return Convert.ToInt32(s1);
        }
        private static string Update(string s, string s1)
        {
            string t = "";
            int val = Check(s1);
            if (val == 9999)    
                return null;
            if (s1[0] == '-')
            {
                if (-val > s.Length) return null;
                for (int i = 0; i < s.Length + val; i++)
                    t += s[i];
            }
            else
            {
                for (int i = 0; i < s.Length; i++)
                    t += s[i];
                for (int i = 0; i < val; i++)
                    t += '_';
            }
            return t;
        }
        private static void Print(string s, string s1)
        {
            string t;
            if (s1 != "")
            {
                t = Update(s, s1);
                if (t != null)
                {
                    if (s1[0] == '-')
                        Console.WriteLine("Результат удаления {0} символов из строки = {1}", s1[1], t);
                    else
                        Console.WriteLine("Результат дабавления {0} символов к строке = {1}", s1, t);
                }
                else
                    Console.WriteLine("Ошибочное значение {0}", s1);
            }
            else
                Console.WriteLine("Не задано количество добавляемых или удаляемых(-) символов");
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
                Console.Write("Введите количество добавляемых или удаляемых(-) символов: ");
                s1 = Console.ReadLine();
                Print(s, s1);
            }
            //            MessageBox.Show("Конец работы");
        }
    }
}
