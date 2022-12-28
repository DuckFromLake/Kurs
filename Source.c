#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define CATAGORY 5
#define TEAM 9

/////////////////// FUNCTION LIST //////////////////////

void read_file(FILE* file, int* L);
void var_declaration_and_sort(int** Var, int** A, int* L, int Team);

void arr(int** A, int* L, int Team);
void rate(int** Var, int Team);

int search_max(int** Var, int Team);
int search_min(int** Var, int Team);

void change_game(int** Var, int** A, int* L, int Team);


/////////////////// MAIN //////////////////////


void main()
{
	int a = 0, b, c, ta, j;
	int max = 0, min = 0, tmax = 0, tmin = 0;
	float tav = 0;
	int** Var;
	int** A;
	int* L;
	FILE* file;
	file = fopen("Kurs.txt", "r");

	Var = (double**)malloc(CATAGORY * sizeof(double*));
	for (int i = 0; i < CATAGORY; i++)
		Var[i] = (double*)malloc(TEAM * sizeof(double));

	A = (double**)malloc(TEAM * sizeof(double*));
	for (int i = 0; i < TEAM; i++)
		A[i] = (double*)malloc(TEAM * sizeof(double));

	L = (double*)malloc(((((TEAM * TEAM) - TEAM) + 1) / 2) * sizeof(double));

	read_file(file, L);
	var_declaration_and_sort(Var, A, L, TEAM);

	while (a != 5) {
		printf("\n\nВыберете функцию:\n1)Таблица счёта\n2)Рейтинговая таблица\n3)Поиск команды\n4)Изменение ячейки\n5)Данные по команде\n5)Выход\n");
		scanf("%d", &a);
		switch (a) {
		case 1:
			system("cls");
			arr(A, L, TEAM);
			printf("\n\n");
			break;
		case 2:
			system("cls");
			rate(Var, TEAM);
			printf("\n\n");
			break;
		case 3:
			system("cls");

			printf("1)Поиск лучшей команды по очкам\n2)Поиск худшей команды по очкам\n");
			scanf("%i", &b);
			switch (b) {
			case 1:
				system("cls");
				max = search_max(Var, TEAM);
				printf("Лучший счёт:\nКоманда %i (Счёт: %i)\n\n", Var[4][max], Var[0][max]);
				break;
			case 2:
				system("cls");
				min = search_min(Var, TEAM);
				printf("Худший счёт:\nКоманда %i (Счёт: %i)\n\n", Var[4][min], Var[0][min]);
				break;
			default:
				printf("Введён некорректный номер функции!\n\n");
				break;
			}
			break;
		case 4:
			system("cls");
			change_game(Var, A, L, TEAM);
			var_declaration_and_sort(Var, A, L, TEAM);
			break;
		case 5:
			fclose(file);
			printf("\nВыход из программы\n");
			break;
		default:
			printf("Введён некорректный номер функции!\n\n");
			break;
		}
	}
}


/////////////////// FUNCTIONS //////////////////////


void read_file(FILE* file, int* L) {
	int i = 0;
	while (fscanf(file, "%1i", &L[i]) != EOF) {
		i++;
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
			if ((Var[2][i] > Var[2][i - 1]) || ((Var[2][i] == Var[2][i - 1]) && (Var[0][i] > Var[0][i - 1])) || ((Var[2][i] == Var[2][i - 1]) && (Var[0][i] == Var[0][i - 1])) && (Var[3][i] > Var[3][i - 1])) {
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
		if (Var[0][i - 1] == Var[0][i] && Var[3][i - 1] == Var[3][i]) {
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
		printf("  %3i    |  Команда %i |  %3i    |  %3i    |  %4i     |      %3i       |\n", Var[1][i], Var[4][i], Var[2][i], Var[3][i], Team - 1 - Var[2][i] - Var[3][i], Var[0][i]);
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

void change_game(int** Var, int** A, int* L, int Team) {
	int x = 0, y = 0;
	int m, n;

	system("cls");
	printf("Команда по горизонтали:");
	scanf("%i", &x);
	printf("Команда по вертикали:");
	scanf("%i", &y);
	printf("Новое значение ячейки Команда %i VS Команда %i\n", y, x);

	printf("Очки команды %i:", x);
	scanf("%i", &n);

	printf("Очки команды %i:", y);
	scanf("%i", &m);

	y--;
	x--;

	if (y < x) {
		L[A[y][x] * 2] = m;
		L[((A[y][x] + 1) * 2) - 1] = n;
	}
	else if (y > x) {
		L[((A[x][y] + 1) * 2) - 1] = m;
		L[A[x][y] * 2] = n;
	}

	for (int i = 0; i < CATAGORY; i++) {
		for (int j = 0; j < Team; j++) {
			Var[i][j] = 0;
		}
	}
}

