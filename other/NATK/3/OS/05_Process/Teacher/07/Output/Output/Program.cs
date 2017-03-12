using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;

/*
 Следующий пример порождает новый исполняемый файл, определенный пользователем и считывает его 
    стандартный вывод. Вывод затем отображается в консоли.
*/

namespace Output
{
    class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            //Process myProcess = new Process();
            Process myProcess = new Process();

            string fileName = "";   //имя файла
            string arguments = "";  //аргументы, для запуска файла из командной строки
            string verbToUse = "";  //какие действия можно производить с заданным файлом
            ProcessStartInfo startInfo = new ProcessStartInfo();    //создание класса для запуска процесса
            OpenFileDialog openFileDialog1 = new OpenFileDialog();  //создание класса диалога

            //определение каталога
            openFileDialog1.InitialDirectory = "c:\\laptev\\labC#\\151\\";
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
            }
                //Process newProcess = new Process();     //создание нового процесса
                myProcess.StartInfo = startInfo;       //инициализация процесса

                try
                {
                    myProcess.Start();                 //запуск процесса
                    //вывод сообщения об успешном запуске процесса
                    Console.WriteLine(
                        "{0} for file {1} started successfully with verb \"{2}\"!",
                        myProcess.ProcessName, fileName, startInfo.Verb);
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
            //}
            //ProcessStartInfo myProcessStartInfo = new ProcessStartInfo("Process_StandardOutput_Sample.exe");
                //ProcessStartInfo myProcessStartInfo = new ProcessStartInfo("c:\\laptev\\labC#\\151\\console1.exe", "qwe rtyu iop[] asdfghjkl");
                ProcessStartInfo myProcessStartInfo = new ProcessStartInfo(fileName, arguments);   
            myProcessStartInfo.UseShellExecute = false;
                myProcessStartInfo.RedirectStandardOutput = true;
                //myProcess.StartInfo = myProcessStartInfo;
                //myProcess.Start();

                StreamReader myStreamReader = myProcess.StandardOutput;
                // Read the standard output of the spawned process.
                for (; ; )
                {
                    string myString = myStreamReader.ReadLine();
                    if (myString == "" || myString.Length == 39) break;
                    Console.WriteLine("{0}, размер {1}", myString, myString.Length);
                    // 39 - олределено путём распечатки myString.Length
                }
                myStreamReader.Close();
                //myProcess.WaitForExit();
                //Console.WriteLine("Process Close");
                //Console.ReadLine();
                myProcess.Close();
        }
    }
}
