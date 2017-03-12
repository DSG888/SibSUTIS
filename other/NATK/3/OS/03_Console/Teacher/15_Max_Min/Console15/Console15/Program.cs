using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Console15
{
    class Program
    {
        static string max, min;
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
        private static void Print(string s)
        {
            if (s.Length > 40)
            {
                Console.WriteLine("Слишком большая длина введённой строки(>40): {0}", s);
                return;
            }
            int count = s.Length;
            int i = 0;
            int first = 1;
            for (; ; )
            {
                if (i >= count)
                    break;
                string s1 = "";
                while ((s[i] != ' ') && (i < count))
                {
                    s1 = s1 + s[i];
                    ++i;
                    if (i == count)
                        break;
                }
                ++i;
                string val = Check(s1);
                if (val == null) 
                {
                    if (first == 1)
                    {
                        max = s1;
                        min = s1;
                        first = 0;
                    }
                    else
                    {
                        if (Convert.ToUInt32(s1) > Convert.ToUInt32(max)) max = s1;
                        if (Convert.ToUInt32(s1) < Convert.ToUInt32(min)) min = s1;
                    }
                }
                else
                {
                    Console.WriteLine("Элемент {0} не является числом. Обнаружены ошибки в позициях:", s1);
                    Console.WriteLine(val);
                }
            }
            if (first == 1) 
                    Console.WriteLine("Вычисления не выполнялись");
            else
                Console.WriteLine("Max = {0}, min = {1}", max, min);
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
                Console.Write("Введите, через пробел, элементы массива чисел(Enter - выход): ");
                s = Console.ReadLine();
                if (s == "") break;
                Print(s);
            }
        }
    }
}
