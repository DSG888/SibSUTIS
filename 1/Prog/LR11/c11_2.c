/*
	Разработайте интерактивную программу, демонстрирующую внутреннее (беззнаковое) представление знаковых однобайтовых целых. Программа взаимодействует с пользователем через простейшее меню. Пример сеанса работы программы приведен ниже (красным цветом выделены данные, вводимые пользователем):
		Want to continue? (1/0): 1
		Input signed integer: -39
		Unsigned representation: 217
		Want to continue? (1/0): 1
		Input signed integer: -38
		Unsigned representation: 218
		Want to continue? (1/0): 0
		Exiting!
*/

#include<stdio.h>

int main()
{
	unsigned char a=0;
	while (1)
	{
		printf("Не хочешь чуток дополнительного кода? (0/1)");
		scanf("%d", &a);
		if (a==1)
		{
			printf("Введите число: ");
			scanf("%d", &a);
			printf("Унсигтнед репресентатион = %u\n", a);
		}
		else
		{
			printf("Ну хватит.\n");
			break;
		}
	}
	return 0;
}
