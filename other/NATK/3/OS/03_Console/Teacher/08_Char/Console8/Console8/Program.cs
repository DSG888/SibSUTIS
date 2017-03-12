using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Console8
{
    class Program
    {
        private static int GetCode(char ch)
        {
            return (int)ch;
        }
        private static void Print(string s)
        {
            int l;
            l = GetCode(s[0]);
            Console.WriteLine("Введённому символу {0} соответствует код {1}", s[0], l);

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
                Console.Write("Введите любой символ: ");
                s = Console.ReadLine();
                if (s == "") break;
                //                Console.WriteLine("Вы ввели {0}", s);
                Print(s);
            }
            //            MessageBox.Show("Конец работы");
        }
    }
}
