
using System;
using System.IO;
using System.Threading;

class Test
{
    static void Main()
    {
        // Load application settings.
        AppSettings appSettings = new AppSettings();
        Thread t = new Thread(appSettings.DoWork);
	t.Start();
    }
}

// Store and retrieve application settings.
class AppSettings
{
    const string fileName = "l:\\video_ts\\vts_01_0.vob";

    public void DoWork()
    {
	int cnt = 0;
/*
        // Create default application settings.
        aspectRatio   = 1.3333F;
        lookupDir     = @"C:\AppDirectory";
        autoSaveTime  = 30;
        showStatusBar = false;
*/
        if(File.Exists(fileName))
        {
            BinaryReader binReader =
                new BinaryReader(File.Open(fileName, FileMode.Open));
            try
            {
/*              
		// If the file is not empty,
                // read the application settings.
                // Read 4 bytes into a buffer to
                // determine if the file is empty.
                byte[] testArray = new byte[3];
                int count = binReader.Read(testArray, 0, 3);

                if (count != 0)
                {
                    aspectRatio   = binReader.ReadSingle();
                    lookupDir     = binReader.ReadString();
                    autoSaveTime  = binReader.ReadInt32();
                    showStatusBar = binReader.ReadBoolean();
                }
*/
		byte bt;
		while (binReader.PeekChar() != -1)
		{
			bt = binReader.ReadByte();
			++cnt;
		}
            }

            // If the end of the stream is reached before reading
            // the four data values, ignore the error and use the
            // default settings for the remaining values.
            catch(EndOfStreamException e)
            {
                Console.WriteLine("{0} . " +
                    "The end of file found.", e.GetType().Name);
            }
	    catch(IOException e)
	    {
                Console.WriteLine("{0} . " +
                    "I/O error. Byte = {1}", e.GetType().Name, cnt);
	    }
            finally
            {
                binReader.Close();
		Console.WriteLine("Reading {0} bytes.", cnt);
            }
        }

    }

}