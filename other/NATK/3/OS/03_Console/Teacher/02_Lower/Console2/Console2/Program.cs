using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Console2
{
    class Program
    {
        private static string Convert(string s)
        {
            string t = "";
            char ch;
            //            for (int i = s.Length - 1; i >= 0; i--)
            //                t += s[i];
            for (int i = 0; i < s.Length; i++)
            {
                ch = s[i];
                if (ch == 'Ё') t += 'ё';
                else if (ch >= 'A' && ch <= 'Z') t += (char)((int)ch + 32);
                else if (ch >= 'А' && ch <= 'Я') t += (char)((int)ch + 32);
                else t += ch;
            }
            return t;
        }
        private static void Print(string s)
        {
            string t;
            t = Convert(s);
            Console.WriteLine("Результат преобразования в маленькие буквы: " + t);

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
                Console.Write("Введите любую строку(большие буквы): ");
                s = Console.ReadLine();
                if (s == "") break;
                //                Console.WriteLine("Вы ввели {0}", s);
                Print(s);
            }
            //            MessageBox.Show("Конец работы");
        }
    }
}
