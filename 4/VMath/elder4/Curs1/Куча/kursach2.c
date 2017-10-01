#include <stdlib.h>
#include <stdio.h>

#define READ 10
#define WRITE 11
#define LOAD 20
#define STORE 21
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43
#define SHR 50

char c[5], *path;
short n, i, memory[100], InstructionCounter=0, OperationCode=0, accumulator=0, InstructionRegister=0, operand=0;
FILE *f, *f1;

/* Функция ввода данных с клавиатуры*/
void input (int i)
{
int k;
char c[5];

    if (i<10)
       printf ("0%d ?>", i);
    else
    printf ("%d ?>", i);
    scanf ("%s", c);
    for (k=1; k<5; k++)
        while ((c[0]!='+' && c[0]!='-') || c[k]<'0' || c[k]>'9' || strlen(c)!=5)
        {
              printf ("Неверный формат данных \n");
              if (i<10)
                 printf ("0%d ?>",i);
              else
                  printf ("%d ?>",i);
              scanf ("%s", c);
        }
    memory[i]=char2int(c);
}

void output (void)
{
   printf ("\nДамп памяти:\n");
   printf ("╔══╤═════╤═════╤═════╤═════╤═════╤═════╤═════╤═════╤═════╤═════╗\n║ ");
   for (i=0; i<10; i++)
       printf ("│  %d  ", i);
   printf ("║\n║00");
   for (InstructionCounter=0; InstructionCounter<100; InstructionCounter++)
   {
        if (InstructionCounter%10==0 && InstructionCounter!=0)
           printf ("║\n║%d", InstructionCounter);
        printf ("│%+04d", memory[InstructionCounter]);
   }
   printf ("║\n╚══╧═════╧═════╧═════╧═════╧═════╧═════╧═════╧═════╧═════╧═════╝\n");
}

/*Функция преобразования типов из char в int*/
int char2int (char c[5])
{
    InstructionRegister=(c[1]*1000+c[2]*100+c[3]*10+c[4])-53328;
    if (c[0]=='-')
       InstructionRegister=-InstructionRegister;
return (InstructionRegister);
}

/* Функция ввода данных из файла*/

void fileread (int i)
{
int k, n;
char c[5];
    n=0;
    fscanf (f, "%s", c);
    for (k=1; k<5; k++)
        if ((c[0]!='+' && c[0]!='-') || c[k]<'0' || c[k]>'9' || strlen(c)!=5)
           n++;
    if (n==0)
       memory[i]=char2int(c);
    else
        printf ("Неверный формат данных в строке %d \n", i);
}

void clrscr()
  { write (1,"\033[2J\033[0;0H",10); }

/*Текст программы*/
int main (void)
{

clrscr();
for (InstructionCounter=0; InstructionCounter<100; InstructionCounter++)
    memory[InstructionCounter]=0;

printf ("      \nПрограммная модель компьютера SC, выполняющего программы на языке SA \n\n");
printf ("\t\t\t   Выполнил: Красняков К.В. \n");
printf ("\t\t\t   Группа П-01, второй курс \n");
printf ("\t\t\t   Логин p01s11 \n\n\n");

n=0;
while (n!=5)
{
clrscr();
printf ("\n\n[1] - Ввод данных с клавиатуры\n");
printf ("[2] - Ввод данных из файла\n");
printf ("[3] - Вывод дампа памяти на экран\n");
printf ("[4] - Вывод дампа памяти в файл\n");
printf ("[5] - Выход\n");
scanf ("%d", &n);

/*Ввод данных с клавиатуры*/
if (n==1)
{

   printf ("Введите значения: \n");
   for (InstructionCounter=0; InstructionCounter<100; InstructionCounter++)
   {
       input (InstructionCounter);
       if (memory[InstructionCounter]==-9999)
       {
          printf ("Процесс ввода завершен \n");
          break;
       }
   }
}

/*Ввод данных из файла*/
if (n==2)
{
   printf ("Введите имя файла \n");
   scanf ("%s", path);
   if ((f=fopen(path, "r"))==NULL)
    printf ("%s","Can't open file");
 else
 {
     for (InstructionCounter=0; InstructionCounter<100; InstructionCounter++)
     {
         fileread (InstructionCounter);
         if (memory[InstructionCounter]==9)
         {
            printf ("Процесс ввода завершен \n");
            break;
         }
     }
 }
}

/*Вывод дампа памяти*/
if (n==3)
   output();

/*Вывод дампа памяти в файл*/
if (n==4)
{
   printf ("Введите имя файла \n");
   scanf ("%s", path);
   f1=fopen(path, "w");
   for (InstructionCounter=0; InstructionCounter<100; InstructionCounter++)
   {
        if (InstructionCounter%10==0)
           fprintf (f1,"\n");
        fprintf (f1,"%+04d ", memory[InstructionCounter]);
   }
   printf ("Готово! \n");
}
/*Выход из програмы*/
if (n==5)
{
   fcloseall();
   exit(0);
}

/*Обработка введенных данных*/
if (n==1 || n==2)
{
InstructionCounter=0;
while (InstructionCounter<100)
{
        InstructionRegister=memory[InstructionCounter];
        OperationCode=InstructionRegister/100;
        operand=InstructionRegister%100;
        if (OperationCode==READ)
        {
           printf ("\nВведите значения: \n");
           input (operand);
        }
        else
            if (OperationCode==WRITE)
            {
               printf ("\nСлово ячейки %d: ", operand);
               printf ("%+04d",memory[operand]);
            }
            else
                if (OperationCode==LOAD)
                   accumulator=memory[operand];
                else
                    if (OperationCode==STORE)
                       memory[operand]=accumulator;
                    else
                         if (OperationCode==ADD)
                            accumulator+=memory[operand];
                         else
                             if (OperationCode==SUBTRACT)
                                accumulator-=memory[operand];
                             else
                                 if (OperationCode==DIVIDE)
                                 {
                                     if (memory[operand]==0)
                                     {
                                        printf ("\nОшибка: Деление на ноль\n");
                                        break;
                                     }
                                     else
                                         accumulator/=memory[operand];
                                 }
                                 else
                                     if (OperationCode==MULTIPLY)
                                        accumulator*=memory[operand];
                                     else
                                         if (OperationCode==BRANCH)
                                            InstructionCounter=operand-1;
                                         else
                                             if (OperationCode==BRANCHNEG)
                                             {
                                                if (accumulator<0)
                                                   InstructionCounter=operand-1;
                                             }
                                             else
                                                 if (OperationCode==BRANCHZERO)
                                                 {
                                                    if (accumulator==0)
                                                       InstructionCounter=operand-1;
                                                 }
                                                 else
                                                     if (OperationCode==HALT)
                                                        break;
                                                     else
                                                         if (OperationCode==SHR)
                                                         {
                                                            accumulator=memory[operand];
                                                            accumulator=accumulator%1000*10;
                                                         }
                                                         else
                                                             if (memory[InstructionCounter]>0)
                                                                printf ("\nНеизвестная команда в строке %d, возможно данные программы", InstructionCounter);
    InstructionCounter++;
}

/*Вывод дампа памяти на экран*/
output();
}
}
return (0);
}