/*
В следующем примере кода показан синтаксис при создании и использовании делегата 
 ParameterizedThreadStart в методе экземпляра и статическом методе.
*/
using System;
using System.Threading;

public class Work
{
    public static void Main()
    {
        // To start a thread using a shared thread procedure, use
        // the class name and method name when you create the 
        // ParameterizedThreadStart delegate. C# infers the 
        // appropriate delegate creation syntax:
        //    new ParameterizedThreadStart(Work.DoWork)
        //
//        Thread newThread = new Thread(Work.DoWork);
        Work1 w = new Work1(500);
        Thread newThread = new Thread(w.DoWork);

        // Use the overload of the Start method that has a
        // parameter of type Object. You can create an object that
        // contains several pieces of data, or you can pass any 
        // reference type or value type. The following code passes
        // the integer value 42.
        //
//        newThread.Start(42);
        newThread.Start();

        // To start a thread using an instance method for the thread 
        // procedure, use the instance variable and method name when 
        // you create the ParameterizedThreadStart delegate. C# infers 
        // the appropriate delegate creation syntax:
        //    new ParameterizedThreadStart(w.DoMoreWork)
        //
//        Work w = new Work();
        Work1 w1 = new Work1("Msg");
        newThread = new Thread(w1.DoMoreWork);
//        Thread newThread1 = new Thread(w1.DoMoreWork);

        // Pass an object containing data for the thread.
        //
//        newThread.Start("The answer.");
        newThread.Start();
        Console.ReadLine();
    }

    public static void DoWork(object data)
    {
        Console.WriteLine("Static thread procedure(Процедура статического потока). Data='{0}'",
            data);
    }

    public void DoMoreWork(object data)
    {
        Console.WriteLine("Instance thread procedure(Процедура экземпляра потока). Data='{0}'",
            data);
    }
}

public class Work1
{
    private object data;

    public Work1(object Data)
    {
	this.data = Data;
    }

    public void DoWork()
    {
	Console.WriteLine("Static thread procedure {0}", data);
    }

    public void DoMoreWork()
    {
	Console.WriteLine("Instance thread procedure {0}", data);
    }
}
/* This code example produces the following output (the order 
   of the lines might vary):

Static thread procedure. Data='42'
Instance thread procedure. Data='The answer'
*/
