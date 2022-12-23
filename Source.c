#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define N 5

int sort_bubble_team(int* ptr_array, int* Team);
int mass(int* L);
int rate(int* L, int** A, int* Wins, int* Team, int* Place);
int search_max(int* L, int** A, int* Wins, int* Team, int* Place);
int search_min(int* L, int** A, int* Wins, int* Team, int* Place);
int search_above(int* L, int** A, int* Wins, int* Team, int* Place);
int search_below(int* L, int** A, int* Wins, int* Team, int* Place);

void main()
{
	int max = 0, min = 0;
	int i = 0;
	int Score[N];
	int Place[N];
	int Wins[N];
	int Non[N];
	int Team[N];
	int A[N][N];
	int L[50];
	FILE* file;
	file = fopen("Kurs.txt", "r");
	while (fscanf(file, "%1i", &L[i]) != EOF) {
		i++;
	}

	int k = 0;
	for (int i = 0; i < N; i++) {
		Wins[i] = 0;
	}

	for (int i = 0; i < N; i++) {
		Non[i] = 0;
	}

	for (int i = 0; i < N; i++) {
		Team[i] = i + 1;
	}

	for (int i = 0; i < N; i++) {
		Score[i] = 0;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i < j) {
				A[i][j] = k;
				Score[i] = Score[i] + L[A[i][j] * 2];
				if (L[A[i][j] * 2] > L[((A[i][j] + 1) * 2) - 1]) {
					Wins[i] = Wins[i] + 1;
				}
				if (L[A[i][j] * 2] == L[((A[i][j] + 1) * 2) - 1]) {
					Non[i] = Non[i] + 1;
				}
				k++;
			}
			else if (i > j) {
				Score[i] = Score[i] + L[((A[j][i] + 1) * 2) - 1];
				if (L[((A[j][i] + 1) * 2) - 1] > L[A[j][i] * 2])
				{
					Wins[i] = Wins[i] + 1;
				}
				 if (L[((A[j][i] + 1) * 2) - 1] == L[A[j][i] * 2]) {
					Non[i] = Non[i] + 1;
				}
			}

		}
	}
	sort_bubble_team(Wins, Team, Non, Score);
	Place[0] = 1;
	for (int i = 1; i < N; i++) {
		if (Wins[i - 1] == Wins[i]) {
			Place[i] = Place[i - 1];
		}
		else {
			Place[i] = Place[i - 1] + 1;
		}
	}
	

	
	
	int a;
	while (1) {
		printf("Кёрлинг\n\nВыберете функцию:\n1)Таблица счёта\n2)Рейтинговая таблица\n3)Поиск лучшей команды\n4)Поиск худшей команды\n5)Команды с победами выше x\n6)Команды с победами ниже x\n");
		scanf("%d", &a);
		switch (a) {
		case 1:
			system("cls");
			mass(L);
			printf("\n\n");
			break;
		case 2:
			system("cls");
			rate(L, A, Wins, Team, Place, Non, Score);
			printf("\n\n");
			break;
		case 3:
			system("cls");
			max = search_max(L, A, Wins, Team, Place, Score);
			printf("Лучший счёт:\nКоманда %i (Счёт: %i)\n\n", Team[max], Score[max]);
			break;
		case 4:
			system("cls");
			min = search_min(L, A, Wins, Team, Place, Score);
			printf("Худший счёт:\nКоманда %i (Счёт: %i)\n\n", Team[min], Score[min]);
			break;
		case 5:
			system("cls");
			search_above(L, A, Wins, Team, Place);
			printf("\n\n");
			break;
		case 6:
			system("cls");
			search_below(L, A, Wins, Team, Place);
			printf("\n\n");
			break;
		}
	}
}

int sort_bubble_team(int* Wins, int* Team, int* Non, int* Score) {
	int  x = 0, y = 0, z = 0, a = 0;
	for (int ch = 1; ch == 1; ch = ch) {
		ch = 0;
		for (int i = 1;i < N; i++) {
			if (Wins[i] > Wins[i - 1]) {
				ch = 1;
				x = Wins[i];
				Wins[i] = Wins[i - 1];
				Wins[i - 1] = x;
				y = Team[i];
				Team[i] = Team[i - 1];
				Team[i - 1] = y;
				z = Non[i];
				Non[i] = Non[i - 1];
				Non[i - 1] = z;
				a = Score[i];
				Score[i] = Score[i - 1];
				Score[i - 1] = a;
			}
			if ((Wins[i] == Wins[i - 1]) && (Score[i] > Score[i-1])) {
				ch = 1;
				x = Wins[i];
				Wins[i] = Wins[i - 1];
				Wins[i - 1] = x;
				y = Team[i];
				Team[i] = Team[i - 1];
				Team[i - 1] = y;
				z = Non[i];
				Non[i] = Non[i - 1];
				Non[i - 1] = z;
				a = Score[i];
				Score[i] = Score[i - 1];
				Score[i - 1] = a;
			}
		}
	}
	return 0;
}

int mass(int* L)
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

int rate(int* L, int** A, int* Wins, int* Team, int* Place, int* Non, int* Score) {

	printf("  Место  |   Команда  | Победы  |  Ничья  | Поражения | Набранные очки |\n");
	for (int i = 0; i < N; i++) {
		printf("  %3i    |  Команда %i |  %3i    |  %3i    |  %4i     |      %3i       |\n", Place[i], Team[i], Wins[i], Non[i], N - 1 - Wins[i] - Non[i], Score[i]);
	}
}

int search_max(int* L, int** A, int* Wins, int* Team, int* Place, int* Score) {
	int maxc;
	int max = 0;
	maxc = Score[0];
	for (int i = 1; i < N; i++) {
		if (Score[i] > maxc) {
			maxc = Score[i];
			max = i;
		}
	}
	return (max);
}

int search_min(int* L, int** A, int* Wins, int* Team, int* Place, int* Score) {
	int minc;
	int min = 0;
	minc = Score[0];
	for (int i = 1; i < N; i++) {
		if (Score[i] < minc) {
			minc = Score[i];
			min = i;
		}
	}
	return (min);
}

int search_above(int* L, int** A, int* Wins, int* Team, int* Place) {
	int flag;
	printf("Введите x:");
	scanf("%i", &flag);
	printf("Команды с количеством побед большим или равным %i:\n", flag);
	for (int i = 0; i < N; i++) {
		if (Wins[i] >= flag) {
			printf("Команада %i (Победы: %i)\n", Team[i], Wins[i]);
		}
	}
	return 0;
}

int search_below(int* L, int** A, int* Wins, int* Team, int* Place) {
	int flag;
	printf("Введите x:");
	scanf("%i", &flag);
	printf("Команды с количеством побед меньше или равным %i:\n", flag);
	for (int i = 0; i < N; i++) {
		if (Wins[i] <= flag) {
			printf("Команада %i (Победы: %i)\n", Team[i], Wins[i]);
		}
	}
	return 0;
}
