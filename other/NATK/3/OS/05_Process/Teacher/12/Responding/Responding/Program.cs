using System;
using System.Diagnostics;
using System.Reflection;
using System.IO;
using System.Text;
using System.Windows.Forms;

/*
 Свойство Responding позволяет определить, отвечает ли пользовательский интерфейс процесса на запросы. 
    При попытке чтения свойства Responding пользовательскому интерфейсу соответствующего процесса 
    отправляется запрос. При получении немедленного ответа свойство возвращает значение true; а если 
    отклика от интерфейса нет, возвращается значение false. Это свойство используется в том случае, 
    когда необходимо принудительно закрыть зависшее приложение.

Проверка отклика процесса
1 Если процесс не был запущен при помощи компонента Process, свяжите его с соответствующим процессом. 
    Дополнительные сведения см. в разделе Практическое руководство. Привязка к существующим процессам.

2 Просмотрите значение свойства Responding.

3 Определите порядок действий в зависимости от значения свойства. 

В следующем примере показано, как определить, отвечает ли программа Блокнот на запросы. Если свойство 
    Responding имеет значение true, вызовите метод CloseMainWindow, чтобы закрыть приложение. Если 
    свойство Responding имеет значение false, для принудительного завершения процесса используется 
    метод M:System.Diagnostics.Process.Kill. 
*/

namespace Responding
{
    class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            //string paf = "c:\\laptev\\labC#\\151\\console1";
            //string fileName = "console1";

            Process myProcess = new Process();
            //myProcess.StartInfo.FileName = paf;
            //myProcess.StartInfo.WindowStyle = ProcessWindowStyle.Maximized;
            //myProcess.StartInfo.Arguments = "qwe rtyu iopas dfghjk";

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

            myProcess.StartInfo.FileName = fileName;
            myProcess.StartInfo.Arguments = arguments;
       
            myProcess.Start();
            myProcess.Start();
            myProcess.Start();
            System.Threading.Thread.Sleep(3000);

            Process[] localByName;
            //localByName = Process.GetProcessesByName("notepad.exe");
            localByName = Process.GetProcessesByName(fn);
            //int count = localByName.Rank;
            //Console.WriteLine("count = {0}", count);
            // Test to see if the process is responding.
            //int cnt = localByName.GetLength(0);
            int cnt = localByName.Length;
            Console.WriteLine("Instance number of {0}", cnt);

            cnt = 0;
            foreach (Process proc in localByName)
            {
                if (proc.Responding)
                {
                    Console.WriteLine("ProcessId {0}, {1} closed", proc.Id, cnt++);
                    proc.CloseMainWindow();
                }
                else
                {
                    Console.WriteLine("ProcessId {0}, {1} killed", proc.Id, cnt++);
                    proc.Kill();
                }
            }
            Console.ReadKey();
            /*            
                        if (localByName[0].Responding)
                        {
                            localByName[0].CloseMainWindow();
                        }
                        else
                        {
                            localByName[0].Kill();
                        }
            */
        }
    }
}
