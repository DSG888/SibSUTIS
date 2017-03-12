using System;
using System.Collections.Generic;
using System.Linq;
using System.Diagnostics;
using System.Windows.Forms;

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
        [STAThread]
        static void Main(string[] args)
        {
            string fileName = "";   //имя файла
            string arguments = "";  //аргументы, для запуска файла из командной строки
            //string verbToUse = "";  //какие действия можно производить с заданным файлом
            ProcessStartInfo startInfo = new ProcessStartInfo();    //создание класса для запуска процесса
            OpenFileDialog openFileDialog1 = new OpenFileDialog();  //создание класса диалога

            //определение каталога
            openFileDialog1.InitialDirectory = "d:\\labC#\\151\\";
            //определение возможного списка выбираемых файлов
            openFileDialog1.Filter = "exe files (*.exe)|*.exe";
            openFileDialog1.FilterIndex = 1;    //индекс фильтра диалогового окна
            //восстановление текущего каталога перед закрытием окна диалога
            openFileDialog1.RestoreDirectory = true;


            //string paf = "c:\\laptev\\labC#\\15\\console1";
            //string fileName = "console1";

        //выбор файла в заданном каталоге с помощью диалогового окна
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {

                Process myProcess = new Process();
                if ((fileName = openFileDialog1.FileName) != null)
                {
                    //задание файла, по которому должен запускаться процесс
                    //startInfo = new ProcessStartInfo(fileName);
                    myProcess.StartInfo.FileName = fileName;
                }

                string fn = "";
                for (int i = fileName.Length - 1; i > 0; i--)
                {
                    if (fileName[i] == '\\')
                        break;
                    if (fileName[i] == '.')
                        fn = "";
                    else
                        fn = fileName[i] + fn;
                }
                Console.WriteLine("File name = {0}", fn);
                Console.Write("Enter the parameter:");  //вывод приглашения о вводе параметров
                arguments = Console.ReadLine();         //ввод параметров
                //startInfo.Arguments = arguments;        //передача параметров

                //Process myProcess = new Process();
                //myProcess.StartInfo.FileName = paf;
                //myProcess.StartInfo.Arguments = "qwer erty yuiop";
                myProcess.StartInfo.Arguments = arguments;
                myProcess.Start();
                System.Threading.Thread.Sleep(3000);

                ProcessThreadCollection threads;
                Process[] notepads;
                // Retrieve the Notepad processes.
                notepads = Process.GetProcessesByName(fn);
                // Read the Process.Threads property.
                threads = notepads[0].Threads;
                // Read desired ProcessThread property.
                Console.WriteLine("Process {0} has Base Priority {1}", fileName, threads[0].BasePriority.ToString());
                Console.ReadLine();
            }
        }
    }
}
