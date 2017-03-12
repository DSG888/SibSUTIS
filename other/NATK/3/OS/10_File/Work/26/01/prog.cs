using System;
using System.IO;

class Test 
{
    public static void Main() 
    {
        // Specify the directories you want to manipulate.
        string path = "MyDir";
        string target = "TestDir";

        try 
        {
            // Determine whether the directory exists.
            if (!Directory.Exists(path)) 
            {
                // Create the directory it does not exist.
                Directory.CreateDirectory(path);
            }

            if (Directory.Exists(target)) 
            {
                // Delete the target to ensure it is not there.
                Directory.Delete(target, true);
            }

            // Move the directory.
            Directory.Move(path, target);

            // Create a file in the directory.
            File.CreateText(target + @"\myfile.txt");

            // Count the files in the target directory.
            Console.WriteLine("The number of files in {0} is {1}",
                target, Directory.GetFiles(target).Length);
        } 
        catch (Exception e) 
        {
            Console.WriteLine("The process failed: {0}", e.ToString());
        } 
        finally {}
    }
}