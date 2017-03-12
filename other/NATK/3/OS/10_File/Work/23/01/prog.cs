using System;
using System.IO;
using System.Text;

class FSOpenWrite
{
    public static void Main()
    {
//        FileStream fs=new FileStream("c:\\Variables.txt", FileMode.Append, FileAccess.Write, FileShare.Write);
        FileStream fs=new FileStream("Variables.txt", FileMode.Append, FileAccess.Write, FileShare.Write);
        fs.Close();
//        StreamWriter sw=new StreamWriter("c:\\Variables.txt", true, Encoding.ASCII);
        StreamWriter sw=new StreamWriter("Variables.txt", true, Encoding.ASCII);
        string NextLine="This is the appended line.\n";
        sw.Write(NextLine);
        sw.Close();
    }
}