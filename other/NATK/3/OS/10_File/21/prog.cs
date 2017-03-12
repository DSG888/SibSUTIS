using System;
using System.IO;

class Test 
{
    public static void Main(string[] args) 
    {
//        string path = @"c:\temp\MyTest.txt";
//        string path = @"MyTest.txt";
        Console.WriteLine("Создание нового каталога.");
        Console.WriteLine("Создание нового файла в новом каталоге.");
        Console.WriteLine("Скопировать новый файла в новом каталоге, но с другим именеи.");
        Console.WriteLine("Переместить созданные файлы из нового каталога в текущий.");
        Console.WriteLine("Установить атрибуты перемещённых файлов только для чтения.");
        Console.WriteLine("Удалениение созданного каталога и перемещённых файлов.");
        // If a directory is not specified, exit program.
        if(args.Length != 3)
        {
            // Display the proper way to call the program.
            Console.WriteLine("Используйте: prog.exe (имя каталога) (имя файла) (имя скопированного файла)");
            return;
        }
	if (Directory.Exists(args[0]))
	{
            Console.WriteLine("Заданный новый каталог {0} уже существует", args[0]);
            return;
	}
//	string path = args[0] + '\\' + args[1];
	if (File.Exists(args[1]))
	{
            Console.WriteLine("Заданный файл {0} в текущем каталоге уже существует", args[1]);
            return;
	}
	if (File.Exists(args[2]))
	{
            Console.WriteLine("Заданный файл {0} в текущем каталоге уже существует", args[2]);
            return;
	}
//	if (Directory.Exists(args[2]))
//	{
//            Console.WriteLine("Заданный каталог {0} для переименования уже существует", args[2]);
//            return;
//	}
//	if (File.Exists(args[3]))
//	{
//            Console.WriteLine("Заданный файл {0} для перемещения уже существует", args[3]);
//            return;
//	}
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
//            File.Delete(path2);

	    //Создать каталог
	    Directory.CreateDirectory(args[0]);
            Console.WriteLine("Новый каталог {0} успешно создан.", args[0]);

	    //Создать файл для записи
	    string path = args[0] + '\\' + args[1];
            using (StreamWriter sw = File.CreateText(path)) 
            {
                sw.WriteLine("Hello");
                sw.WriteLine("And");
                sw.WriteLine("Welcome");
            }	


            //Копировать файл
	    string path1 = args[0] + "\\" + args[2];
            File.Copy(path, path1);
            Console.WriteLine("Файл {0} в новый каталог успешно скопирован с именем.", path, path1);

	    //Перемещение файлов
	    File.Move(path, args[1]);   
	    File.Move(path1, args[2]);   
            Console.WriteLine("Файлы: {0} и {1} успешно перемещены в текущий каталог.", args[1], args[2]);

	    //Переименование каталога
//	    Directory.Move(args[0], args[2]);
//            Console.WriteLine("Каталог {0} переименован в каталог {1}.", args[0], args[2]);

	    //Установмть атрибут файла только для чтения
	    File.SetAttributes(args[1], FileAttributes.ReadOnly);
	    FileAttributes fa = File.GetAttributes(args[1]);
            Console.WriteLine("Атрибут файла {0} установлен только для чтения {1}.", args[1], fa);
	    File.SetAttributes(args[2], FileAttributes.ReadOnly);
	    fa = File.GetAttributes(args[2]);
            Console.WriteLine("Атрибут файла {0} установлен только для чтения {1}.", args[2], fa);
	
	    //Удалить файл из каталога
//	    path = args[2] + "\\" + args[1];
//	    File.Delete(path);
//            Console.WriteLine("Файл {0} из переименованного каталога {1} успешно удалён.", path, args[2]);

	    //Удалить каталог
	    Directory.Delete(args[0]);
            Console.WriteLine("Каталог {0} успешно удалён.", args[0]);

	    //Установмть атрибут файла нормальный
	    File.SetAttributes(args[1], FileAttributes.Normal);
	    fa = File.GetAttributes(args[1]);
            Console.WriteLine("Атрибут файла {0} установлен нормальный {1}.", args[1], fa);
	    File.SetAttributes(args[2], FileAttributes.Normal);
	    fa = File.GetAttributes(args[2]);
            Console.WriteLine("Атрибут файла {0} установлен нормальный {1}.", args[2], fa);
	
	    //Удалить файлы
	    File.Delete(args[1]);
	    File.Delete(args[2]);
            Console.WriteLine("Файлы {0} и {1} из текущего каталога успешно удалены.", args[1], args[2]);
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