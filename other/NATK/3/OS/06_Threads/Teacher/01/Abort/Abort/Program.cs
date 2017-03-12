/*
ThreadAbortException – класс
Исключение, выдаваемое при вызове метода Abort. Этот класс не может наследоваться.
Пространство имен:  System.Threading
Сборка:  mscorlib (в mscorlib.dll)
Заметки
При вызове метода Abort для уничтожения потока, общеязыковая среда выполнения выдает исключение 
 ThreadAbortException. Исключение ThreadAbortException является особым исключением, которое может 
 быть перехвачено, но снова возникает в конце блока catch. При возникновении этого исключения среда 
 выполнения перед тем, как завершить поток, выполняет все блоки finally. Так как поток может выполнять 
 код в блоках finally неограниченное время или вызывать метод Thread.ResetAbort для отмены аварийного 
 завершения потока, нет гарантии, что поток когда-либо закончит работу. Чтобы дождаться окончания 
 работы прерванного потока можно вызвать метод Thread.Join. Вызов метода Join является блокирующим, 
 возврата не происходит до действительного окончания выполнения потока.
*/
using System;
using System.Threading;
using System.Security.Permissions;

public class ThreadWork
{
    private int cnt;

    public ThreadWork(int val)
    {
        this.cnt = val; 
    }

    public void DoWork()
    {
        try
        {
            //for (int i = 0; i < 100; i++)
            for(;;)
            {
                Console.WriteLine("Thread - working(работает) {0}.", cnt++);
                Thread.Sleep(100);
            }
        }
        catch (ThreadAbortException e)
        {
            Console.WriteLine("Thread - caught ThreadAbortException - resetting(поймано исключение отказа потока - сброс).");
            Console.WriteLine("Exception message(исключительное сообщение): {0}", e.Message);
            Thread.ResetAbort();
        }
        Console.WriteLine("Thread - still alive and working(всё ещё жив и работает).");
        Thread.Sleep(1000);
        Console.WriteLine("Thread - finished working(законченная работа).");
    }
}

class ThreadAbortTest
{
    public static void Main()
    {
        //ThreadStart myThreadDelegate = new ThreadStart(ThreadWork.DoWork);
        ThreadWork myObject = new ThreadWork(100);
        //Thread myThread = new Thread(myThreadDelegate);
        Thread myThread = new Thread(myObject.DoWork);
        myThread.Start();
        Thread.Sleep(1000);
        Console.WriteLine("Main - aborting my thread(отказ моего потока).");
        myThread.Abort();
        myThread.Join();
        Console.WriteLine("Main ending(окончание).");
        Console.ReadLine();
    }
}