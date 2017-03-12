using System;
using System.Collections.Generic;
using System.Linq;
using System.Diagnostics;

/*
 Потоки процессов можно просмотреть с помощью значения свойства Threads компонента Process. Возвращаемое 
    значение относится к типу ProcessThreadCollection, содержащему коллекцию объектов ProcessThread, 
    которые представляют собой потоки операционной системы, используемые в процессе. Потом можно 
    повторить те же действия для всей коллекции, чтобы просмотреть свойства каждого отдельного потока. 
    Первичный поток не обязательно будет потоком с индексом 0 в коллекции. 

Получение сведений об использовании потока процессом
1 Если процесс не был запущен компонентом Process, свяжите компонент Process с нужным процессом. 
    Дополнительные сведения см. в разделе Практическое руководство. Привязка к существующим процессам. 

2 Присвойте значение свойства Threads процесса пустой переменной коллекции типа ProcessThread.

3 Повторите то же самое для индекса массива, чтобы увидеть свойства отдельного потока. 

В следующем примере показано считывание свойства Threads приложения Блокнот и присвоение значения 
    пустому массиву. Значение BasePriority первого потока в массиве ProcessThread затем читается и 
    отображается в текстовом окне с именем TextBox1. 
*/

namespace Thread
{
    class Program
    {
        static void Main(string[] args)
        {
            string paf = "d:\\labC#\\151\\console1";
            string fileName = "console1";

            Process myProcess = new Process();
            myProcess.StartInfo.FileName = paf;
            myProcess.StartInfo.Arguments = "qwer erty yuiop";
            myProcess.Start();
            System.Threading.Thread.Sleep(3000);

            ProcessThreadCollection threads;
            Process[] notepads;
            // Retrieve the Notepad processes.
            notepads = Process.GetProcessesByName(fileName);
            // Read the Process.Threads property.
            threads = notepads[0].Threads;
            // Read desired ProcessThread property.
            Console.WriteLine("Process {0} has Base Priority {1}", fileName, threads[0].BasePriority.ToString());
            Console.ReadLine();
        }
    }
}
