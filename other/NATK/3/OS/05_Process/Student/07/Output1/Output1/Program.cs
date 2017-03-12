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
            string fileName = "";   //имя файла
            string arguments = "";  //аргументы, для запуска файла из командной строки
            ProcessStartInfo startInfo = new ProcessStartInfo();    //создание класса для запуска процесса
            OpenFileDialog openFileDialog1 = new OpenFileDialog();  //создание класса диалога

            //определение каталога
            openFileDialog1.InitialDirectory = "d:\\labC#\\151\\";
            //определение возможного списка выбираемых файлов
            openFileDialog1.Filter = "exe files (*.exe)|*.exe";
            openFileDialog1.FilterIndex = 1;    //индекс фильтра диалогового окна
            //восстановление текущего каталога перед закрытием окна диалога
            openFileDialog1.RestoreDirectory = true;

            //выбор файла в заданном каталоге с помощью диалогового окна
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                if ((fileName = openFileDialog1.FileName) == null)
                {
                    Console.WriteLine("Не задано имя файла");
                    Console.ReadLine();
                    return;
                }
                Console.Write("Введите параметры: ");  //вывод приглашения о вводе параметров
                arguments = Console.ReadLine();         //ввод параметров



                Process myProcess = new Process();
                //ProcessStartInfo myProcessStartInfo = new ProcessStartInfo("Process_StandardOutput_Sample.exe");
                //ProcessStartInfo myProcessStartInfo = new ProcessStartInfo("c:\\laptev\\labC#\\15\\console1.exe", "qwe rtyu iop[] asdfghjkl");
                ProcessStartInfo myProcessStartInfo = new ProcessStartInfo(fileName, arguments);
                myProcessStartInfo.UseShellExecute = false;
                myProcessStartInfo.RedirectStandardOutput = true;
                myProcess.StartInfo = myProcessStartInfo;
                myProcess.Start();

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
}
