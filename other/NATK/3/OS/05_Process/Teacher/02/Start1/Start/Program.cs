using System;
using System.Diagnostics;
//using System.ComponentModel;
/*
 В следующем примере сначала порождается экземпляр обозревателя Internet Explorer, в котором 
    отображается содержимое папки "Избранное". Затем запускаются несколько других экземпляров Internet 
    Explorer и отображаются несколько определенных страниц или веб-узлов. И, наконец, запускается 
    Internet Explorer, в котором окно минимизируется при переходе на определенный веб-узел.
*/
/*
 В следующем примере в методе Main создаётся экземпляр класса MyProcess, а затем выполняется метод
    созданного класса - OpenWithArguments. В этом методе процесс запускается и ему передаются параметры.
 */

namespace MyProcessSample
{
    /// <summary>
    /// Shell for the sample.
    /// </summary>
    class MyProcess
    {

        /// <summary>
        /// Opens the Internet Explorer application.
        /// </summary>
        void OpenApplication(string myFavoritesPath)
        {
            // Start Internet Explorer. Defaults to the home page.
            Process.Start("C:\\laptev\\labC#\\15\\Console1.exe");

            // Display the contents of the favorites folder in the browser.
            //Process.Start(myFavoritesPath);

        }

        /// <summary>
        /// Opens urls and .html documents using Internet Explorer.
        /// </summary>
        void OpenWithArguments()
        {
            // url's are not considered documents. They can only be opened
            // by passing them as arguments.
            Process.Start("C:\\laptev\\labC#\\151\\Console1.exe", "asdf");

            // Start a Web page using a browser associated with .html and .asp files.
            //Process.Start("Console1.exe", "C:\\laptev\\labC#\\15\\");
            //Process.Start("IExplore.exe", "C:\\myPath\\myFile.asp");
        }

        /// <summary>
        /// Uses the ProcessStartInfo class to start new processes, both in a minimized 
        /// mode.
        /// </summary>
        void OpenWithStartInfo()
        {

            ProcessStartInfo startInfo = new ProcessStartInfo("C:\\laptev\\labC#\\15\\Console1.exe");
            startInfo.WindowStyle = ProcessWindowStyle.Minimized;

            //Process.Start(startInfo);

            startInfo.Arguments = "asdf";

            Process.Start(startInfo);

        }

        static void Main()
        {
            // Get the path that stores favorite links.
            //string myFavoritesPath =
            //Environment.GetFolderPath(Environment.SpecialFolder.Favorites);

            MyProcess myProcess = new MyProcess();

            //myProcess.OpenApplication(myFavoritesPath);
            myProcess.OpenWithArguments();
            //myProcess.OpenWithStartInfo();

        }
    }
}