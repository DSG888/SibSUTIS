using System;
using System.IO;
using System.Diagnostics;
using System.Text;
using System.Windows.Forms;

namespace CreateNewProcess
{
    class Class1
    {
        [STAThread]
        static void Main(string[] args)
        {

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
                //startInfo = new ProcessStartInfo(fileName);

            }

            //заданный файл испоьзовать для выполнения
            //startInfo.Verb = "runas";

            Console.Write("Enter the parameter:");  //вывод приглашения о вводе параметров
            arguments = Console.ReadLine();         //ввод параметров
            //startInfo.Arguments = arguments;        //передача параметров
        }
            //Process newProcess = new Process();     //создание нового процесса
            //newProcess.StartInfo = startInfo;       //инициализация процесса

            // Создать новый процесс
            System.Diagnostics.Process proc = new System.Diagnostics.Process();
            // Приложение которое будем запускать
            //proc.StartInfo.FileName = "c:\\laptev\\labC#\\151\\console1";
            proc.StartInfo.FileName = fileName;
            //proc.StartInfo.Arguments = "qwer tyuiop asdfghjkl";
            proc.StartInfo.Arguments = arguments;
            proc.EnableRaisingEvents = true;
            proc.Exited += new EventHandler(proc_Exited);
            proc.Start();

            Console.ReadLine();
        }

        // Будет вызываться при завершении процесса
        private static void proc_Exited(object sender, EventArgs e)
        {
            Console.WriteLine("proc_Exited");
        }
    }
}
