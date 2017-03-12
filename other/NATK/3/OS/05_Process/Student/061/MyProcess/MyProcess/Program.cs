using System;
using System.Diagnostics;
using System.Windows.Forms;
/*
 В следующем примере кода запускается экземпляр программы console1.exe. Затем в данном примере 
    извлекаются и отображаются значения различных свойств связанного процесса. В данном примере 
    отслеживается завершение работы процесса, после чего отображается его код завершения и статистика 
    использования памяти.
*/

namespace ProcessSample
{
    class ProcessMonitorSample
    {
        [STAThread]
        public static void Main()
        {

            // Define variables to track the peak
            // memory usage of the process.
            long peakPagedMem = 0,
                peakWorkingSet = 0,
                peakVirtualMem = 0;


        string fileName = "";   //имя файла
        string arguments = "";  //аргументы, для запуска файла из командной строки
        string verbToUse = "";  //какие действия можно производить с заданным файлом
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

            Process myProcess = new Process();     //создание нового процесса
            myProcess.StartInfo = startInfo;       //инициализация процесса


            //\\Process myProcess = null;

            try
            {
                // Start the process.
                //myProcess = Process.Start("NotePad.exe");
                //\\myProcess = Process.Start("c:\\laptev\\labC#\\15\\console1.exe", "sdfghj dert 1234");
                myProcess.Start();

                // Display the process statistics until
                // the user closes the program.
                do
                {
                    if (!myProcess.HasExited)
                    {
                        // Refresh the current process property values.
                        myProcess.Refresh();

                        Console.WriteLine();

                        // Display current process statistics.

                        Console.WriteLine("{0} -", myProcess.ToString());
                        Console.WriteLine("-------------------------------------");

                        Console.WriteLine("  physical memory usage: {0}",
                            myProcess.WorkingSet64);
                        Console.WriteLine("  base priority: {0}",
                            myProcess.BasePriority);
                        Console.WriteLine("  priority class: {0}",
                            myProcess.PriorityClass);
                        Console.WriteLine("  user processor time: {0}",
                            myProcess.UserProcessorTime);
                        Console.WriteLine("  privileged processor time: {0}",
                            myProcess.PrivilegedProcessorTime);
                        Console.WriteLine("  total processor time: {0}",
                            myProcess.TotalProcessorTime);

                        // Update the values for the overall peak memory statistics.
                        peakPagedMem = myProcess.PeakPagedMemorySize64;
                        peakVirtualMem = myProcess.PeakVirtualMemorySize64;
                        peakWorkingSet = myProcess.PeakWorkingSet64;

                        if (myProcess.Responding)
                        {
                            Console.WriteLine("Status = Running");
                        }
                        else
                        {
                            Console.WriteLine("Status = Not Responding");
                        }
                    }
                }
                while (!myProcess.WaitForExit(1000));


                Console.WriteLine();
                Console.WriteLine("Process exit code: {0}",
                    myProcess.ExitCode);

                // Display peak memory statistics for the process.
                Console.WriteLine("Peak physical memory usage of the process: {0}",
                    peakWorkingSet);
                Console.WriteLine("Peak paged memory usage of the process: {0}",
                    peakPagedMem);
                Console.WriteLine("Peak virtual memory usage of the process: {0}",
                    peakVirtualMem);
                Console.ReadLine();
            }
            finally
            {
                if (myProcess != null)
                {
                    myProcess.Close();
                }
            }
        }

        }

    }
}
