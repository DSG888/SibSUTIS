using System;
using System.IO;
class MyStream 
{
    private const string FILE_NAME = "Test.data";
    public static void Main(String[] args) 
    {
        // Create the new, empty data file.
        if (File.Exists(FILE_NAME)) 
        {
            Console.WriteLine("{0} already exists!", FILE_NAME);
            return;
        }
        FileStream fs = new FileStream(FILE_NAME, FileMode.CreateNew);
        // Create the writer for data.
        BinaryWriter w = new BinaryWriter(fs);
        // Write data to Test.data.
        for (int i = 0; i < 11; i++) 
        {
            w.Write( (int) i);
        }
        w.Close();
        fs.Close();
        // Create the reader for data.
        fs = new FileStream(FILE_NAME, FileMode.Open, FileAccess.Read);
        BinaryReader r = new BinaryReader(fs);
        // Read data from Test.data.
        for (int i = 0; i < 11; i++) 
        {
            Console.WriteLine(r.ReadInt32());
        }
        r.Close();
        fs.Close();
    }
}