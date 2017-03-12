using System;
using System.Diagnostics;
using System.Text;
using System.IO;
using System.Windows.Forms;

/*
 В следующем примере кода демонстрируется использование класса ProcessModule для получения и 
 отображения информации обо всех модулях, используемых приложением Notepad.exe.
*/


namespace ProcessModule1
{
    class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            Process myProcess = new Process();
            //ProcessStartInfo myProcessStartInfo = new ProcessStartInfo("c:\\laptev\\labC#\\151\\console1.exe");
            // Assign 'StartInfo' of process to 'StartInfo' of 'myProcess' object.
            //myProcess.StartInfo = myProcessStartInfo;
            //myProcess.StartInfo.Arguments = "asd fgh qwerty";

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

        myProcess.StartInfo = startInfo;       //инициализация процесса

        // Get the process start information 
            // Create a process.
            myProcess.Start();
            System.Threading.Thread.Sleep(3000);
            ProcessModule myProcessModule;
            // Get all the modules associated with 'myProcess'.
            ProcessModuleCollection myProcessModuleCollection = myProcess.Modules;
            Console.WriteLine("Properties of the modules  associated "
               + "with process are:");
            // Display the properties of each of the modules.
            for (int i = 0; i < myProcessModuleCollection.Count; i++)
            {
                myProcessModule = myProcessModuleCollection[i];
                Console.WriteLine("The moduleName is "
                   + myProcessModule.ModuleName);
                Console.WriteLine("The " + myProcessModule.ModuleName + "'s base address is: "
                   + myProcessModule.BaseAddress);
                Console.WriteLine("The " + myProcessModule.ModuleName + "'s Entry point address is: "
                   + myProcessModule.EntryPointAddress);
                Console.WriteLine("The " + myProcessModule.ModuleName + "'s File name is: "
                   + myProcessModule.FileName);
            }
            // Get the main module associated with 'myProcess'.
            myProcessModule = myProcess.MainModule;
            // Display the properties of the main module.
            Console.WriteLine("The process's main moduleName is:  "
               + myProcessModule.ModuleName);
            Console.WriteLine("The process's main module's base address is: "
               + myProcessModule.BaseAddress);
            Console.WriteLine("The process's main module's Entry point address is: "
               + myProcessModule.EntryPointAddress);
            Console.WriteLine("The process's main module's File name is: "
               + myProcessModule.FileName);
            myProcess.CloseMainWindow();
            System.Threading.Thread.Sleep(3000);
        }
    }
}
