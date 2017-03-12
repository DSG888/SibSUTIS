using System;
using System.Diagnostics;

/*
 Ð' Ñ_Ð>Ð÷Ð_Ñ_Ñ_Ñ%Ð÷Ð_ Ð¿Ñ_Ð¸Ð_Ð÷Ñ_Ð÷ Ð_Ð÷Ð_Ð_Ð_Ñ_Ñ'Ñ_Ð¸Ñ_Ñ_Ð÷Ñ'Ñ_Ñ_ Ð·Ð°Ð¿Ñ_Ñ_Ðº Ñ_ÐºÐ·Ð÷Ð_Ð¿Ð>Ñ_Ñ_Ð° Ð¿Ñ_Ð_Ð_Ñ_Ð°Ð_Ð_Ñ< "console1.exe" Ð¸ Ð¸Ð·Ð_Ð>Ð÷Ñ+Ð÷Ð_Ð¸Ð÷ Ð·Ð°Ð_Ð_Ð>Ð_Ð_ÐºÐ° 
    Ð_Ð>Ð°Ð_Ð_Ð_Ð_Ð_ Ð_ÐºÐ_Ð° Ð¿Ñ_Ð_Ñ+Ð÷Ñ_Ñ_Ð°.
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