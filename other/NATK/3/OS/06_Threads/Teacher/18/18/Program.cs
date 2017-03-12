/*
В приведенном ниже примере кода показан результат изменения приоритета потока. Создаются два потока 
 и приоритет одного из них устанавливается в значение BelowNormal. Оба потока увеличивают значение 
 переменной в цикле while и выполняются в течение заданного времени.
*/
using System;
using System.Threading;

class Test
{
    static void Main()
    {
        PriorityTest priorityTest1 = new PriorityTest("Hellow1, {0}", 500);
        PriorityTest priorityTest2 = new PriorityTest("Hellow2, {0}", 1000);
//        PriorityTest priorityTest = new PriorityTest();
        ThreadStart startDelegate1 = 
            new ThreadStart(priorityTest1.ThreadMethod);
        ThreadStart startDelegate2 = 
            new ThreadStart(priorityTest2.ThreadMethod);

        Thread threadOne = new Thread(startDelegate1);
        threadOne.Name = "ThreadOne";
        Thread threadTwo = new Thread(startDelegate2);
        threadTwo.Name = "ThreadTwo";

        threadTwo.Priority = ThreadPriority.BelowNormal;
        threadOne.Start();
        threadTwo.Start();

        // Allow counting for 10 seconds.
        Thread.Sleep(10000);
        priorityTest1.LoopSwitch = false;
        priorityTest2.LoopSwitch = false;
        Console.ReadLine();
    }
}

class PriorityTest
{
    bool loopSwitch;

    private string msg;
    private int val;

    public PriorityTest(string message, int value)
    {
        loopSwitch = true;
	this.msg = message; 
	this.val = value;
    }

    public PriorityTest()
    {
        loopSwitch = true;
	this.msg = ""; 
	this.val = 0;
    }

    public bool LoopSwitch
    {
        set{ loopSwitch = value; }
    }

    public void ThreadMethod()
    {
	Console.WriteLine(msg, val);

        long threadCount = 0;

        while(loopSwitch)
        {
            threadCount++;
        }
        Console.WriteLine("{0} with {1,11} priority " +
            "has a count = {2,13}", Thread.CurrentThread.Name, 
            Thread.CurrentThread.Priority.ToString(), 
            threadCount.ToString("N0")); 
    }
}

