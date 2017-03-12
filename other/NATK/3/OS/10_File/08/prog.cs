// For Directory.GetFiles and Directory.GetDirectories
// For File.Exists, Directory.Exists
using System;
using System.IO;
using System.Collections;

public class RecursiveFileProcessor 
{
    public static void Main(string[] args) 
    {
        Console.WriteLine("Перемещение заданного файла из текущего каталога в заданный каталог:");
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
	if (File.Exists(path))
	{
            Console.WriteLine("Заданный файл {0} в заданном каталоге {1} уже существует", args[1], args[0]);
            return;
	}
	if (!File.Exists(args[1]))
	{
            Console.WriteLine("Заданный файл {0} не существует", args[1]);
            return;
	}
	File.Move(args[1], path);
        Console.WriteLine("Заданный файл {0} успешно перемещён в заданный каталог{1}.", args[1], path);
    }

}