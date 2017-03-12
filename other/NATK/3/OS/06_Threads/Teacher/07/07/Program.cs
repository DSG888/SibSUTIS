/*
Получение данных с помощью метода обратного вызова
В следующем примере показана работа метода обратного вызова, с помощью которого получаются данные из 
 потока. Конструктор класса, содержащего данные и метод потока, также допускает использование делегата, 
 предоставляющего метод обратного вызова; перед завершением работы метод потока вызывает делегат 
 обратного вызова.
*/
using System;
using System.Threading;

// The ThreadWithState class contains the information needed for
// a task, the method that executes the task, and a delegate
// to call when the task is complete.
//
public class ThreadWithState {
    // State information used in the task.
    private string boilerplate;
    private int value;

    // Delegate used to execute the callback method when the
    // task is complete.
    private ExampleCallback callback;

    public ThreadWithState()
    {
        boilerplate = "";
        value = 0;
        callback = null;
//        callback = new ExampleCallback(DisplayEnything);
    }

    private static void DisplayEnything(int value)
    {
        Console.WriteLine("MИспользовался конструктор по умолчанию(без передачи параметров)");
        Console.WriteLine("Значение = {0}", value);
    }

    // The constructor obtains the state information and the
    // callback delegate.
    public ThreadWithState(string text, int number, 
        ExampleCallback callbackDelegate) 
    {
        boilerplate = text;
        value = number;
        callback = callbackDelegate;
    }
    
    // The thread procedure performs the task, such as
    // formatting and printing a document, and then invokes
    // the callback delegate with the number of lines printed.
    public void ThreadProc() 
    {
        Console.WriteLine(boilerplate, value);
        if (callback != null)
            callback(100);
        else
            Console.WriteLine("No callback");
    }
}

// Delegate that defines the signature for the callback method.
//
public delegate void ExampleCallback(int lineCount);

// Entry point for the example.
//
public class Example 
{
    public static void Main() 
    {
        // Supply the state information required by the task.
        ThreadWithState tws = new ThreadWithState();
//            "This report displays the number(Это сообщение показывает число) {0}.",
//            42,
//            new ExampleCallback(ResultCallback)
//        );

        Thread t = new Thread(new ThreadStart(tws.ThreadProc));
        t.Start();
        Console.WriteLine("Main thread does some work, then waits(Главный поток выполняет некоторую работу, и затем ждёт).");
        t.Join();
        Console.WriteLine(
            "Independent task has completed; main thread ends(Независимая задача завершилась; главный поток окончен).");
        Console.ReadLine();
    }

    // The callback method must match the signature of the
    // callback delegate.
    //
    public static void ResultCallback(int lineCount) 
    {
        Console.WriteLine(
            "Independent task printed(Независимой задачей напечатано) {0} lines.", lineCount);
    }
}

