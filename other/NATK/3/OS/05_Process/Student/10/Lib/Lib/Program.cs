using System;
using System.Collections.Generic;
using System.Linq;
using System.Diagnostics;

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
        static void Main(string[] args)
        {
            string paf = "d:\\labC#\\151\\console1";
            string fileName = "console1";
            //string paf = "WinWord";
            //string fileName = paf;

            Process myProcess = new Process();
            myProcess.StartInfo.FileName = paf;
            myProcess.StartInfo.Arguments = "qwer sdfg ghjkl";
            myProcess.Start();
            System.Threading.Thread.Sleep(3000);

            Process[] wordapps;
            ProcessModuleCollection modules;
            wordapps = Process.GetProcessesByName(fileName);
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
