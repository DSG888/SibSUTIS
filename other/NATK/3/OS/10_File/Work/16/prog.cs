using System;
using System.IO;
using System.Text;

class Test 
{
    public static void Main() 
    {
//        string path = @"c:\temp\MyTest.txt";
        string path = @"MyTest.txt";

        // Create the file if it exists.
        if (!File.Exists(path)) 
        {
            File.Create(path);
        }

        if ((File.GetAttributes(path) & FileAttributes.Hidden) == FileAttributes.Hidden) 
        {
            // Show the file.
            File.SetAttributes(path, FileAttributes.Archive);
            Console.WriteLine("The {0} file is no longer hidden.", path);
        } 
        else 
        {
            // Hide the file.
            File.SetAttributes(path, File.GetAttributes(path) | FileAttributes.Hidden);
            Console.WriteLine("The {0} file is now hidden.", path);
        }
    }
}