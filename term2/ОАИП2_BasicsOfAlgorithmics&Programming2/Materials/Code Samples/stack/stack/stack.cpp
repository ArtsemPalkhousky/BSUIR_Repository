// пример работы со стеком
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>

struct zap
{
	char inf[50];
	zap *l;
};
void push(zap **);
char* pop(zap **);
void show(zap *);

int main()
{
	setlocale(LC_ALL, "Russian");
	zap *s = nullptr;
	char l, ss[50];
	while (1)
	{
		puts("\nвид операции:\n  1-создать/добавить\n  2-удалить");
		puts("  3-просмотреть\n  4- \n  5-");
		puts("  0-окончить");
		fflush(stdin);
		l = getch();
		switch (l)
		{
			case '1': push(&s); break;
			case '2': if(s)
					{  strcpy(ss, pop(&s));
					   printf("%s", ss);
					}
					else puts("стек пуст");
					break;
			case '3': show(s); break;
			case '4':  break;
			case '5':  break;
			case '0': return 0;
			default: printf("Ошибка, повторите \n");
		}
	}
	return 0;
}

// функция cоздания/добавления в стек
void push(zap **s)
{
	zap *s1 = *s;
	do
	{
		if(!(*s = (zap *)calloc(1, sizeof(zap))))
		{
			puts("Нет свободной памяти");
			return;
		}
		puts("Введите информацию в inf");
		fflush(stdin);
		gets((*s)->inf);
		(*s)->l = s1;
		s1 = *s;
		puts("Продолжить (y/n)");
		fflush(stdin);
	} while (getch() == 'y');
}

// функция просмотра элементов стека
void show(zap *s)
{
	if(!s)
	{
		puts("Стек пуст");
		return;
	}
	do
	{
		printf("    %s\n", s->inf);
		s = s->l;
	} while (s);
}

// функция удаления последнего элемента стека
// (с вершины стека)
char* pop(zap **s)
{
	zap *s1, ss;
	char st[50];
	strcpy(st, (*s)->inf);
	s1 = *s;       // указатель на вершину стека      
	ss = **s;      // запоминаем содержимое вершины стека
	*s = (*s)->l;  // указатель передвигаем "вниз" по стеку
	free(s1);    // удаляем с вершины стека
	return ss.inf;
}

