using System;
using System.IO;

public class Test
{

    public static void Main()
    {
	Run();

    }

    public static void Run()
    {
        string[] args = new string[3];
	args[0] = "Любое";
	args[1] = "значение ";
	args[2] = "переменной ";
	foreach (string a in args)
		Console.WriteLine(a);

    }
}