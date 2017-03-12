using System;
using System.IO;
using System.Text;
using System.Diagnostics;
using System.Windows.Forms;
/*
 Компонент Process может использоваться для запуска процессов в системе путем вызова метода Start. 
 Перед запуском метода Start необходимо задать имя файла процесса для запуска, установив в качестве 
 свойства FileName либо полный путь к конечному процессу, либо имя процесса (для удовлетворяющих 
 данному условию приложений Windows, таких как Блокнот).

Свойство FileName можно установить во время разработки в окне Свойства или во время выполнения, 
 используя значение свойства. StartInfo. Если имя файла устанавливается во время выполнения, можно 
 предпринять одно из следующих действий: 

- Задайте для свойства StartInfo соответствующее значение и вызовите метод Start или
- вызовите форму Shared метода Start и задайте имя файла в качестве параметра. Используйте этот метод, 
 когда не требуется задавать никаких других начальных параметров запуска. Этот метод не позволяет 
 задавать никакие другие аргументы открытия. 

Запуск процесса во время выполнения с помощью свойств StartInfo
1 Установите параметры запуска, предоставляемые свойством StartInfo.

2 Вызовите метод Start компонента Process. 

*/

namespace Start
{
    class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            //Process myProcess = new Process();
            //myProcess.StartInfo.FileName = "Notepad";
            //myProcess.StartInfo.FileName = "c:\\laptev\\labC#\\151\\console1.exe";
            //myProcess.StartInfo.WindowStyle = ProcessWindowStyle.Maximized;
            //myProcess.StartInfo.Arguments = "qwe rtyu iopas dfghjk";
            //myProcess.Start();
            string fileName = "";   //имя файла
            string arguments = "";  //аргументы, для запуска файла из командной строки
            string verbToUse = "";  //какие действия можно производить с заданным файлом
            ProcessStartInfo startInfo = new ProcessStartInfo();    //создание класса для запуска процесса
            OpenFileDialog openFileDialog1 = new OpenFileDialog();  //создание класса диалога

            //определение каталога
            openFileDialog1.InitialDirectory = "c:\\laptev\\labC#\\15\\";
            //определение возможного списка выбираемых файлов
            openFileDialog1.Filter = "exe files (*.exe)|*.exe";
            openFileDialog1.FilterIndex = 1;    //индекс фильтра диалогового окна
            //восстановление текущего каталога перед закрытием окна диалога
            openFileDialog1.RestoreDirectory = true;

            //выбор файла в заданном каталоге с помощью диалогового окна
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                if ((fileName = openFileDialog1.FileName) != null)
                {
                    //задание файла, по которому должен запускаться процесс
                    startInfo = new ProcessStartInfo(fileName);

                }

                //заданный файл испоьзовать для выполнения
                //startInfo.Verb = "runas";

                Console.Write("Enter the parameter:");  //вывод приглашения о вводе параметров
                arguments = Console.ReadLine();         //ввод параметров
                startInfo.Arguments = arguments;        //передача параметров

                Process newProcess = new Process();     //создание нового процесса
                newProcess.StartInfo = startInfo;       //инициализация процесса

                try
                {
                    newProcess.Start();                 //запуск процесса
                    //вывод сообщения об успешном запуске процесса
                    Console.WriteLine(
                        "{0} for file {1} started successfully with verb \"{2}\"!",
                        newProcess.ProcessName, fileName, startInfo.Verb);
                }
                catch (System.ComponentModel.Win32Exception e)
                {
                    Console.WriteLine("  Win32Exception caught!");  //сообщения об ошибке
                    Console.WriteLine("  Win32 error = {0}",
                        e.Message);
                }
                catch (System.InvalidOperationException)
                {
                    // Catch this exception if the process exits quickly, 
                    // and the properties are not accessible.
                    //сообщения об ошибке
                    Console.WriteLine("File {0} started with verb {1} and the properties did not accessible",
                        fileName, verbToUse);
                }
            }
        }
    }
}
