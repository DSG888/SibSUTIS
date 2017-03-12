// For Directory.GetFiles and Directory.GetDirectories
// For File.Exists, Directory.Exists
using System;
using System.IO;
using System.Collections;

public class RecursiveFileProcessor 
{
    public static void Main(string[] args) 
    {
        Console.WriteLine("—копировать заданный каталог в заданный другой:");
        // If a directory is not specified, exit program.
        if(args.Length != 2)
        {
            // Display the proper way to call the program.
            Console.WriteLine("»спользуйте: prog.exe (им€ каталога) (им€ другого каталога)");
            return;
        }
	if (!Directory.Exists(args[0]))
	{
            Console.WriteLine("«аданный каталог {0} не существует", args[0]);
            return;
	}
	if (Directory.Exists(args[1]))
	{
            Console.WriteLine("«аданный новый каталог {0} уже существует", args[1]);
            return;
	}
	Directory.CreateDirectory(args[1]);
	string[] myStr = Directory.GetFiles(args[0]);
//	string path = args[1]+"\\*.*";
//        Console.WriteLine(path);
	foreach (string s in myStr)
	{
//	    Console.WriteLine(s);
	    string name = _getname(s);
	    string path = args[1]+'\\'+name;
//	    Console.WriteLine(path);
	    File.Copy(s, path);
	}
        Console.WriteLine("«аданный каталог {0} успешно скопирован в каталог {1}.", args[0], args[1]);
    }

    static string _getname(string s)
    {
	string s1 = "";
	char ch;
	int ln = s.Length;
	int i = ln-1;
	while (true)
	{
	    ch = s[i];
	    if (ch == '\\') break;
	    s1 = ch + s1;
	    --i;
	}
	return s1;
    }	
}