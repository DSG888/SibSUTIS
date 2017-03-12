using System;
using System.IO;

class Test 
{
    public static void Main() 
    {
        // Create an instance of StreamWriter to write text to a file.
        // The using statement also closes the StreamWriter.
        using (StreamWriter sw = new StreamWriter("TestFile.txt")) 
        {
            // Add some text to the file.
            sw.Write("This is the ");
            sw.WriteLine("header for the file.");
            sw.WriteLine("-------------------");
            // Arbitrary objects can also be written to the file.
            sw.Write("The date is: ");
            sw.WriteLine(DateTime.Now);
        }
    }
}