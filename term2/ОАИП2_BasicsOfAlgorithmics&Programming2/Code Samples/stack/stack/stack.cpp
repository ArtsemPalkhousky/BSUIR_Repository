// ������ ������ �� ������
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
		puts("\n��� ��������:\n  1-�������/��������\n  2-�������");
		puts("  3-�����������\n  4- \n  5-");
		puts("  0-��������");
		fflush(stdin);
		l = getch();
		switch (l)
		{
			case '1': push(&s); break;
			case '2': if(s)
					{  strcpy(ss, pop(&s));
					   printf("%s", ss);
					}
					else puts("���� ����");
					break;
			case '3': show(s); break;
			case '4':  break;
			case '5':  break;
			case '0': return 0;
			default: printf("������, ��������� \n");
		}
	}
	return 0;
}

// ������� c�������/���������� � ����
void push(zap **s)
{
	zap *s1 = *s;
	do
	{
		if(!(*s = (zap *)calloc(1, sizeof(zap))))
		{
			puts("��� ��������� ������");
			return;
		}
		puts("������� ���������� � inf");
		fflush(stdin);
		gets((*s)->inf);
		(*s)->l = s1;
		s1 = *s;
		puts("���������� (y/n)");
		fflush(stdin);
	} while (getch() == 'y');
}

// ������� ��������� ��������� �����
void show(zap *s)
{
	if(!s)
	{
		puts("���� ����");
		return;
	}
	do
	{
		printf("    %s\n", s->inf);
		s = s->l;
	} while (s);
}

// ������� �������� ���������� �������� �����
// (� ������� �����)
char* pop(zap **s)
{
	zap *s1, ss;
	char st[50];
	strcpy(st, (*s)->inf);
	s1 = *s;       // ��������� �� ������� �����      
	ss = **s;      // ���������� ���������� ������� �����
	*s = (*s)->l;  // ��������� ����������� "����" �� �����
	free(s1);    // ������� � ������� �����
	return ss.inf;
}

