/*
Thread.Abort – метод
Вызывает исключение ThreadAbortException в вызвавшем его потоке для того, чтобы начать процесс 
 завершения потока. Вызов данного метода обычно завершает поток.
Когда этот метод вызывается в потоке, система создает в нем исключение ThreadAbortException 
 для аварийного завершения. ThreadAbortException — специальное исключение, которое может быть 
 зафиксировано кодом приложения, но создается заново в конце блока catch, если не вызван метод 
 ResetAbort. ResetAbort отменяет запрос на аварийное завершение и предотвращает 
 ThreadAbortException от завершения потока. Невыполненные блоки finally выполняются до того, как 
 поток аварийно завершится.
 В следующем примере кода показано, как передается информация прерываемому потоку.
*/
using System;
using System.Threading;

class Test
{
    public static void Main()
    {
        //Thread newThread  = new Thread(new ThreadStart(TestMethod));
        TestMethod newObject = new TestMethod(10); 
        Thread newThread = new Thread(newObject.DoWork);
        newThread.Start();
        Thread.Sleep(1000);

        // Abort newThread.
        Console.WriteLine("Main aborting new thread(Главный прерывает новый поток).");
        newThread.Abort("Information from Main(Информация от Главного).");

        // Wait for the thread to terminate.
        newThread.Join();
        Console.WriteLine("New thread terminated - Main exiting(Новый поток завершён - Главный выходит.");
        Console.ReadLine();
    }

    //static void TestMethod()
    public class TestMethod
    {
        private int cnt;

        public TestMethod(int val)
        {
            this.cnt = val;
        }

        public void DoWork()
        {
        try
        {
            //while(true)
            for(;;)
            {
                Console.WriteLine("New thread running(Новый поток работает) {0}.", cnt++);
                Thread.Sleep(100);
            }
        }
        catch(ThreadAbortException abortException)
        {
            Console.WriteLine("Exception message(исключительное сообщение): {0}", (string)abortException.ExceptionState);
            //Console.WriteLine("Exception message: {0}", e.Message);
            Thread.ResetAbort();
        }
        Console.WriteLine("Thread - still alive and working(всё ещё жив и работает).");
        Thread.Sleep(1000);
        Console.WriteLine("Thread - finished working(закончил работу).");
        }
    }
} 
