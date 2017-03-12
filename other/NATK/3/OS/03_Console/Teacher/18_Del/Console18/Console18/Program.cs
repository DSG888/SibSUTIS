using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Console6
{
    class Program
    {
        private static int Find(string s, string s1)
        {
            int len = s.Length;
            int len1 = s1.Length;
            int pos = -1;
            for (int i = 0; i < len; i++)
            {
                int k = i;
                if ((len - k) < len1)
                    break;
                int cnt = 0;
                for (int j = 0; j < len1; j++)
                {
                    if (s[i + j] == s1[j])
                        ++cnt;
                    else break;
                }
                if (cnt == len1)
                {
                    pos = k;
                    break;
                }
            }
            return pos;
        }

        private static string DelStr(string s, int len, int pos, int len1)
        {
            string t = "";
            for (int i = 0; i < len; i++)
            {
                if (i < pos || i >= pos + len1)
                    t += s[i];
            }
            return t;
        }

        private static void Print(string s, string s1)
        {
            int pos;
            if (s1 != "")
            {
                pos = Find(s, s1);
                if (pos != -1)
                {
                    string t = DelStr(s, s.Length, pos, s1.Length);
                    //Console.WriteLine("Подстрока {0} найдена в стоке {1} в позиции {2}", s1, s, pos);
                    Console.WriteLine("Результат удаления подстроки {0} в стоке {1} = {2}", s1, s, t);
                }
                else
                    Console.WriteLine("Подстрока {0} в стоке {1} не найдена", s1, s);
            }
            else
                Console.WriteLine("Не задана подстрока");
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
                Console.Write("Введите подстроку, находящуюся в строке: ");
                s1 = Console.ReadLine();
                Print(s, s1);
            }
        }
    }
}
