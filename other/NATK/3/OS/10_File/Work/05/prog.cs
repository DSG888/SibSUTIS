using System;
using System.IO;
class DirectoryLister
{
    public static void Main(String[] args)
    {
        string path = ".";
        if (args.Length > 0)
        {
            if (File.Exists(args[0]))
            {
                path = args[0];
            }
            else
            {
                Console.WriteLine("{0} not found; using current directory:",
                    args[0]);
            }
        
        DirectoryInfo dir = new DirectoryInfo(path);
        foreach (FileInfo f in dir.GetFiles("*.exe")) 
        {
            String name = f. Name;
            long size = f.Length;
            DateTime creationTime = f.CreationTime;
            Console.WriteLine("{0,-12:N0} {1,-20:g} {2}", size, 
                creationTime, name);
        }
        }
    }
}