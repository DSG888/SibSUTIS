// For Directory.GetFiles and Directory.GetDirectories
// For File.Exists, Directory.Exists
using System;
using System.IO;
using System.Collections;

public class RecursiveFileProcessor 
{
    public static void Main(string[] args) 
    {
        Console.WriteLine("Удаление заданного файла из заданного каталога:");
        // If a directory is not specified, exit program.
        if(args.Length != 2)
        {
            // Display the proper way to call the program.
            Console.WriteLine("Используйте: prog.exe (имя каталога) (имя файла)");
            return;
        }
	if (!Directory.Exists(args[0]))
	{
            Console.WriteLine("Заданный каталог {0} не существует", args[0]);
            return;
	}
	string path = args[0] + '\\' + args[1];
	if (File.Exists(args[1]))
	{
            Console.WriteLine("Заданный файл {0} в текущем каталоге уже существует", args[1]);
            return;
	}
	if (!File.Exists(path))
	{
            Console.WriteLine("Заданный файл {0} не существует", path);
            return;
	}
	File.Delete(path);
        Console.WriteLine("Заданный файл {0} успешно удалён из каталога {1}.", path, args[0]);
    }

}