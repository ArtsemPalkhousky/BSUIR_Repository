#include<stdio.h>
#include<conio.h>
#include<locale.h>
#include<Windows.h>
#define kk 3
#define abc 5
int main(int argc,char* argv[])
{
	setlocale(LC_ALL, "Russian");
	system("CLS");
	union un
	{
		short exnum[5], res[5];
	};
	struct Name
	{
		char name[kk];
		char surname[kk];
		char patronymic[kk];
		short term;
	}b;
	struct info
	{
		Name person[100];
		un inf;
		const char *exams[8]= { "Математика", "ОАиП", "Физика" , "АиЛОВТ","Философия","Аглийский","История","Химия" };
	};
	b.term = *argv[1]-'0';
	int i=0,j,kolex[5],*poryadok;
	info a;
	for (j = 0; j < 100; j++)
	{
		while (i < kk)
		{
			if (!i)
			{
				a.person[j].name[i] = rand() % 25 + 66;
				a.person[j].surname[i] = rand() % 25 + 66;
				a.person[j].patronymic[i] = rand() % 25 + 66;
			}

			else
			{
				a.person[j].name[i] = rand() % 25 + 98;
				a.person[j].surname[i] = rand() % 25 + 98;
				a.person[j].patronymic[i] = rand() % 25 + 98;
			}
			i++;
			a.person[j].term = rand() % 5 + 1;                      //распределение людей по семестрам
		}
		i = 0;
	}
	for(i=0;i<5;i++)
	kolex[i] = rand() % 2 + 3;                                //количество экзаменов в текущем семестре
	poryadok = (int*)malloc(kolex[b.term] * sizeof(int));   //порядок экзаменов в текущем семестре
	i = 0; j = 0;
	while (j < kolex[b.term])                        //цикл выбора порядка проведения экзаменов
	{
		poryadok[j] = rand() % 8 + 1;
		j++;
		while (i < j)                                 //проверка на несовпадение экзаменов(чтобы экзамены не повторялись)
		{
			if (poryadok[i] == poryadok[j])
				j--; i++;
		}
	}
	printf("Имя  Фам. Отч.        результаты экзаменов(№экзамена, предмет, оценка)\n\n");
	for (j = 0; j < 100; j++)                     //цикл вывода информации об учащихся за текущий семестр
	{
		if (a.person[j].term == b.term)
		{
			for (i = 0; i < kk; i++)
				printf("%c", a.person[j].name[i]);
			printf("  ");
			for (i = 0; i < kk; i++)
				printf("%c", a.person[j].surname[i]);
			printf("  ");
			for (i = 0; i < kk; i++)
				printf("%c", a.person[j].patronymic[i]);
			for (int i = 0; i < kolex[b.term]; i++)
			/*printf("%s  %s  %s", a.person[j].name, a.person[j].surname[i], person[j].patronymic[i]);*/
			{
				a.inf.exnum[i] = i + 1;
				printf("%d: ", a.inf.exnum[i]);
				printf("%s", a.exams[poryadok[i]]);
				a.inf.res[i] = rand() % 10 + 1;
				printf(" - %d,	", a.inf.res[i]);
			}
			printf("\n");
		}
	}
	return 0;
}
