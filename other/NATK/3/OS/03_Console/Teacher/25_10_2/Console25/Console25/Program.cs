using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Console4
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

        private static string Con_10_2(string s)
        {
            string t = "";
            int n = Convert.ToInt32(s);
            int n1, n2;
            while (true)
            {
                n1 = n / 2;
                n2 = n % 2;
//                Console.WriteLine("{0} {1}", n1, n2);
                t = Convert.ToString(n2) + t;
                if (n1 == 0) break;
                n = n1;
            }
            return t;
        }

        private static void Print(string s)
        {
            string t, t1;
            t = Check(s);
            if (t == null)
            {
                t1 = Con_10_2(s);
                Console.WriteLine("Десятичное число {0} = двоичному {1}", s, t1);
            }
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
                Console.Write("Введите десятичное число: ");
                s = Console.ReadLine();
                if (s == "") break;
                //                Console.WriteLine("Вы ввели {0}", s);
                Print(s);
            }
            //            MessageBox.Show("Конец работы");
        }
    }
}
