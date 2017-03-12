// The following example calculates the size of a directory
// and its subdirectories, if any, and displays the total size
// in bytes.

using System;
using System.IO;

public class ShowDirSize 
{
    public static long DirSize(DirectoryInfo d) 
    {    
        long Size = 0;    
        // Add file sizes.
        FileInfo[] fis = d.GetFiles();
        foreach (FileInfo fi in fis) 
        {      
            Size += fi.Length;    
        }
        // Add subdirectory sizes.
        DirectoryInfo[] dis = d.GetDirectories();
        foreach (DirectoryInfo di in dis) 
        {
            Size += DirSize(di);   
        }
        return(Size);  
    }
    public static void Main(string[] args) 
    {
        if (args.Length != 1) 
        {
            Console.WriteLine("You must provide a directory argument at the command line.");    
        } 
        else 
        {  
            DirectoryInfo d = new DirectoryInfo(args[0]);
            Console.WriteLine("The size of {0} and its subdirectories is {1} bytes.", d, DirSize(d));
        }
    }
}