using System;
using System.IO;

class Test 
{
    public static void Main() 
    {
//        string path = @"c:\temp\MyTest.txt";
        string path = @"MyTest.txt";
        try 
        {
            using (StreamWriter sw = File.CreateText(path)) {}
            string path2 = path + "temp";

            // Ensure that the target does not exist.
            File.Delete(path2);

            // Copy the file.
            File.Copy(path, path2);
            Console.WriteLine("{0} was copied to {1}.", path, path2);

            // Delete the newly created file.
            File.Delete(path2);
            Console.WriteLine("{0} was successfully deleted.", path2);
        } 
        catch (Exception e) 
        {
            Console.WriteLine("The process failed: {0}", e.ToString());
        }
    }
}