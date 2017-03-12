using System;
using System.IO;

class Test 
{
    public static void Main(string[] args) 
    {
//        string path = @"c:\temp\MyTest.txt";
//        string path = @"MyTest.txt";
        Console.WriteLine("Создание нового каталога.");
        Console.WriteLine("Копирование заданного файла из текущего каталога в заданный новый каталог.");
        Console.WriteLine("Перемещение скопированного файла обратно, но с другим именем.");
//        Console.WriteLine("Переименование созданного каталога и установка атрибута скопированного файла только для чтения.");
        Console.WriteLine("Удалениение созданного каталога и перемещённого файла.");
        // If a directory is not specified, exit program.
        if(args.Length != 3)
        {
            // Display the proper way to call the program.
            Console.WriteLine("Используйте: prog.exe (имя каталога) (имя файла) (имя перемещаемого файла)");
            return;
        }
	if (Directory.Exists(args[0]))
	{
            Console.WriteLine("Заданный новый каталог {0} уже существует", args[0]);
            return;
	}
	if (!File.Exists(args[1]))
	{
            Console.WriteLine("Заданный файл {0} для копирования не существует", args[1]);
            return;
	}
//	if (Directory.Exists(args[2]))
//	{
//            Console.WriteLine("Заданный каталог {0} для переименования уже существует", args[2]);
//            return;
//	}
	if (File.Exists(args[2]))
	{
            Console.WriteLine("Заданный файл {0} для перемещения уже существует", args[2]);
            return;
	}
/*
        if (!File.Exists(path)) 
        {
            // Create a file to write to.
            using (StreamWriter sw = File.CreateText(path)) 
            {
                sw.WriteLine("Hello");
                sw.WriteLine("And");
                sw.WriteLine("Welcome");
            }	
        }

        // Open the file to read from.
        using (StreamReader sr = File.OpenText(path)) 
        {
            string s = "";
            while ((s = sr.ReadLine()) != null) 
            {
                Console.WriteLine(s);
            }
        }
*/
        try 
        {
//            string path2 = path + "temp";
            // Ensure that the target does not exist.
///            File.Delete(path2);

	    //Создать каталог
	    Directory.CreateDirectory(args[0]);
            Console.WriteLine("Новый каталог {0} успешно создан.", args[0]);

            //Копировать файл
	    string path = args[0] + "\\" + args[1];
            File.Copy(args[1], path);
            Console.WriteLine("Файл {0} в каталог {1} успешно скопирован.", args[1], args[0]);

	    //Перемещение файла
	    File.Move(path, args[2]);   
            Console.WriteLine("Скопированный файл {0} перемещён в текущий каталог, но с именеи {1}.", args[1], args[2]);

	    //Переименование каталога
//	    Directory.Move(args[0], args[2]);
//          Console.WriteLine("Каталог {0} переименован в каталог {1}.", args[0], args[2]);

	    //Установмть атрибут файла только для чтения
//	    File.SetAttributes(args[3], FileAttributes.ReadOnly);
//	    FileAttributes fa = File.GetAttributes(args[3]);
//          Console.WriteLine("Атрибут файла {0} установлен только для чтения {1}.", args[3], fa);
	
	    //Удалить каталог
	    Directory.Delete(args[0]);
            Console.WriteLine("Каталог {0} успешно удалён.", args[0]);

	    //Установмть атрибут файла нормальный
//	    File.SetAttributes(args[3], FileAttributes.Normal);
//	    fa = File.GetAttributes(args[3]);
//          Console.WriteLine("Атрибут файла {0} установлен нормальный {1}.", args[3], fa);
	
	    //Удалить файл
	    File.Delete(args[2]);
            Console.WriteLine("Файл {0} успешно удалён.", args[2]);
/*
	FileAttributes fa = File.GetAttributes(path2);
        Console.WriteLine("Атрибуты файла {0}: {1}", path2, fa);
	    File.SetAttributes(path2, FileAttributes.Normal);
	fa = File.GetAttributes(path2);
        Console.WriteLine("Атрибуты файла {0}: {1}", path2, fa);

            // Delete the newly created file.
            File.Delete(path2);
            Console.WriteLine("{0} was successfully deleted.", path2);
*/
        } 
        catch (Exception e)                 
        {
            Console.WriteLine("The process failed: {0}", e.ToString());
        }
/*
        catch (UnauthorizedAccessException e)                  
        {
            Console.WriteLine("The process failed: {0}", e.ToString());
        }
*/
    }
}