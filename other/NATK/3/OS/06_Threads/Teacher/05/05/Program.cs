/*
Передача данных в потоки и получение данных из потоков

В .NET Framework версии 2.0 делегат ParameterizedThreadStart предоставляет простой способ передачи 
 объекта, содержащего данные, в поток при вызове перегрузки метода Thread.Start. Пример кода см. в 
 разделе ParameterizedThreadStart.
Использование делегата ParameterizedThreadStart не является безопасным способом передачи данных, так 
 как перегрузка метода Thread.Start принимает любой объект. Альтернативой является инкапсуляция 
 процедуры потока и данных во вспомогательном классе и использование делегата ThreadStart для 
 выполнения процедуры потока. Этот подход показан в приведенных ниже двух примерах кода.
Ни один из этих делегатов не имеет возвращаемого значения, потому что отсутствует расположение для 
 возвращения данных после асинхронного вызова. Для получения результатов метода потока можно 
 воспользоваться методом обратного вызова, как показано во втором примере.
*/
using System;
using System.Threading;

// The ThreadWithState class contains the information needed for
// a task, and the method that executes the task.
//
public class ThreadWithState {
    // State information used in the task.
    private string boilerplate;
    private int value;

    // Delegate used to execute the callback method when the
    // task is complete.
    private ExampleCallback callback;

    //Конструктор по умолчанию
    public ThreadWithState()
    {
        boilerplate = "";
        value = 0;
         callback = null;
//        callback = new ExampleCallback(DisplayEnything);
   }

    // The constructor obtains the state information.
    public ThreadWithState(string text, int number, 
        ExampleCallback callbackDelegate) 
    {
        boilerplate = text;
        value = number;
        callback = callbackDelegate;
    }

    // The thread procedure performs the task, such as formatting 
    // and printing a document.
    public void ThreadProc() 
    {
        Console.WriteLine(boilerplate, value); 
        if (callback != null)
            callback(value);
        else
            Console.WriteLine("No callback");
        Console.WriteLine("worker thread: terminating gracefully.");
    }
}

// Delegate that defines the signature for the callback method.
//
public delegate void ExampleCallback(int lineCount);

// Entry point for the example.
//
public class Example {
    public static void Main() 
    {
        // Supply the state information required by the task.
        ThreadWithState tws = new ThreadWithState(
            "This report displays the number(это сообщение показывает число) {0}.", 42,
//			null);
	            new ExampleCallback(ResultCallback));

        // Create a thread to execute the task, and then
        // start the thread.
        Thread t = new Thread(new ThreadStart(tws.ThreadProc));
        t.Start();
        Console.WriteLine("Main thread does some work, then waits(Главный поток выполняет некоторую работу, и затем ждёт).");
        t.Join();
        Console.WriteLine(
            "Independent task has completed; main thread ends.(Независимая задача завершилась; главный поток окончен)");
        Console.ReadLine();
    }

    // The callback method must match the signature of the
    // callback delegate.
    //
    public static void ResultCallback(int lineCount) 
    {
        Console.WriteLine(
            "Independent task returned value {0}.", lineCount);
    }
}
