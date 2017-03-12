using System;
using System.Diagnostics;
using System.IO;

namespace ProcessReference
{
    class Class1
    {
        static void Main()
        {
            Process p;

            // Получаем текущий процесс
            //p = Process.GetCurrentProcess();
            p = new Process();
            p.StartInfo.FileName = "d:\\labC#\\151\\console1";
            p.StartInfo.Arguments = "asdf dfgh erty wert";
            p.Start();

            // Выводим все DLL, связанные с ним
            foreach (ProcessModule module in p.Modules)
            {
                Print(module.ModuleName, 20);
                Print(module.FileName, 75);
                Print(module.FileVersionInfo.FileVersion, 20);
                Print(File.GetLastWriteTime(module.FileName).ToShortDateString(), 20);
                Console.WriteLine();
            }
            p.Close();
            p = null;
            Console.ReadLine();
        }

        // Специальная функция форматирования строки
        static void Print(string towrite, int maxlen)
        {
            if (towrite.Length >= maxlen)
            {
                Console.Write(towrite.Substring(0, maxlen - 4) + "... ");
                return;
            }
            towrite += new string(' ', maxlen - towrite.Length);

            Console.Write(towrite);
        }
    }
}

