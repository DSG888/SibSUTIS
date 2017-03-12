using System;
using System.IO;
public class TextToFile 
{
    private const string FILE_NAME = "MyFile.txt";
    public static void Main(String[] args) 
    {
        if (File.Exists(FILE_NAME)) 
        {
            Console.WriteLine("{0} already exists.", FILE_NAME);
            return;
        }
        using (StreamWriter sw = File.CreateText(FILE_NAME))
        {
            sw.WriteLine ("This is my file.");
            sw.WriteLine ("I can write ints {0} or floats {1}, and so on.", 
                1, 4.2);
            sw.Close();
        }
    }
}