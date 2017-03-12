using System;
using System.IO;
using System.Text;

public class CharsToStr
{
    public static void Main(String[] args)
    {
        // Create an instance of StringBuilder that can then be modified.
        StringBuilder sb = new StringBuilder("Some number of characters");
        // Define and create an instance of a character array from which 
        // characters will be read into the StringBuilder.
        char[] b = {' ','t','o',' ','w','r','i','t','e',' ','t','o','.'};
        // Create an instance of StringWriter 
        // and attach it to the StringBuilder.
        StringWriter sw = new StringWriter(sb);
        // Write three characters from the array into the StringBuilder.
        sw.Write(b, 0, 3);
        // Display the output.
        Console.WriteLine(sb);
        // Close the StringWriter.
        sw.Close();
    }
}