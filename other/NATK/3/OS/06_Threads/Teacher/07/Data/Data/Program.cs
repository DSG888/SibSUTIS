/*
В следующем примере показано использование поля, обозначенного атрибутом ThreadStaticAttribute, 
 для хранения информации о потоках. Эта технология обеспечивает большую производительность в сравнении 
 с технологией во втором примере.
*/
using System;
using System.Threading;

class Test
{
    static void Main()
    {
        for(int i = 0; i < 3; i++)
        {
            //Thread newThread = new Thread(ThreadData.ThreadStaticDemo);
            //newThread.Start();
            ThreadData td = new ThreadData(i);
            //Thread t = new Thread(new ThreadStart(td.ThreadStaticDemo));
            Thread t = new Thread(new ThreadStart(td.ThreadStaticDemo));
            t.Start();
        }
        Console.ReadLine();
    }
}

public class ThreadData
{
    [ThreadStaticAttribute]
    static int threadSpecificData;


    public ThreadData(int val)
    {
        cnt = val;
    }

    public void ThreadStaticDemo()
    {
        // Store the managed thread id for each thread in the static
        // variable.
        //threadSpecificData = Thread.CurrentThread.ManagedThreadId;
        threadSpecificData = cnt;

        // Allow other threads time to execute the same code, to show
        // that the static data is unique to each thread.
        Thread.Sleep( 1000 );

        // Display the static data.
        Console.WriteLine( "Data for managed thread(Данные для управляемого потока) {0}: {1}", 
            Thread.CurrentThread.ManagedThreadId, threadSpecificData );
    }
    private int cnt;
}

/* This code example produces output similar to the following:

Data for managed thread 4: 0
Data for managed thread 5: 1
Data for managed thread 3: 2
 */
