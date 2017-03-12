using System;
using System.IO;
using System.Text;
using System.Diagnostics;
using System.ComponentModel;
using System.Windows.Forms;

/*
 Следующий пример задает значение свойства StartInfo файлом для выполнения, действия, производимые 
    над ним, и необходимость отображения пользовательского интерфейса.
*/

namespace MyProcessSample
{
    /// <summary>
    /// Shell for the sample.
    /// </summary>
    class MyProcess
    {
        // These are the Win32 error code for file not found or access denied.
        const int ERROR_FILE_NOT_FOUND = 2;
        const int ERROR_ACCESS_DENIED = 5;

        /// <summary>
        /// Prints a file with a .doc extension.
        /// </summary>
        void Start()
        {
            //Process myProcess = new Process();
            Process newProcess = new Process();

            try
            {
                // Get the path that stores user documents.
                //string myDocumentsPath =
                //  Environment.GetFolderPath(Environment.SpecialFolder.Personal);

                //myProcess.StartInfo.FileName = myDocumentsPath + "c:\\laptev\\labC#\\15\\Console1.exe";
                //myProcess.StartInfo.FileName = "c:\\laptev\\labC#\\151\\Console1.exe";
                //myProcess.StartInfo.Verb = "runas";
                //myProcess.StartInfo.Arguments = "sdfghjk";
                //myProcess.StartInfo.CreateNoWindow = true;
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
                }
                //Process newProcess = new Process();     //создание нового процесса
                newProcess.StartInfo = startInfo;       //инициализация процесса
                newProcess.Start();                 //запуск процесса
                //вывод сообщения об успешном запуске процесса
                Console.WriteLine(
                    "{0} for file {1} started successfully with verb \"{2}\"!",
                    newProcess.ProcessName, fileName, startInfo.Verb);
                
            }
            catch (Win32Exception e)
            {
                if (e.NativeErrorCode == ERROR_FILE_NOT_FOUND)
                {
                    Console.WriteLine(e.Message + ". Check the path.");
                }

                else if (e.NativeErrorCode == ERROR_ACCESS_DENIED)
                {
                    // Note that if your word processor might generate exceptions
                    // such as this, which are handled first.
                    Console.WriteLine(e.Message +
                        ". You do not have permission to exec this file.");
                }
            }
        }


        [STAThread]
        public static void Main()
        {
            MyProcess myProcess = new MyProcess();
            myProcess.Start();
        }
    }
}