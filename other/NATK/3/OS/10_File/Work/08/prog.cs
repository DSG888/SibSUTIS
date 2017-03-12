using System;
using System.IO;
public class CharsFromStr
{
    public static void Main(String[] args)
    {
        // Create a string to read characters from.
        String str = "Some number of characters";
        // Size the array to hold all the characters of the string
        // so that they are all accessible.
        char[] b = new char[24];
        // Create an instance of StringReader and attach it to the string.
        StringReader sr = new StringReader(str);
        // Read 13 characters from the array that holds the string, starting
        // from the first array member.
        sr.Read(b, 0, 13);
        // Display the output.
        Console.WriteLine(b);
        // Close the StringReader.
        sr.Close();
    }
}