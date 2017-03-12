using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.IO;

/*
 Следующий пример порождает новый исполняемый файл, определенный пользователем и считывает его 
    стандартный вывод. Вывод затем отображается в консоли.
*/

namespace Output
{
    class Program
    {
        static void Main(string[] args)
        {
                Process myProcess = new Process();
                //ProcessStartInfo myProcessStartInfo = new ProcessStartInfo("Process_StandardOutput_Sample.exe");
                ProcessStartInfo myProcessStartInfo = new ProcessStartInfo("d:\\labC#\\151\\console1.exe", "qwe rtyu iop[] asdfghjkl");
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
