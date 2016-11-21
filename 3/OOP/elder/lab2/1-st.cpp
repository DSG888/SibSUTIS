#include <stdlib.h>
#include <stdio.h>
#include <graphics.h>
#include <math.h>
struct stack {
       int data; // данные 
       stack *next; // ссылка на след. элемент
}; // класс для стека
struct queue {
       int data;
       queue *next;
}; // класс для очереди
void printS(stack *p) { // вывод стека
     while (p) { // пока элемент существует
           printf("%3d -> ",p->data);//выводим его
           p=p->next; // переходим к следующему
     }
     printf("NULL\n"); // вывод конца стека
}
void printQ(queue *p) {
     while (p) { // тоже саое для вывода очереди
           printf("%3d -> ",p->data);
           p=p->next;
     }
     printf("TAIL\n");
}
stack *addS(stack *head, int n, int pos) { // добавить элемент в стек head-голова стека n-данные нового элемента pos-на какую позицию вставить
      stack *p=new(stack); // выделяем паять дл янового элемента
      p->data=n; // записваем данные
      if (pos==0) { // если позиция нулевая, тогда
         p->next=head; // записываем элемент перед головой и
         return p; // возвращаем новую голову стека
      } // если этого не произошло
      stack *q=head; // создаем новый указатель на голову стека
      pos--; // указываем что продвинулись на одну позицию
      while (pos>0) { // пока не продвинемся до нужной позиции
            pos--; // меняем счетчик позиции
            if (!q) { // если элемента, после которого нужно вставить элемент, нет
               free(p); // осовбождаем паямть
               printf("\nERROR!\n"); // выводим сообщение об ошибки
               return head; // возвращаем старую голову
            }
            q=q->next; // переходим к след. элементу
      }
      p->next=q->next;// после найденного элемента вставляем наш
      q->next=p; // а после нашего текущий
      return head; // возвращаем старую голову
}
queue *addQ(queue *tail, int n) { // добавление элемента в очередь
     queue *p=new(queue); // таже самая процедура
     p->data=n; // только вставка элемента будет
     tail->next=p; // проходить в позицию после хвоста,
     tail=p; // после чего возвращается новая голова
     tail->next=NULL;
     return p;
}
stack *delS(stack *head, int pos) { // удалить элемент из стека
      stack *p=head;
      if (pos==1) { // если нужно удалить первый элемент
         head=head->next; // передвигаем голову на один элемент вперед
         free(p); // удаляем старую голову
         return head; // возвращаем новую
      } // если не произошло
      stack *q=head; // анчиная с головы
      p=head->next; // запоминаем элемент после головы
      pos-=2; // уменьшаем похицию на 2
      while (pos>0) { // пока не нашли нужную позицию
            pos--;
            if (!p) { // если нет нужной позиции
               printf("\nERROR!\n"); // ошибка
               return head;
            }
            q=p; // двигаем вперед оба указателя
            p=p->next;
      }
      // p - удаляемый элемент
      q->next=p->next; // ссылку с предыдущего элемента переносим на элемент после удаляемго
      free(p); // удаляем
      return head;     
}
queue *delQ(queue *head, int pos) { // удаление из очереди (аналогично)
      queue *p=head;
      if (pos==1) {
         head=head->next;
         free(p);
         return head;
      }
      queue *q=head;
      p=head->next;
      pos-=2;
      while (pos>0) {
            pos--;
            if (!p) {
               printf("\nERROR!\n");
               return head;
            }
            q=p;
            p=p->next;
      }
      q->next=p->next;
      free(p); 
      return head;     
}
int number(stack *p) { // считаем количество элементов в стеке
    if (!p) return 0; else // если нет элемента вохвращаем 0
       return 1+number(p->next); // иначе возвращаем 1 + следущий элемент (счет организован с помощью рекурсии)
}
int number1(queue *p) { // тоже самое для очереди
    if (!p) return 0; else
       return 1+number1(p->next);
}
stack *swapS(int n1,int n2, stack *head) { // меняем элементы местами в стеке с головой head и позициями n1 и n2
      int num=1;
      stack *head0,*p1,*p2;
      head0=new(stack); // новый указатель
      head0->next=head; // который указывет на голову (то есть он является элементом до головы)
      p1=head0;
      while (num<n1) {p1=p1->next; num++;} // находим элемент с номером n1
      p2=p1;
      while (num<n2) {p2=p2->next; num++;} // и номером n2
      if (n2-n1>1) {// если элементы стоят не рядом (далее рекомендую нарисовать чтобы понять принцип обмена, или погуглить, ибо сложно к пониманию)
          stack *q=p1->next->next; // здесь производятся зитрые махинации с адресами обмениваемых элементов таким образом
          p1->next->next=p2->next->next; // что после этих действий указатели с элемента, который был до второго из обмениваемых, стал указывать на первый
          p2->next->next=q; // а который указывал на первый стал указывать на второй, и соответственно, который стоял после первого
          q=p1->next; // стал стять после второго и наоборот
          p1->next=p2->next;
          p2->next=q;
      } else { // если элементы стоят рядом
          stack *q=p2->next->next; // здесб все на много проще, элемент, стоявший после второго элемента теперь стоит после первого, а первый элемент после второго.
          p1->next=p2->next; // а второй теперь стоит на месте первого, то есть до него стоит тот элемент, который стол до первого
          p2->next->next=p2;
          p2->next=q;
      }
      return head0->next; // возвращаем новую голову
}
queue *swapQ(int n1,int n2, queue *head) { // обмен элементов в очереди
      int num=1; // тут аналогично
      queue *head0,*p1,*p2;
      head0=new(queue);
      head0->next=head;
      p1=head0;
      while (num<n1) {p1=p1->next; num++;}
      p2=p1;
      while (num<n2) {p2=p2->next; num++;}
      if (n2-n1>1) {
          queue *q=p1->next->next;
          p1->next->next=p2->next->next;
          p2->next->next=q;
          q=p1->next;
          p1->next=p2->next;
          p2->next=q;
      } else {
          queue *q=p2->next->next;
          p1->next=p2->next;
          p2->next->next=p2;
          p2->next=q;
      }
      return head0->next;
}
int main() {
    stack *head; // стек
    queue *head1, *tail; // очередь
 //   srand(time(NULL));
    int a[100]; // массив для чисел
    bool b[256];
    head=NULL; // обнуление указателей
    tail=head1=NULL;
    for (int i=0;i<100;i++) a[i]=rand()%256; // заполняем массив случайными числами от 0 до 255
    for (int i=0;i<100;i++) {
        if (sqrt(a[i])*sqrt(a[i])==a[i]) { // если извлекается квадратный корень из элемента
           head=addS(head,a[i],0); // добавим его в стек в начало
           b[a[i]]=false; // помечаем, что данный элемент был включен в список
           printS(head); // выводим стек
        }
    }
    stack *p=head;
    int num=1;
    b[head->data]=true; // помечаем первый элемент списка флагом, что он встретился впервые
    while (p->next) { // пока есть элементы (тут будем избавляеть от повторяющихся элементов)
          if (!b[p->next->data]) { // если элемент еще не встречался
             b[p->next->data]=true; // помечаем что встретили
             num++;
             p=p->next; // переходим к следующему
          } else { // иначе
             delS(head,num+1);            // удаляем его
             printS(head); // выводим
          }
    }
    head=swapS(2,3,head); // меняем для примера 2 и 3 элементы стека
    printf("after swap 2 and 3\n");
    printS(head); // выводим
    printf("number of elements: %d\n",number(head));   // выводим количество элементов в стеке  
    for (int i=0;i<100;i++) { // далее тоже самое для очереди
        if (sqrt(a[i])*sqrt(a[i])==a[i]) {
           head=addS(head,a[i],0);
           if (tail==NULL) { // если элементов еще нет (хвоста не существует)
              tail=new (queue); // выделяем память
              tail->data=a[i]; // записываем данные
              tail->next=NULL; // указываем что после хвоста быть не может элементов
              head1=tail; // запоминаем голову (она является еще и хвостом так как всего 1 элемент)
           } else tail=addQ(tail,a[i]);
           b[a[i]]=false;
           printQ(head1);
        }
    } 
    queue *p1=head1;
    num=1;
    b[head1->data]=true;
    while (p1->next) {
          if (!b[p1->next->data]) {
             b[p1->next->data]=true;
             num++;
             p1=p1->next;
          } else {
             delQ(head1,num+1);           
             printQ(head1);
          }
    } 
    head1=swapQ(2,3,head1);
    printf("after swap 2 and 3\n");
    printQ(head1);    
    printf("number of elements: %d\n",number1(head1));         
    system("pause");
}
