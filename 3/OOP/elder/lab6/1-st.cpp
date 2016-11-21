#include <stdlib.h>
#include <stdio.h>

int main() {
    tQueue *myQueue;// создадим очередь
    tStack *myStack;    // и стек
    myStack=new tStack; // выделим память, вызовем конструкторы
    myQueue=new tQueue;    
    for (int i=0;i<10;i++) { // добавим 10 случ. чисел в стек
        myStack->AddElement(rand()%100); // от 0 до 99
        myStack->PrintList(); // вывод стека
    }
    myStack->DeleteElement(rand()%10+1); // удалим случайный элемент стека
    myStack->PrintList(); // выведем
    for (int i=0;i<10;i++) { // тоже самое длч очереди
        myQueue->AddElement(rand()%100);
        myQueue->PrintList();
    }
    myQueue->DeleteElement(rand()%10+1);
    myQueue->PrintList();     
    system("pause");
}
