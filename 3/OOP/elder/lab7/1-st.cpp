#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <strings.h>
#include <time.h>
#include <windows.h>
const int M[12]={31,28,31,30,31,30,31,31,30,31,30,31}; //количество дней в месяцах
struct product { // структура для продуктов
       char name[32]; // наименование
       float cost; // цена
       float amt; // коичество
       SYSTEMTIME shelf; // срок годности
};
struct list { // список продуктов
       product p; // продукт
       list *next; // ссылка на след. элемент
};
void readProduct(list *&head) { // считывае данных о продуктак из документа
       FILE *f;
       list *p;
       f=fopen("base.txt","rb"); // открываем файл для бинарного счения
       while (!feof(f)) { // пока не конец файла
             p=new(list);
             fread(&p->p, sizeof(p->p), 1, f); // считываем данные в стек
             p->next=head;
             head=p;
       }
       head=p->next;
       free(p);
       fclose(f);
}
void printList(list *p) {// вывод данных о продуктах
     int num=1;
     printf("#            Наименование           Количество    Цена    Годен до\n");
     while (p) { // пока есть элемент
           printf("%3d %32s  %8.2f   %4.2f  %2d.%2d.%2d\n",num,p->p.name,p->p.amt,p->p.cost,p->p.shelf.wDay,p->p.shelf.wMonth,p->p.shelf.wYear); // вывод соответствующих данных
           p=p->next;
           num++;
     }
}
bool find(list *p, char s[32]) {// поиск продукта
     while (p) { // пока есть элементы
           if (strcmp(p->p.name,s)==0) return true; // если нашелся продукт с наименованием таким же как и s, то возврадаем истину
           p=p->next;
     }
     return false; // иначе ложь
}
void addProduct(list *&head) { // добавление продукта
     FILE *f;
     list *p=new(list); // новая запись
     char name[32],shelf[12];
     float amt,cost;
     printf("Введите наименование товара(32б): ");
     scanf("%s",name); // считваем данные
     printf("Введите количество товара(шт,кг): ");
     scanf("%f",&amt);
     printf("Введите цену товара за шт,кг(руб): ");
     scanf("%f",&cost);          
     printf("Введите срок годности товара(дд.мм.гг): ");
     scanf("%s",shelf);
     strcpy(p->p.name,name); // запоминаем данные в список
     p->p.amt=amt;
     p->p.cost=cost;
     GetSystemTime(&p->p.shelf); // запоминаем срок годности, отдельно присваивая день, месяц и год
        char s[3];
        strncpy(s,shelf,2);
        p->p.shelf.wDay+=atoi(s);
        strncpy(s,shelf+3,2);
        p->p.shelf.wMonth+=atoi(s);
        strncpy(s,shelf+6,4);
        p->p.shelf.wYear+=atoi(s);
     while (p->p.shelf.wMonth>12) { // к тому же смотрим чтобы не было ошибок (месяц больше 12)
           p->p.shelf.wMonth-=12;
           p->p.shelf.wYear++;
     }
     while (p->p.shelf.wDay>M[p->p.shelf.wMonth]) { // чтобы не было больше дней в году
           p->p.shelf.wDay-=M[p->p.shelf.wMonth];
           p->p.shelf.wMonth++;           
           while (p->p.shelf.wMonth>12) {
                 p->p.shelf.wMonth-=12;
                 p->p.shelf.wYear++;
           }          
     }
     if (find(head,p->p.name)) { // если продукт в таким именем уже существует
        printf("product exists!\n"); // говорим что уже есть такой продукт
        free(p); // очщаем память
        return; // выход
     }
     p->next=head; // добавляем в стек запись
     head=p; // перносим голову
     f=fopen("base.txt","ab"); // открваем файл для дозаписи
     fwrite(&p->p, sizeof(p->p), 1, f); // дозаписываем нашу новую запись
     fclose(f); // закрываем файл
}
void checkShelf(list *p) { // проверка срока годности
     SYSTEMTIME t;
     GetSystemTime(&t); // получаем текущую дату
     while (p) { // пробегаем по всем элементам
           if (p->p.shelf.wYear<t.wYear) { // если текущий год больше чем в сроке годности то
              printf("%32s - %2d.%2d.%2d\n",p->p.name,p->p.shelf.wDay,p->p.shelf.wMonth,p->p.shelf.wYear); // выводи этот продукт на экран
           } else  // иначе
           if (p->p.shelf.wYear==t.wYear) { // если годы совпадают
              if (p->p.shelf.wMonth<t.wMonth) { // а месяц больше
                 printf("%32s - %2d.%2d.%2d\n",p->p.name,p->p.shelf.wDay,p->p.shelf.wMonth,p->p.shelf.wYear); // выводим
              } else
              if (p->p.shelf.wMonth==t.wMonth) { // и месяцы совпадают а день больше
                 if (p->p.shelf.wDay<=t.wDay) {
                    printf("%32s - %2d.%2d.%2d\n",p->p.name,p->p.shelf.wDay,p->p.shelf.wMonth,p->p.shelf.wYear); // выводим
                 }
              }
           }
           p=p->next; // переход к след. записи
     }
}
void deleteProduct(list *p) { // удаление продукта
     int num;
     FILE *f;
     printList(p); // выводим список продуктов
     printf("Какой товар удалить? ");
     scanf("%d",&num); // запоминаем номер удаляемого товара
     f=fopen("base.txt","wb"); // открываем файл для бинарной записи (запись а не дозапись, значит, что файл сотрется перед записью)
     while (num>1) { // пока номер элемента меньше номера удаляемого элемента
           if (!p) { // если нет элемента
              printf("not found!\n"); // значит не найден
              fclose(f);
              return;
           }
           fwrite(&p->p, sizeof(p->p), 1, f); // иначе выводим данные о элементе
           list *q=p;
           p=p->next;
           free(q);
           num--;
     }
     if (!p) { // если и сейчас не нашли элемент - беда
        printf("not found!\n");
        fclose(f);
        return; // выход
     }
     p=p->next; // переходим к след. элементу, пропуская текущий, иначе говоря не записываем в файл удаляемый элемент
     while (p) { // выводим все остальные записи в файл
           fwrite(&p->p, sizeof(p->p), 1, f);
           list *q=p;
           p=p->next;
           free(q);
     }
     fclose(f);
}
void correctCost(list *p) { // исправление цены
     int num;
     FILE *f;
     printList(p);
     printf("Какой товар изменить? ");
     scanf("%d",&num);
     f=fopen("base.txt","wb");
     while (num>1) { // поиск элемента аналогичен
           if (!p) {
              printf("not found!\n");
              fclose(f);
              return;
           }
           fwrite(&p->p, sizeof(p->p), 1, f);
           p=p->next;        
           num--;
     }
     if (!p) {
        printf("not found!\n");
        fclose(f);
        return;
     }
     printf("Введите цену: "); // как только нашли нужную запись
     scanf("%d",&num);
     p->p.cost=num; // считываем новую цену
     while (p) { // записываем и все выводим
           fwrite(&p->p, sizeof(p->p), 1, f);
           p=p->next;
     }
     fclose(f);
}
int main() {
    list *head=NULL;
    setlocale(LC_ALL,"rus"); // подключаем русский язык в консоль
    int key=1;
    readProduct(head); // считываем все продукты
    while (key!=0) { // пока не нажали выход
          system("CLS"); // очистка экрана
          printf(" 0) Выход\n"); // пункты меню
          printf(" 1) Список товаров\n");
          printf(" 2) Добавить товар\n");
          printf(" 3) Проверить срок годности\n");
          printf(" 4) Удалить товар\n");
          printf(" 5) Изменить цену товара\n");
          scanf("%d",&key); // считываем введенный пункт меню
          switch (key) { // проверяем что за пункт
                 case 0: break; // если нулевой - выход
                 case 1: printList(head); system("pause"); break; // если первый - вызываем функцию вывода списка
                 case 2: addProduct(head); system("pause"); break; // второй - добавление продукта
                 case 3: checkShelf(head); system("pause"); break; // проверка срока годности
                 case 4: deleteProduct(head); head=NULL; readProduct(head); system("pause"); break;  // удаление продукта и заново считывание из файла
                 case 5: correctCost(head); system("pause"); break; // изменение цены
          }
    }
    return 0;
}
