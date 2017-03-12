using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace Console1
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
                if (ch == 'ё') t += 'Ё';
                else if (ch >= 'a' && ch <= 'z') t += (char)((int)ch - 32);
                else if (ch >= 'а' && ch <= 'я') t += (char)((int)ch - 32);
                else t += ch;
            }
            return t;
        }
        private static void Print(string s)
        {
            string t;
            t = Convert(s);
            Console.WriteLine("Результат преобразования в большие буквы: " + t);

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
                Console.Write("Введите любую строку(маленькие буквы): ");
                s = Console.ReadLine();
                if (s == "") break;
//                Console.WriteLine("Вы ввели {0}", s);
                   Print(s);
            }
//            MessageBox.Show("Конец работы");
        }
        internal class WorkerClass
        {
            public void DoSomeWork()
            {
                // Get some information about the worker thread.
                Console.WriteLine("ID of worker thread is: {0}",
                                  Thread.CurrentThread.GetHashCode());

                // Do the work.
                Console.Write("Worker says: ");
                for (int i = 0; i < 20; i++)
                {
                    Console.Write(i + ", ");
                    Thread.Sleep(500);
                }
                Console.WriteLine();
            }
        }
    }
}
