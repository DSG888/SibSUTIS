using System;
using System.IO;

class Test 
{
    public static void Main() 
    {
//        string path = @"c:\temp\MyTest.txt";
        string path = @"MyTest.txt";
        string path2 = path + "temp";
        try 
        {
            using (StreamWriter sw = File.CreateText(path)) {}

            // Only do the Copy operation if the first file exists
            // and the second file does not.
            if (File.Exists(path)) 
            {
                if (File.Exists(path2)) 
                {
                    Console.WriteLine("The target already exists");
                } 
                else 
                {
                    // Try to copy the file.
                    File.Copy(path, path2);
                    Console.WriteLine("{0} was copied to {1}.", path, path2);
                }
            } 
            else 
            {
                Console.WriteLine("The source file does not exist.");
            }
        } 
        catch 
        {
            Console.WriteLine("Double copying is not allowed, as expected.");
        }
    }
}