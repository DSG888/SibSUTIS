using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Console4
{
    class Program
    {
        private static int Compare(string s, string s1)
        {
            int n1, n2;
            n1 = Convert.ToInt32(s);
            n2 = Convert.ToInt32(s1);
            if (n1 == n2) return 0;
            else if (n1 > n2) return 1;
            else return -1;
        }

        private static string Check(string s)
        {
            char ch;
            int cnt = 0;
            string t = "";
            for (int i = 0; i < s.Length; i++)
            {
                ch = s[i];
                if (ch < '0' || ch > '9')
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
        private static void Print(string s, string s1)
        {
            string t, t1;
            int err = 0;
            t = Check(s);
            if (t != null)
//                Console.WriteLine("Введено число: {0}", s);
//            else
            {
                Console.WriteLine("Для 1-го числа обнаружены ошибки в следующих позициях: {0}", t);
                ++err;
            }
            t1 = Check(s1);
            if (t1 != null)
//                Console.WriteLine("Введено число: {0}", s);
//            else
            {
                Console.WriteLine("Для 2-го числа обнаружены ошибки в следующих позициях: {0}", t1);
                ++err;
            }
            if (err == 0)
            {
                int rez = Compare(s, s1);
                switch (rez)
                {
                    case 0:
                        Console.WriteLine("Введённые числа равны, т.е. {0} = {1}", s, s1);
                        break;
                    case 1:
                        Console.WriteLine("Первое число больше второго, т.е. {0} > {1}", s, s1);
                        break;
                    case -1:
                        Console.WriteLine("Первое число меньше второго, т.е. {0} < {1}", s, s1);
                        break;
                }
            }
        }
        static void Main(string[] args)
        {
            if (args.Length == 0) Console.WriteLine("Не заданы параметры");
            else
            {
                Console.WriteLine("Введены следующие параметры:");
                for (int i = 0; i < args.LongLength; i++)
                    Console.WriteLine("Параметр {0} - {1}", i, args[i]);
                Print(args[0], args[1]);
                //    			WorkerClass w = new WorkerClass();
                //                w.DoSomeWork();
                //  
            }
            string s, s1;
            for (; ; )
            {
                Console.Write("Введите первое число: ");
                s = Console.ReadLine();
                if (s == "") break;
                Console.Write("Введите второе число: ");
                s1 = Console.ReadLine();
                Print(s, s1);
            }
            //            MessageBox.Show("Конец работы");
        }
    }
}
