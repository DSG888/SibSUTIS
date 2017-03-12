// For Directory.GetFiles and Directory.GetDirectories
// For File.Exists, Directory.Exists
using System;
using System.IO;
using System.Collections;

public class RecursiveFileProcessor 
{
    public static void Main(string[] args) 
    {
        Console.WriteLine("Переименовать заданный каталог на заданный другой:");
        // If a directory is not specified, exit program.
        if(args.Length != 2)
        {
            // Display the proper way to call the program.
            Console.WriteLine("Используйте: prog.exe (имя каталога) (имя нового каталога)");
            return;
        }
	if (!Directory.Exists(args[0]))
	{
            Console.WriteLine("Заданный каталог {0} не существует", args[0]);
            return;
	}
	if (Directory.Exists(args[1]))
	{
            Console.WriteLine("Заданный новый каталог {0} уже существует", args[1]);
            return;
	}
	Directory.Move(args[0], args[1]);
        Console.WriteLine("Заданный каталог {0} успешно переименован в каталог {1}.", args[0], args[1]);
    }

}