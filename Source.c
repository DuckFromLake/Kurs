#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define TEAM 5
#define CATAGORY 5


void var_declaration_and_sort(int** Var, int** A, int* L, int Team);

void arr(int** A,int* L, int Team);
void rate(int** Var, int Team);

int search_max(int** Var, int Team);
int search_min(int** Var, int Team);

int change_score_y(int y);
int change_score_x(int x);




void main()
{
	int x = 0, y = 0;
	int max = 0, min = 0;
	int i = 0;

	// Score 0
	// Place 1
	// Wins 2
	// Non 3
	// Team 4

	int **Var;
	int** A;
	int L[50];

	Var = (double**)malloc(TEAM * sizeof(double*));
	for (int i = 0; i < TEAM; i++)
		Var[i] = (double*)malloc(CATAGORY * sizeof(double));

	A = (double**)malloc(TEAM * sizeof(double*));
	for (int i = 0; i < TEAM; i++)
		A[i] = (double*)malloc(TEAM * sizeof(double));

	FILE* file;
	file = fopen("Kurs.txt", "r");
	while (fscanf(file, "%1i", &L[i]) != EOF) {
		i++;
	}

	var_declaration_and_sort(Var, A, L, TEAM);

	int a, b;
	while (1) {
		printf("Кёрлинг\n\nВыберете функцию:\n1)Таблица счёта\n2)Рейтинговая таблица\n3)Поиск команды\n4)Изменение ячейки\n5)Выход");
		scanf("%d", &a);
		switch (a) {
		case 1:
			system("cls");
			arr(A,L,TEAM);
			printf("\n\n");
			break;
		case 2:
			system("cls");
			rate(Var, TEAM);
			printf("\n\n");
			break;
		case 3:
			system("cls");

			printf("1)Поиск лучшей команды\n2)Поиск худшей команды\n");
			scanf("%i", &b);
			switch (b) {
			case 1:
				system("cls");
				max = search_max(Var,TEAM);
				printf("Лучший счёт:\nКоманда %i (Счёт: %i)\n\n", Var[4][max], Var[0][max]);
				break;
			case 2:
				system("cls");
				min = search_min(Var,TEAM);
				printf("Худший счёт:\nКоманда %i (Счёт: %i)\n\n", Var[4][min], Var[0][min]);
				break;
			default:
				printf("Введён некорректный номер функции!\n\n");
				break;
			}
			break;
		case 4:
			system("cls");
			printf("Ось x ячейки:");
			scanf("%i", &x);
			x--;
			printf("Ось y ячейки:");
			scanf("%i", &y);
			y--;
			printf("Новое значение ячейки Команда %i VS Команда %i\n", y + 1, x + 1);
			if (y < x) {
				L[A[y][x] * 2] = change_score_y(y);
				L[((A[y][x] + 1) * 2) - 1] = change_score_x(x);
			}
			else if (y > x) {
				L[((A[x][y] + 1) * 2) - 1] = change_score_y(y);
				L[A[x][y] * 2] = change_score_x(x);
			}

			for (int i = 0; i < CATAGORY; i++) {
				for (int j = 0; j < TEAM; j++) {
					Var[i][j] = 0;
				}
			}

			var_declaration_and_sort(Var, A, L, TEAM);
			break;
		default:
			printf("Введён некорректный номер функции!\n\n");
			break;
		}
	}
}


void var_declaration_and_sort(int** Var, int** A, int* L, int Team) {

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < Team; j++) {
			Var[i][j] = 0;
		}
	}

	for (int j = 0; j < Team; j++) {
		Var[4][j] = j + 1;
	}

	int k = 0;
	for (int i = 0; i < Team; i++) {
		for (int j = 0; j < Team; j++) {
			if (i < j) {
				A[i][j] = k;
				Var[0][i] = Var[0][i] + L[A[i][j] * 2];
				if (L[A[i][j] * 2] > L[((A[i][j] + 1) * 2) - 1]) {
					Var[2][i] = Var[2][i] + 1;
				}
				if (L[A[i][j] * 2] == L[((A[i][j] + 1) * 2) - 1]) {
					Var[3][i] = Var[3][i] + 1;
				}
				k++;
			}
			else if (i > j) {
				Var[0][i] = Var[0][i] + L[((A[j][i] + 1) * 2) - 1];
				if (L[((A[j][i] + 1) * 2) - 1] > L[A[j][i] * 2])
				{
					Var[2][i] = Var[2][i] + 1;
				}
				if (L[((A[j][i] + 1) * 2) - 1] == L[A[j][i] * 2]) {
					Var[3][i] = Var[3][i] + 1;
				}
			}
		}
	}

	int  x = 0, y = 0, z = 0, a = 0;
	for (int ch = 1; ch == 1; ch = ch) {
		ch = 0;
		for (int i = 1;i < Team; i++) {
			if ((Var[2][i] > Var[2][i - 1]) || ((Var[2][i] == Var[2][i - 1]) && (Var[0][i] > Var[0][i - 1]))) {
				ch = 1;
				x = Var[2][i];
				Var[2][i] = Var[2][i - 1];
				Var[2][i - 1] = x;
				y = Var[4][i];
				Var[4][i] = Var[4][i - 1];
				Var[4][i - 1] = y;
				z = Var[3][i];
				Var[3][i] = Var[3][i - 1];
				Var[3][i - 1] = z;
				a = Var[0][i];
				Var[0][i] = Var[0][i - 1];
				Var[0][i - 1] = a;
			}
		}
	}
	Var[1][0] = 1;
	for (int i = 1; i < Team; i++) {
		if (Var[0][i - 1] == Var[0][i]) {
			Var[1][i] = Var[1][i - 1];
		}
		else {
			Var[1][i] = Var[1][i - 1] + 1;
		}
	}

}


void arr(int** A, int* L, int Team)
{
	int k = 0;
	printf("  Команды  |");
	for (int i = 0; i < Team; i++) {
		printf(" Команда %i |", i + 1);
	}
	printf("\n");
	for (int i = 0; i < Team; i++) {
		printf(" Команда %i |", i + 1);
		for (int j = 0; j < Team; j++) {
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

void rate(int** Var, int Team) {

	printf("  Место  |   Команда  | Победы  |  Ничья  | Поражения | Набранные очки |\n");
	for (int i = 0; i < Team; i++) {
		printf("  %3i    |  Команда %i |  %3i    |  %3i    |  %4i     |      %3i       |\n", Var[1][i], Var[4][i], Var[2][i], Var[3][i], TEAM - 1 - Var[2][i] - Var[3][i], Var[0][i]);
	}
}

int search_max(int** Var, int Team) {
	int maxc;
	int max = 0;
	maxc = Var[0][0];
	for (int i = 1; i < Team; i++) {
		if (Var[0][i] > maxc) {
			maxc = Var[0][i];
			max = i;
		}
	}
	return (max);
}

int search_min(int** Var, int Team) {
	int minc;
	int min = 0;
	minc = Var[0][0];
	for (int i = 1; i < Team; i++) {
		if (Var[0][i] < minc) {
			minc = Var[0][i];
			min = i;
		}
	}
	return (min);
}
int change_score_y(int y) {
	int n;
	printf("Очки команды %i:", y + 1);
	scanf("%i", &n);
	return n;
}

int change_score_x(int x) {
	int n;
	printf("Очки команды %i:", x + 1);
	scanf("%i", &n);
	return n;
}
