#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <io.h>
#include <malloc.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

//1. В бинарном файле хранится множество геометрических фигур (3 вида на выбор), каждая
//представлена своей структурой. Реализовать удаление всех фигур по заданному с клавиатуры
//типу, вывод содержимого файла на экран. Дополнительных коллекций и файлов не использовать.

//2. В бинарном файле хранятся имена и количество детей, названных этим именем. Добавить
//возможность отсортировать данные в файле по убыванию количества и по алфавиту относительно
//имен. Добавить возможность вывода данных из файла. Дополнительных коллекций и файлов не использовать

struct Circle {
	int x, y;
	double r;
};
struct Square {
	double x;
};
struct Triangle {
	double a, b, c;
};

union Figure {
	struct Circle circle;
	struct Square square;
	struct Triangle triangle;
};

struct Geometry {
	int type;
	char* name;
	union Figure figure;
};

void FileName(char*);
int MenuType();
FILE* Fopen(char*, const char*);
void Create(char*);
void View(char*);
void Delete(char*);
int Menu();

int main(){
	FILE* f;
	char namef[100];
	FileName(namef);
	while (1){
		switch (Menu()){
		case 1: Create(namef);
			break;
		case 2: View(namef);
			break;
		case 3: Delete(namef);
			break;
		case 0: return 0;
		}
	}
}

void FileName(char* namef){
	puts("Input name of file: ");
	rewind(stdin);
	int i = 0;
	char a;
	do {
		a = getchar();
		if (a != '\n' && a != '\t') {
			namef[i++] = a;
		}
	} while (a != '\n');
	namef[i] = '\0';
}

FILE* Fopen(char* namef, const char* key){
	FILE* fl;
	fl = fopen(namef, key);
	if (!fl){
		puts("Error open file");
		return 0;
	}
	return fl;
}

int MenuType(){
	int type;
	do{
		puts("1 - Circle\n2 - Square\n3 - Triangle");
		puts("Input value:");
		scanf_s("%d", &type);
	} while (type < 1 || type > 3);
	return type;
}


void Create(char* namef){
	FILE* f;
	int count, i;
	struct Geometry geometry;
	f = Fopen(namef, "wb");
	printf("Count of structs = ");
	scanf_s("%d", &count);
	for (i = 0; i < count; i++){
		printf("\nInput %d-th struct:\n ", i + 1);
		geometry.type = MenuType();
		geometry.name = (char*)malloc(20);
		switch (geometry.type){
		case 1:
			strcpy_s(geometry.name, 20, "Circle");
			printf("Input coordinates x, y: ");
			scanf_s("%d%d", &geometry.figure.circle.x, &geometry.figure.circle.y);
			do{
				printf("Input radius r: ");
				scanf_s("%lf", &geometry.figure.circle.r);
			} while (geometry.figure.circle.r <= 0);
			break;
		case 2:
			strcpy_s(geometry.name, 20, "Square");
			do{
				printf("Input Side x: ");
				scanf_s("%lf", &geometry.figure.square.x);
			} while (geometry.figure.square.x <= 0);
			break;
		case 3:
			strcpy_s(geometry.name, 20, "Triangle");
			do{
				printf("Input Sides a, b, c: ");
				scanf_s("%lf%lf%lf", &geometry.figure.triangle.a,
					&geometry.figure.triangle.b, &geometry.figure.triangle.c);
			} while (geometry.figure.triangle.a <= 0 &&
			geometry.figure.triangle.b <= 0 && geometry.figure.triangle.c <= 0);
		}
		fwrite(&geometry, sizeof(struct Geometry), 1, f);
	}
	fclose(f);
}

void View(char* namef){
	FILE* f;
	struct Geometry geometry;
	f = Fopen(namef, "rb");
	puts("Current geometry figures:");
	while (fread(&geometry, sizeof(struct Geometry), 1, f) == 1){
		switch (geometry.type){
		case 1:
			printf("%s: x = %d, y = %d, r = %.2lf\n", geometry.name, geometry.figure.circle.x,
				geometry.figure.circle.y, geometry.figure.circle.r);
			break;
		case 2:
			printf("%s: x = %.2lf\n", geometry.name, geometry.figure.square.x);
			break;
		case 3:
			printf("%s: a = %.2lf, b = %.2lf, c = %.2lf\n", geometry.name, geometry.figure.triangle.a,
				geometry.figure.triangle.b, geometry.figure.triangle.c);
		}
	}
	fclose(f);
}

void Delete(char* namef){
	FILE* f;
	struct Geometry geometry;
	int type, i, j; // счётчики
	f = Fopen(namef, "rb+");
	type = MenuType();
	for (i = 0; fread(&geometry, sizeof(struct Geometry), 1, f) == 1; i++)
		if (geometry.type == type){
			for (j = i; fread(&geometry, sizeof(struct Geometry), 1, f) == 1; j++)
			{
				fseek(f, j * sizeof(struct Geometry), 0);
				fwrite(&geometry, sizeof(struct Geometry), 1, f);
				fseek(f, sizeof(struct Geometry), 1);
			}
			_chsize(_fileno(f), _filelength(_fileno(f)) - sizeof(struct Geometry)); // уменьшение размера файла на 
			fseek(f, i * sizeof(struct Geometry), 0);
			i--;
		}
	fclose(f);
}

int Menu(){
	int choice;
	do {
		puts("1 - Create structs\n2 - View structs\n3 - Delete figure\n0 - exit");
		puts("Input choice: ");
		scanf_s("%d", &choice);
	} while (choice > 3 || choice < 0);
	return choice;
}