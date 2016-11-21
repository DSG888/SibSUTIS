//--------------------------------------ОБЪЯВЛЕНИЕ КЛАССОВ--------------------------
class tList { // общий класс - список
      protected: // данные только для класса и дочерних классов
       struct List { // структура списка
        int Data; // данные
        List *Next;  // ссылка на след. элемент
       };   
      public: // методы для свех
       tList(); // констурктор
       virtual void PrintList(){}; // вывод списка
       virtual void DeleteElement(){}; // удаление элемента
       virtual void AddElement(){}; // добавление элемента
};
class tStack: public tList {  // класс стека дочерний от класса списка
      protected: // добавляем поля голова
       List *Head;   
      public:
       tStack(); // конструктор
       virtual void PrintList(); // выводд стека
       virtual void DeleteElement(int NumElement); // удаление элемента по померу
       virtual void AddElement(int Element); // добавление элемента по данным
};
class tQueue: public tStack {  // очередь - наследуется от стека
      protected:
       List *Tail;   // добавляется поле хвост
      public:
       tQueue(); // конструктор
       virtual void PrintList(); // вывод очереди
       virtual void DeleteElement(int NumElement); // удаоение
       virtual void AddElement(int Element); // добавление
};
//--------------------------ОПИСАНИЕ КОНСТРУКТОРОВ----------------------------------
tList::tList() { // конструктор для списка пустой
}
tStack::tStack():tList() { // для стека инициализируется голова
     Head=NULL;
}
tQueue::tQueue():tStack() { // для очереди инициализируется хвост
     Tail=NULL;    
}
//------------------------ОПИСАНИЕ ДВИЖЕНИЯ---------------------------------------

void tStack::DeleteElement(int NumElement) { // удаление элемента из стека
     NumElement--; // уменьшаем номер элемента на 1 (будем тут считать сколько элементов осталось до нашего элемента)
     if (NumElement<0) { // если осталось отрицательное количество элементов, то значит элемента нет
        printf("Not found!\n"); // вывод о том что ничего не найдено
        return; // и выход
     }
     List *pHead,*sHead,*Temp; // обьявляем указатели
     Temp=Head; // указатель на голову
     sHead=new List; // создаем указатель, после кторого
     sHead->Next=Head; // будет голова
     pHead=sHead; // и начиная с элемента, который находится до головы, пробегать все
     while (NumElement>0) { // пока номер растояние нуля
           NumElement--; // уменьшаем его
           pHead=Temp; // сдвигаем указатели
           Temp=Temp->Next;
           if (Temp==NULL) { // если сдвигать уже некуда, значит элементы закончились
              printf("Not found!\n"); // выводим об этом месагу
              return; // выход
           }
     }
     pHead->Next=Temp->Next; // иначе перекидываем адреса с элемента До удаляемого на элемент ПОСЛЕ удаляемого
     free(Temp); // и удаляем наш элемент
     Head=sHead->Next; // запоминаем новую голову (которая не обязательно должна поменяться)
     free(sHead); // и удаляем указатель на псевдоголову(то что до головы)
}
void tStack::AddElement(int Element) { // добавление элемента в стек
     List *NewElement = new List; // создаем новый элемент
     NewElement->Data=Element; // заполняем данными
     NewElement->Next=Head; // ставим перед головой
     Head=NewElement; // переносим голову
}
void tStack::PrintList() { // вывод стека
     List *Temp=Head; // начина с головы
     while (Temp) { // пока есть элементы
           printf("%d ",Temp->Data);     // выводим данные 
           Temp=Temp->Next; // и переходим к следущему элементу
     }
     printf("\n");
}
void tQueue::AddElement(int Element) { // добавление элемента в очередь
     List *NewElement = new List; // выделение памяти
     NewElement->Data=Element; // заполение данными
     NewElement->Next=NULL; // после элемента ничего нет
     if (Tail==NULL) { // если хвоста нет
        Head=NewElement; // создаем новый элемент в голове
        Tail=Head; // изапоминаем хвост
     } else {
        Tail->Next=NewElement; // иначе добавим новый элемент после хвоста
        Tail=NewElement; // обновим хвост
     }
}
void tQueue::PrintList() { // вывод очереди аналогичен выводу стека
     List *Temp=Head;
     while (Temp) {
           printf("%d ",Temp->Data);     
           Temp=Temp->Next;
     }
     printf("\n");
}
void tQueue::DeleteElement(int NumElement) { // удаление элемента из очереди аналогично стеку
     NumElement--;
     if (NumElement<0) {
        printf("Not found!\n");
        return;
     }
     List *pHead,*sHead,*Temp;
     Temp=Head;
     sHead=new List;
     sHead->Next=Head;
     pHead=sHead;
     while (NumElement>0) {
           NumElement--;
           pHead=Temp;     
           Temp=Temp->Next;
           if (Temp==NULL) {
              printf("Not found!\n");
              return;
           }
     }
     pHead->Next=Temp->Next;
     free(Temp);
     Head=sHead->Next;
     free(sHead);
}
