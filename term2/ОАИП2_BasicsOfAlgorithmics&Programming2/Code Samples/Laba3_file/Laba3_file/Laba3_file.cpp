#include <iostream>
#include <stdio.h>
#include<stdlib.h>


int max(int, int, int);


int main()
{
	setlocale(LC_ALL,"ru");
	system("CLS");
	int i,j,k1,k2,k3,k;
	int* msa, *msb, *msc;
	printf("введите размерность массивов: ");
	scanf_s("%d", &i);
	msa = (int*)malloc(i * sizeof(int));
	msb = (int*)malloc(i * sizeof(int));
	msc = (int*)malloc(i * sizeof(int));
	FILE* fa,*fb,*fc,*f;
	fopen_s(&fa, "NameA.txt", "w+");           //Открытие файлов и проверка
	if(!fa)
	{
		puts("Файл NameA не может быть создан");
			return 0;
	}
	fopen_s(&fb, "NameB.txt", "w+");
	if (!fb)
	{
		puts("Файл NameB не может быть создан");
		fclose(fa);
		return 0;
	}
	fopen_s(&fc, "NameC.txt", "w+");
	if (!fc)
	{
		puts("Файл NameC не может быть создан");
		fclose(fa);
		fclose(fb);
		return 0;
	}
	fopen_s(&f, "Main.txt", "w+");
	if (!f)
	{
		puts("Файл Main не может быть создан");
		fclose(fa);
		fclose(fb);
		fclose(fc);
		return 0;
	}
	for (j = 0; j < i; j++)
	{
		msa[j] = rand() % 1000;
		msb[j] = rand() % 1000;
		msc[j] = rand() % 1000;
	}
	for (j = 0; j < i; j++)              //Запись случайных значений в файлы NameA, NameB, NameC
	{
		fprintf(fa, "%4d", msa[j]);
		fprintf(fb, "%4d", msb[j]);
		fprintf(fc, "%4d", msc[j]);	
	}
	rewind(fa);
	rewind(fb);                          //Перемещение указателей в начало файла
	rewind(fc);
	rewind(stdin);
	printf("Файл NameA:");               //Вывод содерживого файлов NameA, NameB, NameC
	for (j = 0; j < i; j++)
		printf("%4d", msa[j]);
	printf("\n");
	printf("Файл NameB:");
	for (j = 0; j < i; j++)
		printf("%4d", msb[j]);
	printf("\n");
	printf("Файл NameC:");
	for (j = 0; j < i; j++)
		printf("%4d", msc[j]);
	printf("\n");
	while (!feof(fa) && !feof(fb) && !feof(fc))     //Чтение из файлов и запись наибольшего значения в Main файл
	{
		fscanf_s(fa, "%4d", &k1);
		fscanf_s(fb, "%4d", &k2);
		fscanf_s(fc, "%4d", &k3);
		fprintf(f,"%4d", max(k1,k2,k3));
	}
	fclose(fa);                                   //Закрытие файлов
	fclose(fb);
	fclose(fc);
	fclose(f);
	free(msa);                                    //Очистка памяти
	free(msb);
	free(msc);
	return 0;
}

int max(int k1, int k2, int k3)                         //Функция нахождения наибольшего значения
{
	return((k1 > k2) ? (k1 > k3) ? k1 : k3 : k2);
}