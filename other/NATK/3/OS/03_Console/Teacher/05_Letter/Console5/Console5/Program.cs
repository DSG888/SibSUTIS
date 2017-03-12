using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Console5
{
    class Program
    {
        private static string Check(string s)
        {
            char ch;
            int cnt = 0;
            string t = "";
            for (int i = 0; i < s.Length; i++)
            {
                ch = s[i];
                if (ch >= '0' && ch <= '9')
                {
                    if (cnt == 0)
                        t += Convert.ToString(i);
                    else
                    {
                        t += ", ";
                        t += Convert.ToString(i);
                    }
                    cnt++;
                }
            }
            if (cnt == 0)
                return null;
            else
                return t;
        }
        private static void Print(string s)
        {
            string t;
            t = Check(s);
            if (t == null)
                Console.WriteLine("Введены не числа: {0}", s);
            else
                Console.WriteLine("Обнаружены ошибки в следующих позициях: {0}", t);
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
                //    			WorkerClass w = new WorkerClass();
                //                w.DoSomeWork();
                //  
            }
            string s;
            for (; ; )
            {
                Console.Write("Введите любую строку: ");
                s = Console.ReadLine();
                if (s == "") break;
                //                Console.WriteLine("Вы ввели {0}", s);
                Print(s);
            }
            //            MessageBox.Show("Конец работы");
        }
    }
}
