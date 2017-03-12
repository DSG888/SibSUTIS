using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Console10
{
    class Program
    {
        private static string Convert(string s)
        {
            string t = "";
            for (int i = s.Length - 1; i >= 0; i--)
                t += s[i];
            return t;
        }
        private static void Print(string s)
        {
            string t;
            t = Convert(s);
            Console.WriteLine("Результат преобразования строки: " + t);

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
