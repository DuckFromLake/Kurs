#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define N 5


void sort_bubble(int* ptr_array) {
	int  x = 0;
	for (int ch = 1; ch == 1; ch = ch) {
		ch = 0;
		for (int i = 1;i < N; i++) {
			if (ptr_array[i] > ptr_array[i - 1]) {
				ch = 1;
				x = ptr_array[i];
				ptr_array[i] = ptr_array[i - 1];
				ptr_array[i - 1] = x;
			}
		}
	}
}

void sort_bubble_team(int* ptr_array, int* Team) {
	int  x = 0, y = 0;
	for (int ch = 1; ch == 1; ch = ch) {
		ch = 0;
		for (int i = 1;i < N; i++) {
			if (ptr_array[i] > ptr_array[i - 1]) {
				ch = 1;
				x = ptr_array[i];
				ptr_array[i] = ptr_array[i - 1];
				ptr_array[i - 1] = x;
				y = Team[i];
				Team[i] = Team[i - 1];
				Team[i - 1] = y;
			}
		}
	}
}

void mass(int* L)
{
	int A[N][N];
	int k = 0;
	printf("  Команды  |");
	for (int i = 0; i < N; i++) {
		printf(" Команда %i |", i + 1);
	}
	printf("\n");
	for (int i = 0; i < N; i++) {
		printf(" Команда %i |", i + 1);
		for (int j = 0; j < N; j++) {
			if (i < j) {
				A[i][j] = k;
				printf("    %i:%i    |", L[A[i][j] * 2], L[((A[i][j] + 1) * 2) - 1]);
				k++;
			}
			else if (i > j) {
				printf("    %i:%i    |", L[((A[j][i] + 1) * 2) - 1], L[A[j][i] * 2]);
			} 
			else {
				printf("           |");
			}
		}
		printf("\n");
	}
}

void rate(int* L, int* Wins, int* Team, int* Place) {
	printf("  Место  |   Команда  |  Побед  | Поражений |\n");
	for (int i = 0; i < N; i++) {
		printf("  %3i    |  Команда %i |  %3i    |  %4i     |\n", Place[i], Team[i], Wins[i], N - 1 - Wins[i]);
	}
}



void main()
{
	int i = 0;
	int L[50];
	FILE* file;
	file = fopen("Kurs.txt", "r");
	while (fscanf(file, "%1i", &L[i]) != EOF) {
		i++;
	}

	int Place[N];
	int Wins[N];
	int Team[N];
	int A[N][N];
	int k = 0;
	for (int i = 0; i < N; i++) {
		Wins[i] = 0;
	}

	for (int i = 0; i < N; i++) {
		Team[i] = i + 1;
		printf("%i\n", Team[i]);
	}


	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i < j) {
				A[i][j] = k;
				if (L[A[i][j] * 2] > L[((A[i][j] + 1) * 2) - 1]) {
					Wins[i] = Wins[i] + 1;
				}
				k++;
			}
			else if (i > j) {
				if (L[((A[j][i] + 1) * 2) - 1] > L[A[j][i] * 2])
				{
					Wins[i] = Wins[i] + 1;
				}
			}

		}
	}
	sort_bubble_team(Wins, Team);
	Place[0] = 1;
	for (int i = 1; i < N; i++) {
		if (Wins[i - 1] == Wins[i]) {
			Place[i] = Place[i - 1];
		}
		else {
			Place[i] = Place[i - 1] + 1;
		}
	}

	for (int j = 0; j < i / 2; j++) {
		printf("%i:%i\n", L[j * 2], L[((j + 1) * 2) - 1]);
	}
	
	printf("Кёрлинг\n");
	printf("Выберете функцию:\n1)Таблица счёта\n2)Рейтинговая таблица\n3)Функция 2\n4)Функция 3\n");
	int a;
	while (1) {
		scanf("%d", &a);
		switch (a) {
		case 1:
			mass(L);
			break;
		case 2:
			rate(L, Wins, Team, Place);
			break;
		case 3:
			search();
			break;
		case 4:
			printf("Функция 2");
			break;
		}
	}
}