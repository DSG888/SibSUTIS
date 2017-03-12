using System;
using System.Threading;
using System.IO;
using System.Diagnostics;
using System.Text;
using System.Windows.Forms;

/*
В следующем примере запускается экземпляр программы "console1.exe". Затем он извлекает использование 
    физической памяти связанного процесса с 2-секундным интервалом максимум для 10 секунд. В примере 
    отслеживается завершение работы процесса по истечении 10 секунд. В примере процесс закрывается, 
 если его выполнение продолжается по истечение 10 секунд.
*/

namespace Process_Sample
{
    class MyProcessClass
    {
        [STAThread]
        public static void Main()
        {
            try
            {
                Process myProcess;

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
                    myProcess = new Process();     //создание нового процесса
                    //newProcess.StartInfo = startInfo;       //инициализация процесса
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
                //}                //myProcess = Process.Start("c:\\laptev\\labC#\\151\\console1.exe", "qwe rty uiop asdf ghjkl");
                // Display physical memory usage 5 times at intervals of 2 seconds.
                for (int i = 0; i < 5; i++)
                {
                    if (!myProcess.HasExited)
                    {
                        // Discard cached information about the process.
                        myProcess.Refresh();
                        // Print working set to console.
                        Console.WriteLine("Physical Memory Usage: "
                                             + myProcess.WorkingSet.ToString());
                        // Wait 2 seconds.
                        Thread.Sleep(2000);
                    }
                    else
                    {
                        break;
                    }
                }

                // Close process by sending a close message to its main window.
                myProcess.CloseMainWindow();
                // Free resources associated with process.
                myProcess.Close();

            }
            catch (Exception e)
            {
                Console.WriteLine("The following exception was raised: ");
                Console.WriteLine(e.Message);
            }
        }
    }
}