using System;
using System.Diagnostics;
using System.Reflection;

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
        static void Main(string[] args)
        {
            string paf = "d:\\labC#\\151\\console1";
            string fileName = "console1";

            Process myProcess = new Process();
            myProcess.StartInfo.FileName = paf;
            //myProcess.StartInfo.WindowStyle = ProcessWindowStyle.Maximized;
            myProcess.StartInfo.Arguments = "qwe rtyu iopas dfghjk";
            myProcess.Start();
            myProcess.Start();
            myProcess.Start();
            System.Threading.Thread.Sleep(3000);

            Process[] localByName;
            //localByName = Process.GetProcessesByName("notepad.exe");
            localByName = Process.GetProcessesByName(fileName);
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
