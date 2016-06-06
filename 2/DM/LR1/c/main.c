/*
Лабораторная работа № 1  Множества и операции над ними
Написать программу, в которой для конечных упорядоченных множеств реализовать все основные операции (, , , \) с помощью алгоритма типа слияния (по материалам лекции 1). Допустима организация множеств в виде списка или в виде массива.
Работа программы должна происходить следующим образом:
1.	На вход подаются два упорядоченных множества A и B (вводятся с клавиатуры, элементы множеств – буквы латинского алфавита). 
2. После ввода множеств выбирается требуемая операция (посредством текстового меню, вводом определенного символа в ответ на запрос – выбор по желанию автора). Операции: вхождение AB, AB, AB (дополнительно: A\B, B\A, AB). 
3. Программа посредством алгоритма типа слияния определяет результат выбранной операции и выдает его на экран с необходимыми пояснениями.
4. Возврат  на п.2 (выбор операции).
5. Завершение работы программы – из п.2 (например, по ESC).
Дополнительно: возможность возврата (по выбору пользователя) на п.2 или п.1. Выход в таком случае должен быть предусмотрен из любого пункта (1 или 2).
 
*/

#include <stdio.h>
#include <stdlib.h>
#include "set.h"

void getSet(char* name, Set** set)
{
    char* str = "Через пробел введите элементы множества ";
    printf(str);
    printf(name);
    printf(".\n");
    int flag = getSetFromCon(set);
    while (flag != 0) {
        printf("Некорректные данные. Попробуйте еще раз.\n");
        flag = getSetFromCon(set);
    }
}

void printMenu()
{
    printf("\n\t1. A ⊂ B\n");
    printf("\t2. A ∪ B\n");
    printf("\t3. A ⋂ B\n");
    printf("\t4. А \\ В\n");
    printf("\t5. В \\ А\n");
    printf("\t6. А ⊕ В\n");
    printf("\t7. Выход\n");
}

void printAnsw(Set* setA, Set* setB)
{
    printf("A = ");
    printSet(setA);
    printf("B = ");
    printSet(setB);
    printf("Результат.\n");
}

int main()
{
    Set* setA;
    getSet("A", &setA);
    Set* setB;
    getSet("B", &setB);
    char exit = 0;
    while (exit == 0)
    {
        printMenu();
        char c = (char) getchar();
        Set* setC = NULL;
        switch (c) {
            case '1':
                printAnsw(setA, setB);
                if (subSet(setA, setB) == 1)
                {
                    printf("Да\n");
                }
                else
                {
                    printf("Нет\n");
                }
                break;
            case '2':
                printAnsw(setA, setB);
                setC = merge(setA, setB);
                printSet(setC);
                destSet(&setC);
                break;
            case '3':
                printAnsw(setA, setB);
                setC = intersect(setA, setB);
                printSet(setC);
                destSet(&setC);
                break;
            case '4':
                printAnsw(setA, setB);
                setC = complement(setA, setB);
                printSet(setC);
                destSet(&setC);
                break;
            case '5':
                printAnsw(setA, setB);
                setC = complement(setB, setA);
                printSet(setC);
                destSet(&setC);
                break;
            case '6':
                printAnsw(setA, setB);
                setC = symComplement(setA, setB);
                printSet(setC);
                destSet(&setC);
                break;
            case '7':
                exit = 1;
                break;
            default:
                break;
        }
        getchar();
    }
    destSet(&setA);
    destSet(&setB);
    return 0;
}
