using System;
using System.Diagnostics;
using System.Threading;

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
        public static void Main()
        {
            try
            {
                Process myProcess;
                myProcess = Process.Start("d:\\labC#\\151\\console1.exe", "qwe rty uiop asdf ghjkl");
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