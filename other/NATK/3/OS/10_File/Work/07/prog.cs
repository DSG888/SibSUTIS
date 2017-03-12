using System;
using System.IO;
class DirAppend
{
    public static void Main(String[] args)
    {
        using (StreamWriter w = File.AppendText("log.txt"))
        {
            Log ("Test1", w);
            Log ("Test2", w);
            // Close the writer and underlying file.
            w.Close();
        }
        // Open and read the file.
        using (StreamReader r = File.OpenText("log.txt"))
        {
            DumpLog (r);
        }
    }
    public static void Log (String logMessage, TextWriter w)
    {
        w.Write("\r\nLog Entry : ");
        w.WriteLine("{0} {1}", DateTime.Now.ToLongTimeString(),
            DateTime.Now.ToLongDateString());
        w.WriteLine("  :");
        w.WriteLine("  :{0}", logMessage);
        w.WriteLine ("-------------------------------");
        // Update the underlying file.
        w.Flush(); 
    }
    public static void DumpLog (StreamReader r)
    {
        // While not at the end of the file, read and write lines.
        String line;
        while ((line=r.ReadLine())!=null)
        {
            Console.WriteLine(line);
        }
        r.Close();
    }
}