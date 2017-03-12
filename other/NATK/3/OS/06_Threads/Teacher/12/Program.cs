/*
В следующем примере кода показано использование потока в спящем режиме.
*/
using System;
using System.Threading;

class ApartmentTest
{
    static void Main()
    {
/*
        Thread newThread = 
            new Thread(new ThreadStart(ThreadMethod));
        newThread.SetApartmentState(ApartmentState.MTA);

        // The following line is ignored since 
        // ApartmentState can only be set once.
        //newThread.SetApartmentState(ApartmentState.STA);

        Console.WriteLine("ThreadState(Состояние потока): {0}, ApartmentState(Состояние апартамента): {1}", 
            newThread.ThreadState, newThread.ApartmentState);

        newThread.Start();

        // Wait for newThread to start and go to sleep.
        Thread.Sleep(300);
        try
        {
            // This causes an exception since newThread is sleeping.
            newThread.SetApartmentState(ApartmentState.STA);
            Console.ReadLine();
        }
        catch(ThreadStateException stateException)
        {
            Console.WriteLine("\n{0} caught(обнаружено):\n" +
                "Thread is not in the Unstarted or Running state(Поток стартовал но не выполняется).", 
                stateException.GetType().Name);
            Console.WriteLine("ThreadState(Состояние потока): {0}, ApartmentState(Состояние апартамента): {1}",
                newThread.ThreadState, newThread.GetApartmentState());
            Console.ReadLine();
        }
 */
//        Program myObject = new Program(1000);
//        Thread myThread = new Thread(new ThreadStart(myObject.ThreadMethod));
        Thread myThread = new Thread(new ThreadStart(ThreadMethod));
        myThread.Start();
        Console.ReadLine();
    }
/*
    //static void ThreadMethod()
    public class Program
    {
 
        //Thread.Sleep(1000);
        //for (int i = 0; i < 10000; i++)
        private int maxval;
    
        public Program(int val)
        {
            this.maxval = val;
        }
*/
        public static void ThreadMethod()
        {
//            for (int i=0; i<maxval; i++)
            for (int i=0; i<1000; i++)
                Console.WriteLine(i);
        }
//    }
}

