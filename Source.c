
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <malloc.h>

#define CATAGORY 5
//#define TEAM 5

/////////////////// FUNCTION LIST //////////////////////

void read_file(FILE* file, int* L);
void var_declaration_and_sort(int** Var, int** A, int* L, int Team);

void arr(int** A, int* L, int Team);
void rate(int** Var, int Team);

int search_max(int** Var, int Team);
int search_min(int** Var, int Team);

int score_max(int** Var, int** A, int* L, int Team, int i);
int score_min(int** Var, int** A, int* L, int Team, int i);

void change_game(int** Var, int** A, int* L, int Team);



/////////////////// MAIN //////////////////////


void main()
{
	int a = -1, b, с,tm,  scr_max = 0, scr_min = 0;
	int TEAM;
	int max = 0, min = 0, tmax = 0, tmin = 0;
	float tav = 0;
	int** Var;
	int** A;
	int* L;
	FILE* file;
	file = fopen("Kurs.txt", "r");

	printf("Введите количество команд (не более 9):");
	scanf("%i", &TEAM);

	Var = (int**)malloc(CATAGORY * sizeof(int*));
	for (int i = 0; i < CATAGORY; i++)
		Var[i] = (int*)malloc(TEAM * sizeof(int));

	A = (int**)malloc(TEAM * sizeof(int*));
	for (int i = 0; i < TEAM; i++)
		A[i] = (int*)malloc(TEAM * sizeof(int));

	L = (int*)malloc((86) * sizeof(int));

	read_file(file, L);
	var_declaration_and_sort(Var, A, L, TEAM);

	while (a != 0) {
		printf("\n\nВыберете функцию:\n1)Таблица счёта\n2)Рейтинговая таблица\n3)Поиск команды\n4)Поиск результатов\n5)Изменение ячейки\n\n0)Выход\n");
		scanf("%i", &a);
		switch (a) {
		case 0:
			printf("\nВыход из программы\n");
			fclose(file);
			break;
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

			printf("1)Поиск лучшей команды по очкам\n2)Поиск худшей команды по очкам\n\n0)Назад\n");
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
			case 0:
				system("cls");
				break;
			default:
				printf("Введён некорректный номер функции!\n\n");
				break;
			}
			break;
		case 4:
			system("cls");

			printf("1)Поиск лучшего результата команды\n2)Поиск худшего результата команды\n\n0)Назад\n");
			scanf("%i", &с);
			switch (с) {
			case 1:
				system("cls");
				printf("Лучший результат\n\nПоиск по команде номер: ");
				scanf("%i", &tm);
				scr_max = score_max(Var, A, L, TEAM, tm-1);
				printf("Лучший счёт команды %i: %i ", tm, scr_max);
				break;
			case 2:
				system("cls");
				printf("Худший результат\n\nПоиск по команде номер : ");
				scanf("%i", &tm);
				scr_min = score_min(Var, A, L, TEAM, tm-1);
				printf("Худший счёт команды %i: %i ", tm, scr_min);
				break;
			case 0:
				system("cls");
				break;
			default:
				printf("Введён некорректный номер функции!\n\n");
				break;
			}
			break;
		case 5:
			system("cls");
			change_game(Var, A, L, TEAM);
			var_declaration_and_sort(Var, A, L, TEAM);
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

int score_max(int** Var, int** A, int* L,int Team, int i) {
	int max = 0;
	for (int j = 0; j < Team; j++) {
		if (i < j) {
			if (max < L[A[i][j] * 2])
			max = L[A[i][j] * 2];

		}
		else if (i > j) {
			if (max < L[((A[j][i] + 1) * 2) - 1])
			max = L[((A[j][i] + 1) * 2) - 1];
		}
	}
	return max;
}

int score_min(int** Var, int** A, int* L, int Team, int i) {
	int min = 10;
	for (int j = 0; j < Team; j++) {
		if (i < j) {
			if (min > L[A[i][j] * 2])
				min = L[A[i][j] * 2];

		}
		else if (i > j) {
			if (min > L[((A[j][i] + 1) * 2) - 1])
				min = L[((A[j][i] + 1) * 2) - 1];
		}
	}
	return min;
}
