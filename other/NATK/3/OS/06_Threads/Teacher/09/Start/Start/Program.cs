/*
Следующий пример демонстрирует создание и запуск потока.
Этот код формирует следующие выходные данные: 

     In main.
     Working thread...
     In main. Working thread...
     In main.
     Working thread...

Обратите внимание, что последовательность операторов вывода типичная, но не гарантируется, что она 
 будет одинаковой в разных системах.
Потоковые процедуры могут быть статическими методами или методами экземпляров. См. пример кода, 
 предоставленный для делегата ThreadStart. Дополнительные сведения о создании потоков см. в разделе 
 Создание потоков и передача данных во время запуска.
*/
using System;
using System.Threading;

public class ThreadWork 
{
    private int numb;

    public ThreadWork(int val)
    {
        this.numb = val;
    }

   public void DoWork()
   {
      for(int i = 0; i<3;i++)
      {
         Console.WriteLine("Working thread.(Работает поток)..{0}",numb++);
            Thread.Sleep(100);
      }
   }
}
class ThreadTest
{
   public static void Main()
   {
      //ThreadStart myThreadDelegate = new ThreadStart(ThreadWork.DoWork);
      //Thread myThread = new Thread(myThreadDelegate);
       ThreadWork tw = new ThreadWork(10);
       Thread myThread = new Thread(new ThreadStart(tw.DoWork));
      myThread.Start();
         for(int i = 0; i<3; i++)
         {
         Console.WriteLine("In main(В главном).");
            Thread.Sleep(100);
         }
         Console.ReadLine();
   }
}
