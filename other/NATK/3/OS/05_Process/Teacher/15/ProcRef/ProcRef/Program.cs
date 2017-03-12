using System;
using System.Diagnostics;
using System.IO;
using System.Text;
using System.Windows.Forms;

namespace ProcessReference
{
    class Class1
    {
        [STAThread]
        static void Main()
        {
            //Process p;
            Process newProcess;
            // Получаем текущий процесс
            //p = Process.GetCurrentProcess();
            //p = new Process();
            //p.StartInfo.FileName = "c:\\laptev\\labC#\\151\\console1";
            //p.StartInfo.Arguments = "asdf dfgh erty wert";
            //p.Start();
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
            newProcess = new Process();     //создание нового процесса
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
            // Выводим все DLL, связанные с ним
            foreach (ProcessModule module in newProcess.Modules)
                //foreach (ProcessModule module in p.Modules)
                {
                Print(module.ModuleName, 20);
                Print(module.FileName, 75);
                Print(module.FileVersionInfo.FileVersion, 20);
                Print(File.GetLastWriteTime(module.FileName).ToShortDateString(), 20);
                Console.WriteLine();
            }
            //p.Close();
            newProcess.Close();
            //p = null;
            newProcess = null;
            Console.ReadLine();
        }

        // Специальная функция форматирования строки
        static void Print(string towrite, int maxlen)
        {
            if (towrite.Length >= maxlen)
            {
                Console.Write(towrite.Substring(0, maxlen - 4) + "... ");
                return;
            }
            towrite += new string(' ', maxlen - towrite.Length);

            Console.Write(towrite);
        }
    }
}

