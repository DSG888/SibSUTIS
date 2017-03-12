using System;
using System.Threading;

namespace Async
{
    class Program
    {
        static void Main(string[] args)
        {
            //Определение объекта-потока(Counting) с возможностоью передачи ему параметров
            //Поток определяется на пользовательском уровне, поэтому для него бесполезно
            //  использовать примитивы синхронизации, которые применимы только к потокам,
            //  выполняющимся на уровне ядра.
            ParameterizedThreadStart starter = new ParameterizedThreadStart(Counting);
            Thread first = new Thread(starter);     //Создание экземпляров потоков
            Thread second = new Thread(starter);

            first.Start(4);     //Запуск потоков с передачей им параметров
            second.Start(8);

            first.Join();       //Ожидание завершения потоков
            second.Join();

            Console.WriteLine("Нажмите любую клавишу");
            Console.Read();
        }

        static void Counting(object o)  //Типом параметра должен быть объект
        {
            Monitor.Enter(o);       //Попытка синхронизации потоков
            //Вход в критическую секцию
            try
            {
                int info = (int)o;  //Преобразование типов
                if (info == 0)
                {
                    Console.WriteLine("Не задано количество повторений для потока {0}", Thread.CurrentThread.ManagedThreadId);
                    return;
                }
                for (int i = 1; i <= info; i++)
                {
                    Console.WriteLine("Счётчик: {0} - Поток: {1}", i, Thread.CurrentThread.ManagedThreadId);
                    Thread.Sleep(100);
                }
            }
            finally
            {
                Monitor.Exit(o);    //Выход из критической секции
            }
        }
    }
}

