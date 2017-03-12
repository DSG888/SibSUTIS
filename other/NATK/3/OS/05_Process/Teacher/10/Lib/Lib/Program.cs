using System;
using System.Collections.Generic;
using System.Linq;
using System.Diagnostics;
using System.IO;
using System.Text;
using System.Windows.Forms;

/*
 Свойство Modules компонента Process предоставляет доступ к загруженным библиотекам для процесса. 
    Свойство Modules возвращает коллекцию типа ProcessModuleCollection, которая включает все 
    загруженные библиотеки для конечного процесса. Впоследствии можно повторить те же действия для 
    всей коллекции, чтобы просмотреть свойства каждой отдельной библиотеки.

Получение сведений об использовании библиотек для процесса 
1 Если конечный процесс был запущен без использования компонента Process, свяжите новый экземпляр 
    компонента Process с процессом. Дополнительные сведения см. в разделе Практическое руководство. 
    Привязка к существующим процессам. 

2 Объявите объект типа ProcessModuleCollection для хранения коллекции модуля.

3 Присвойте свойство Modules переменной ProcessModuleCollection. Это действие заполнит объект 
    ProcessModuleCollection модулями из конечного модуля.

4 Повторите те же действия для всего объекта ProcessModuleCollection для просмотра отдельных 
    библиотек и управления ими. 

В следующем примере показан способ возврата всех загруженных библиотек для Microsoft Word и 
    отображения элементов в объекте ListBox: 
*/

namespace Lib
{
    class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            //string paf = "c:\\laptev\\labC#\\151\\console1";
            //string fileName = "console1";
            //string paf = "WinWord";
            //string fileName = paf;

            string fn = "";

            //Process myProcess = new Process();
            //myProcess.StartInfo.FileName = paf;
            //myProcess.StartInfo.Arguments = "qwer sdfg ghjkl";
            //myProcess.Start();
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


            System.Threading.Thread.Sleep(3000);

            Process[] wordapps;
            ProcessModuleCollection modules;
            wordapps = Process.GetProcessesByName(fn);
            // Populate the module collection.
            //int cnt=wordapps.Count();
            modules = wordapps[0].Modules;
            // Iterate through the module collection.

            foreach (ProcessModule aModule in modules)
            {
                Console.WriteLine(aModule.ModuleName);
            }

            //Console.WriteLine("Count = {0}", cnt);
            Console.ReadLine();
        }
    }
}
