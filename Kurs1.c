#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 7

void mass()
{
	char A[N][N];
	int u;
	printf("|  Команды  |");
	for (int i = 0; i < N; i++) {
		printf(" Команда %i |", i+1);
	}
	printf("\n|");
	for (int i =0; i < N; i++) {
		printf(" Команда %i |", i + 1);
		for (int j = 0; j < N; j++) {
			A[i][j] = ;
			if (i > j) {

			}
			if (i == j) {
				printf("           |");
			}
			else {
				printf("  %4.f     |", A[i][j]);
			}
		}
		printf("\n|");
	}

}

void rate() {
	printf("|  Место  |  Команда  |  Игр сыграно  |  Побед  | Поражений  |\n");
	for (int i = 0; i < N; i++) {
		printf("|  %3i    |  Команда  |  %6i       |  %3i    |  %5i     |\n", 1,1,1,1 );
	}

}

void menu() {
	printf("Кёрлинг\n");
	printf("Выберете функцию:\n1)Вывод таблицы счёта\n2)Вывод рейтинговой таблицы\n3)Функция 2\n4)Функция 3\n");
	int a;
	while (1){
		scanf("%d", &a);
		switch (a) {
		case 1:
			mass();
			break;
		case 2:
			rate();
			break;
		case 3:
			printf("Функция 1");
			break;
		case 4:
			printf("Функция 2");
			break;
		}
	}
}

void main()
{
	menu();
}