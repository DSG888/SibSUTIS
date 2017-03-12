// For Directory.GetFiles and Directory.GetDirectories
// For File.Exists, Directory.Exists
using System;
using System.IO;
using System.Collections;

public class RecursiveFileProcessor 
{
    public static void Main(string[] args) 
    {
        Console.WriteLine("Копирование заданного файла из заданного каталога в другой каталог:");
        // If a directory is not specified, exit program.
        if(args.Length != 3)
        {
            // Display the proper way to call the program.
            Console.WriteLine("Используйте: prog.exe (имя каталога) (имя файла) (имя другого каталога)");
            return;
        }
	if (!Directory.Exists(args[0]))
	{
            Console.WriteLine("Заданный каталог {0} не существует", args[0]);
            return;
	}
	string path = args[0] + '\\' + args[1];
	if (!File.Exists(path))
	{
            Console.WriteLine("Заданный файл {0} в заданном каталоге {1} не существует", args[1], args[0]);
            return;
	}
	if (!Directory.Exists(args[2]))
	{
            Console.WriteLine("Заданный каталог {0} не существует", args[2]);
            return;
	}
	string path1 = args[2] + '\\' + args[1];
	if (File.Exists(path1))
	{
            Console.WriteLine("Заданный файл {0} в заданном каталоге {1} уже существует", args[1], args[2]);
            return;
	}
	File.Copy(path, path1);
        Console.WriteLine("Заданный файл {0} успешно скопирован из каталога {1} в каталог {2}.", args[1], path, path1);
    }

}