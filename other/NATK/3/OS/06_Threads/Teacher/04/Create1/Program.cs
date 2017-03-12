/*
В следующем примере показано создание двух потоков с целью вызова статических методов и методов 
 экземпляров для другого объекта.
*/
using System;
using System.Threading;

public class ServerClass
{
    private int val;

    public ServerClass()
    {
        this.val = 0;
    }

//    public ServerClass(int value)
//    {
//        this.val = value;
//    }

    // The method that will be called when the thread is started.
    public void InstanceMethod()
    {
        Console.WriteLine(
            "ServerClass.InstanceMethod is running on another thread(..InstanceMethod работает как другой поток) с параметром = {0}.", val);

        // Pause for a moment to provide a delay to make 
        // threads more apparent.
        Thread.Sleep(3000);
        Console.WriteLine(
            "The instance method called by the worker thread has ended(instance метод, вызванный рабочим потоком, завершился).");
    }

    public void StaticMethod()
    {
        Console.WriteLine(
            "ServerClass.StaticMethod is running on another thread(..StaticMethod работает как другой поток) с параметром = {0}.", val);

        // Pause for a moment to provide a delay to make 
        // threads more apparent.
        Thread.Sleep(5000);
        Console.WriteLine(
            "The static method called by the worker thread has ended(static метод, вызванный рабочим потоком, завершился).");
    }
}

public class Simple{
    public static int Main(String[] args)
    {
        Console.WriteLine("Thread Simple Sample(Простой образец потока)");

//        ServerClass serverObject = new ServerClass(1000);
        ServerClass serverObject = new ServerClass();

        // Create the thread object, passing in the 
        // serverObject.InstanceMethod method using a 
        // ThreadStart delegate.
        Thread InstanceCaller = new Thread(
            new ThreadStart(serverObject.InstanceMethod));

        // Start the thread.
        InstanceCaller.Start();

        Console.WriteLine("The Main() thread calls this after "
            + "starting the new InstanceCaller thread(Главный поток вызывает этот после старта нового потока InstanceCaller).");

//        ServerClass serverObject1 = new ServerClass(2000);
        ServerClass serverObject1 = new ServerClass();

        // Create the thread object, passing in the 
        // serverObject.StaticMethod method using a 
        // ThreadStart delegate.
        Thread StaticCaller = new Thread(
            new ThreadStart(serverObject1.StaticMethod));

        // Start the thread.
        StaticCaller.Start();

        Console.WriteLine("The Main() thread calls this after "
            + "starting the new StaticCaller thread(Главный поток вызывает этот после старта нового потока StaticCaller).");
        Console.ReadLine();

        return 0;
    }
}
