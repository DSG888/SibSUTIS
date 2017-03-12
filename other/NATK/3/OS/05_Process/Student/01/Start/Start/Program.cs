using System;
using System.IO;
using System.Text;
using System.Diagnostics;
/*
 Компонент Process может использоваться для запуска процессов в системе путем вызова метода Start. 
 Перед запуском метода Start необходимо задать имя файла процесса для запуска, установив в качестве 
 свойства FileName либо полный путь к конечному процессу, либо имя процесса (для удовлетворяющих 
 данному условию приложений Windows, таких как Блокнот).

Свойство FileName можно установить во время разработки в окне Свойства или во время выполнения, 
 используя значение свойства. StartInfo. Если имя файла устанавливается во время выполнения, можно 
 предпринять одно из следующих действий: 

- Задайте для свойства StartInfo соответствующее значение и вызовите метод Start или
- вызовите форму Shared метода Start и задайте имя файла в качестве параметра. Используйте этот метод, 
 когда не требуется задавать никаких других начальных параметров запуска. Этот метод не позволяет 
 задавать никакие другие аргументы открытия. 

Запуск процесса во время выполнения с помощью свойств StartInfo
1 Установите параметры запуска, предоставляемые свойством StartInfo.

2 Вызовите метод Start компонента Process. 

*/

namespace Start
{
    class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            Process myProcess = new Process();
            //myProcess.StartInfo.FileName = "Notepad";
            myProcess.StartInfo.FileName = "d:\\labC#\\151\\console1.exe";
            //myProcess.StartInfo.WindowStyle = ProcessWindowStyle.Maximized;
            myProcess.StartInfo.Arguments = "qwe rtyu iopas dfghjk";
            myProcess.Start();
        }
    }
}
