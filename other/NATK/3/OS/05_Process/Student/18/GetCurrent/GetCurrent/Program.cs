/*
В следующем примере извлекаются сведения о текущем процессе, о всех экземплярах программы "Блокнот", 
  запущенных на локальном компьютере, о всех экземплярах программы "Блокнот", запущенных на заданном 
  компьютере (с использованием псевдонима и IP-адреса), о всех процессах, выполняемых на локальном и 
  удаленном компьютерах, о заданном процессе на локальном или удаленном компьютере (с использованием 
  идентификатора процесса).

*/
using System;
using System.Diagnostics;
using System.ComponentModel;

namespace MyProcessSample
{
    /// <summary>
    /// Shell for the sample.
    /// </summary>
    class MyProcess
    {



        void BindToRunningProcesses()
        {
            // Get the current process.
            Process currentProcess = Process.GetCurrentProcess();


            // Get all instances of Notepad running on the local
            // computer.
            Process[] localByName = Process.GetProcessesByName("notepad");
            int cnt = 0;
            foreach (Process proc in localByName)
            {
                Console.WriteLine("ProcessId {0}, {1}", proc.Id, cnt++);
            }


            // Get all instances of Notepad running on the specifiec
            // computer.
            // 1. Using the computer alias (do not precede with "\\").
            //Process[] remoteByName = Process.GetProcessesByName("notepad", "myComputer");

            // 2. Using an IP address to specify the machineName parameter. 
            //Process[] ipByName = Process.GetProcessesByName("notepad", "169.0.0.0");


            // Get all processes running on the local computer.
            Process[] localAll = Process.GetProcesses();
            cnt = 0;
            foreach (Process proc in localAll)
            {
                Console.WriteLine("{0}, ProcessId {1}", cnt++, proc.Id);
            }


            // Get all processes running on the remote computer.
            //Process[] remoteAll = Process.GetProcesses("myComputer");


            // Get a process on the local computer, using the process id.
            //Process localById = Process.GetProcessById(1234);


            // Get a process on a remote computer, using the process id.
            //Process remoteById = Process.GetProcessById(2345, "myComputer");
            Console.ReadLine();

        }



        static void Main()
        {

            MyProcess myProcess = new MyProcess();


            myProcess.BindToRunningProcesses();

        }
    }
}