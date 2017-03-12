using System;
using System.Diagnostics;
using System.IO;

namespace RunProcess
{
    class Class1
    {
        [STAThread]
        static void Main(string[] args)
        {
            ProcessStartInfo startinfo;
            Process process = null;
            OperatingSystem os;
            string command, stdoutline;
            StreamReader stdoutreader;

            // Команда которую будет выполнять
            command = "NETSTAT -a";

            try
            {
                // Работаем только если это WinNT
                os = Environment.OSVersion;
                if (os.Platform != PlatformID.Win32NT)
                {
                    throw new PlatformNotSupportedException("Supported on Windows NT or later only");
                }
                os = null;

                // Проверка
                if (command == null || command.Trim().Length == 0)
                {
                    throw new ArgumentNullException("command");
                }

                startinfo = new ProcessStartInfo();
                // Запускаем через cmd
                startinfo.FileName = "cmd.exe";
                // Ключ /c - выполнение команды
                startinfo.Arguments = "/C " + command;
                // Не используем shellexecute
                startinfo.UseShellExecute = false;
                // Перенаправить вывод на обычную консоль
                startinfo.RedirectStandardOutput = true;
                // Не надо окон
                startinfo.CreateNoWindow = true;
                // Стартуем
                process = Process.Start(startinfo);

                // Получаем вывод
                stdoutreader = process.StandardOutput;
                while ((stdoutline = stdoutreader.ReadLine()) != null)
                {
                    // Выводим
                    Console.WriteLine(stdoutline);
                }
                stdoutreader.Close();
                stdoutreader = null;
            }
            catch
            {
                throw;
            }
            finally
            {
                if (process != null)
                {
                    // Закрываем
                    process.Close();
                }

                // Освобождаем
                process = null;
                startinfo = null;
            }

            Console.ReadLine();
        }
    }
}
