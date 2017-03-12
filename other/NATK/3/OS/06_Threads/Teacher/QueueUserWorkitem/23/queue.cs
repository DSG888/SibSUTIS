using System;
using System.Threading;
public class Example {
    public static void Main() {
        TaskInfo ti = new TaskInfo("Simple message.");
        // Queue the task.
        //ThreadPool.QueueUserWorkItem(new WaitCallback(ThreadProc));
        ThreadPool.QueueUserWorkItem(new WaitCallback(ThreadProc), ti);

        Console.WriteLine("Main thread does some work, then sleeps.");
        // If you comment out the Sleep, the main thread exits before
        // the thread pool task runs.  The thread pool uses background
        // threads, which do not keep the application running.  (This
        // is a simple example of a race condition.)
        Thread.Sleep(1000);

        Console.WriteLine("Main thread exits.");
    }

    // This thread procedure performs the task.
    static void ThreadProc(Object stateInfo) {
        // No state object was passed to QueueUserWorkItem, so 
        // stateInfo is null.
	TaskInfo ti = (TaskInfo)stateInfo;
        Console.WriteLine("Hello from the thread pool - {0}", ti.msg);
    }

}

public class TaskInfo
{
    public string msg;
	
    public TaskInfo(Object stateInfo)
    {
	this.msg = (string)stateInfo;
    }
}