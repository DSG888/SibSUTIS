using System;
using System.IO;
using System.Diagnostics;
using System.Text;
using System.Windows.Forms;

/*
 Получение сведений об интенсивности использования памяти процессом
1 Привяжите экземпляр компонента процесса к процессу. Дополнительные сведения см. в разделе 
    Практическое руководство. Привязка к существующим процессам. 

2 Если кэш свойств нуждается в обновлении, вызовите метод Refresh. Дополнительные сведения см. в 
    разделе Практическое руководство. Обновление свойств компонента Process. 

3 Считайте необходимое свойство интенсивности использования памяти с помощью ссылки на 
    соответствующее свойство.
 
 В следующем примере показано использование компонента Process для чтения свойства 
    PrivateMemorySize64 блокнота и назначения возвращенного значения свойства NotepadMemory. 
    Значение затем отображается на консоли. Так как Component1(0) – это новый экземпляр компонента 
    Process, кэш свойства не нуждается в обновлении. 

*/

namespace Memory
{
    class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            long memory;
            //string paf = "c:\\laptev\\labC#\\151\\console1";
            //string fileName = "console1";
            //Process myProcess = new Process();
            //myProcess.StartInfo.FileName = paf;
            //myProcess.StartInfo.WindowStyle = ProcessWindowStyle.Maximized;
            //myProcess.StartInfo.Arguments = "qwe rtyu iopas dfghjk";
            //myProcess.Start();

            string fn = "";


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

                //заданный файл испоьзовать для выполнения
                //startInfo.Verb = "runas";

                Console.Write("Enter the parameter:");  //вывод приглашения о вводе параметров
                arguments = Console.ReadLine();         //ввод параметров
                startInfo.Arguments = arguments;        //передача параметров
            }
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
            //}
            //Process[] notepads;
            Process[] values;
            //notepads = Process.GetProcessesByName("Notepad.exe");
            //notepads = Process.GetProcessesByName(fileName);
            values = Process.GetProcessesByName(fn);
            //memory = notepads[0].PrivateMemorySize64;
            //int count = values.Length;
            memory = values[0].PrivateMemorySize64;
            Console.WriteLine("Memory used: {0}.", memory);
            //Console.WriteLine("Element count: {0}.", count);
            Console.ReadLine();
        }
    }
}
