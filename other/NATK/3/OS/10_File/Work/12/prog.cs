using System;
using System.IO;

class Test 
{
    public static void Main() 
    {
//        string path = @"c:\temp\MyTest.txt";
        string path = @"Test.txt";
        string path2 = path + "temp";

        try 
        {
            using (FileStream fs = File.Create(path)) {}
            // Ensure that the target does not exist.
            File.Delete(path2);

            // Copy the file.
            File.Copy(path, path2);
            Console.WriteLine("{0} copied to {1}", path, path2);

            // Try to copy the same file again, which should fail.
            File.Copy(path, path2);
            Console.WriteLine("The second Copy operation succeeded, which was not expected.");
        } 

        catch (Exception e) 
        {
            Console.WriteLine("Double copying is not allowed, as expected.");
            Console.WriteLine(e.ToString());
        }
    }
}
