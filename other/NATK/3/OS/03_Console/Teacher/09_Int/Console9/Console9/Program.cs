using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Console9
{
    class Program
    {
        private static string GetChar(string s)
        {
            string t="";
            char ch;
            int val;
            for (int i = 0; i < s.Length; i++)
            {
                ch=s[i];
                if (ch < '0' || ch > '9')
                    return null;
            }
            val = Convert.ToInt32(s);
            if ((val < 33 || val > 1103) || (val >255 && val < 1040))
                return null;
            else
                return t += Convert.ToChar(val);
        }
        private static void Print(string s)
        {
            string t;
            t = GetChar(s);
            if (t!=null)
                 Console.WriteLine("Введённому коду {0} соответствует символ {1}", s, t);
            else
                Console.WriteLine("Ошибочное значение {0}", s);
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
                Console.Write("Введите число(>32,но <255 или >1039,но <1104): ");
                s = Console.ReadLine();
                if (s == "") break;
                //                Console.WriteLine("Вы ввели {0}", s);
                Print(s);
            }
            //            MessageBox.Show("Конец работы");
        }
    }
}
