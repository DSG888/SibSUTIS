using System;
using System.Diagnostics;
using System.Text;

/*
 В следующем примере кода демонстрируется использование класса ProcessModule для получения и 
 отображения информации обо всех модулях, используемых приложением Notepad.exe.
*/


namespace ProcessModule1
{
    class Program
    {
        static void Main(string[] args)
        {
            Process myProcess = new Process();
            // Get the process start information 
            ProcessStartInfo myProcessStartInfo = new ProcessStartInfo("d:\\labC#\\151\\console1.exe");
            // Assign 'StartInfo' of process to 'StartInfo' of 'myProcess' object.
            myProcess.StartInfo = myProcessStartInfo;
            myProcess.StartInfo.Arguments = "asd fgh qwerty";
            // Create a process.
            myProcess.Start();
            System.Threading.Thread.Sleep(1000);
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
        }
    }
}
