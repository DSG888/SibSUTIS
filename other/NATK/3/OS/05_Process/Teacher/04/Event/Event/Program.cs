using System;
using System.IO;
using System.Text;
using System.Diagnostics;
using System.ComponentModel;
using System.Threading;
using Microsoft.VisualBasic;
using System.Windows.Forms;
/*
В следующем примере кода создается процесс, Свойству EnableRaisingEvents задается побуждение 
    процесса к возникновению события Exited при его завершении. Обработчик событий Exited отображает 
    информацию о процессе.
*/


class EventProcessClass
{

    private Process myProcess = new Process();
    private int elapsedTime;
    private bool eventHandled;

    // Print a file with any known extension.
    public void Event(string fileName, string args)
    {

        elapsedTime = 0;
        eventHandled = false;

        try
        {
            // Start a process to print a file and raise an event when done.
            myProcess.StartInfo.FileName = fileName;
            myProcess.StartInfo.Verb = "runas";
            //myProcess.StartInfo.Arguments = "qwe rty uiop asdf ghjkl";
            myProcess.StartInfo.Arguments = args;
            myProcess.StartInfo.CreateNoWindow = true;
            myProcess.EnableRaisingEvents = true;
            myProcess.Exited += new EventHandler(myProcess_Exited);
            myProcess.Start();

        }
        catch (Exception ex)
        {
            Console.WriteLine("An error occurred trying to print \"{0}\":" + "\n" + ex.Message, fileName);
            return;
        }

        // Wait for Exited event, but not more than 10 seconds.
        const int SLEEP_AMOUNT = 100;
        while (!eventHandled)
        {
            elapsedTime += SLEEP_AMOUNT;
            if (elapsedTime > 10000)
            {
                break;
            }
            Thread.Sleep(SLEEP_AMOUNT);
        }
    }

    // Handle Exited event and display process information.
    private void myProcess_Exited(object sender, System.EventArgs e)
    {

        eventHandled = true;
        Console.WriteLine("Exit time:    {0}\r\n" +
            "Exit code:    {1}\r\nElapsed time: {2}", myProcess.ExitTime, myProcess.ExitCode, elapsedTime);
    }

    [STAThread]
    public static void Main(string[] args)
    {

        string fileName = "";   //имя файла
        string arguments = "";  //аргументы, для запуска файла из командной строки

        // Verify that an argument has been entered.
/*
        if (args.Length <= 0)
        {
            Console.WriteLine("Enter a file name.");
            return;
        }
*/
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

        // Create the process and print the document.
        EventProcessClass myProcess = new EventProcessClass();
        //myProcess.Event(args[0]);
        myProcess.Event(fileName, arguments);
    }
}