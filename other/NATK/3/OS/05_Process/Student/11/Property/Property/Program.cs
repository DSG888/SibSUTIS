using System;
using System.Collections.Generic;
using System.Linq;
using System.Diagnostics;

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
        static void Main(string[] args)
        {
            Process notepad;
            ProcessStartInfo startinfo = new ProcessStartInfo();
            startinfo.FileName = "d:\\labC#\\151\\Console1";
            startinfo.Arguments = "qwer sdfg ghjkl";
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
