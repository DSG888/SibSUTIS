using System;
using System.Diagnostics;

/*
 Получение сведений об интенсивности использования памяти процессом
1 Привяжите экземпляр компонента процесса к процессу. Дополнительные сведения см. в разделе 
    Практическое руководство. Привязка к существующим процессам. 

2 Если кэш свойств нуждается в обновлении, вызовите метод Refresh. Дополнительные сведения см. в 
    разделе Практическое руководство. Обновление свойств компонента Process. 

3 Считайте необходимое свойство интенсивности использования памяти с помощью ссылки на 
    соответствующее свойство.
 
 В следующем примере показано использование компонента Process для чтения свойства 
    PrivateMemorySize64 блокнота и назначения возвращенного значения свойства NotepadMemory. 
    Значение затем отображается на консоли. Так как Component1(0) – это новый экземпляр компонента 
    Process, кэш свойства не нуждается в обновлении. 

*/

namespace Memory
{
    class Program
    {
        static void Main(string[] args)
        {
            long memory;
            string paf = "d:\\labC#\\151\\console1";
            string fileName = "console1";
            Process myProcess = new Process();
            myProcess.StartInfo.FileName = paf;
            //myProcess.StartInfo.WindowStyle = ProcessWindowStyle.Maximized;
            myProcess.StartInfo.Arguments = "qwe rtyu iopas dfghjk";
            myProcess.Start();

            //Process[] notepads;
            Process[] values;
            //notepads = Process.GetProcessesByName("Notepad.exe");
            //notepads = Process.GetProcessesByName(fileName);
            values = Process.GetProcessesByName(fileName);
            //memory = notepads[0].PrivateMemorySize64;
            //int count = values.Length;
            memory = values[0].PrivateMemorySize64;
            Console.WriteLine("Memory used: {0}.", memory);
            //Console.WriteLine("Element count: {0}.", count);
            Console.ReadLine();
        }
    }
}
