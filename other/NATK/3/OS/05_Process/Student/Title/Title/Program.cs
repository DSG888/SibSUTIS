using System;
using System.Diagnostics;

/*
 В следующем примере демонстрируется запуск экземпляра программы "console1.exe" и извлечение заголовка 
    главного окна процесса.
*/

class MainWindowTitleClass
{
    public static void Main()
    {
        try
        {

            // Create an instance of process component.
            Process myProcess = new Process();
            // Create an instance of 'myProcessStartInfo'.
            ProcessStartInfo myProcessStartInfo = new ProcessStartInfo();
            myProcessStartInfo.FileName = "d:\\labC#\\151\\console1.exe";
            myProcess.StartInfo = myProcessStartInfo;
            // Start process.
            myProcess.Start();
            // Allow the process to finish starting.
            myProcess.WaitForInputIdle();
            Console.Write("Main window Title : " + myProcess.MainWindowTitle);

            myProcess.CloseMainWindow();
            myProcess.Close();
        }
        catch (Exception e)
        {
            Console.Write(" Message : " + e.Message);
        }

    }
}