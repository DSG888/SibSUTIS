using System;
using System.IO;
using System.Text;

namespace Lab10
{
    class Program
    {
        static void Main(string[] args)
        {
            // Проверки
            if(args.Length != 2)
            {
        		//Сообщение об ошибке, если количество параметров не равно 2
                Console.ReadLine();
                return;
            }

        	if (!Directory.Exists(args[0]))	//!File.Exists(args[0]))
	        {
        		//Сообщение об ошибке, если каталог(или файл)(1-ый параметр) не существует 
                Console.ReadLine();
                return;
            }
            try
            {
                //Основной алгоритм
                Console.ReadLine();
            }
            catch (Exception e)
            {
                Console.WriteLine("Процесс был прерван из-за: {0}", e.ToString());
                Console.ReadLine();
            }
        }
    }
}
