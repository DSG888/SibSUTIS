using System;
using System.Collections.Generic;
using System.Linq;
using System.Diagnostics;
using System.IO;
using System.Text;
using System.Windows.Forms;

/*
 Обновление свойств компонента Process
1 Создайте экземпляр процесса программно или путем добавления компонента Process к проекту в режиме 
    разработки. Дополнительные сведения см. в разделе Практическое руководство. Привязка к существующим 
    процессам.

2 Если перед извлечением сведений о свойствах произошли какие-либо изменения в свойствах процесса, 
    вызовите метод Refresh.

3 Установите свойства для чтения соответствующих сведений о процессе и назначьте возвращенное значение 
    для переменной. 

В следующем примере показано, как открыть экземпляр блокнота и затем вызвать метод Refresh для 
    обновления свойств компонента. Затем код считывает обновленное свойство WorkingSet64 компонента, 
    чтобы возвратить общий объем памяти для связанного процесса. Обновленное значение свойства затем 
    отображается на экране консоли 6 раз с двухсекундным интервалом. После завершения процедуры консоль 
    остается открытой пять секунд.
*/

namespace Property
{
    class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            Process notepad;
            ProcessStartInfo startinfo = new ProcessStartInfo();
            //startinfo.FileName = "c:\\laptev\\labC#\\151\\Console1";
            //startinfo.Arguments = "qwer sdfg ghjkl";

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

                Console.Write("Enter the parameter:");  //вывод приглашения о вводе параметров
                arguments = Console.ReadLine();         //ввод параметров
                startInfo.Arguments = arguments;        //передача параметров
            }
                //Process newProcess = new Process();     //создание нового процесса
                //newProcess.StartInfo = startInfo;       //инициализация процесса
/*
                try
                {
                    //newProcess.Start();                 //запуск процесса
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
*/
            startinfo.FileName = fileName;
            startinfo.Arguments = arguments;

            notepad = Process.Start(startinfo);
            for (int i = 0; i < 5; i++)
            {
                // Forces the Process component to get a new set 
                // of property values.
                notepad.Refresh();
                // Writes the property value to the console screen.
                Console.WriteLine(notepad.WorkingSet64.ToString());
                // Waits two seconds before running the next loop.
                System.Threading.Thread.Sleep(2000);
            }
            // Closes Notepad and waits 5 seconds before closing 
            // the console screen.
            notepad.CloseMainWindow();
            System.Threading.Thread.Sleep(5000);
        }
    }
}
