// For Directory.GetFiles and Directory.GetDirectories
// For File.Exists, Directory.Exists
using System;
using System.IO;
using System.Collections;

public class RecursiveFileProcessor 
{
    public static void Main(string[] args) 
    {
        Console.WriteLine("Удалить все файлы из заданного каталога:");
        // If a directory is not specified, exit program.
        if(args.Length != 1)
        {
            // Display the proper way to call the program.
            Console.WriteLine("Используйте: prog.exe (имя каталога)");
            return;
        }
	if (!Directory.Exists(args[0]))
	{
            Console.WriteLine("Заданный каталог {0} не существует", args[0]);
            return;
	}
	string[] myStr = Directory.GetFiles(args[0]);
	foreach (string s in myStr)
	    File.Delete(s);
        Console.WriteLine("Все файлы из заданного каталога {0} удалены", args[0]);
    }

    // Process all files in the directory passed in, recurse on any directories 
    // that are found, and process the files they contain.
    public static void ProcessDirectory(string targetDirectory) 
    {
        // Process the list of files found in the directory.
        string [] fileEntries = Directory.GetFiles(targetDirectory);
        foreach(string fileName in fileEntries)
            ProcessFile(fileName);

        // Recurse into subdirectories of this directory.
        string [] subdirectoryEntries = Directory.GetDirectories(targetDirectory);
        foreach(string subdirectory in subdirectoryEntries)
            ProcessDirectory(subdirectory);
    }

    // Insert logic for processing found files here.
    public static void ProcessFile(string path) 
    {
        Console.WriteLine("Processed file '{0}'.", path);	    
    }
}