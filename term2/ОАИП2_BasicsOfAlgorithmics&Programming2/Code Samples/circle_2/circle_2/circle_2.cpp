// ������ � ����� ��������
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
struct node
{
	char inf[50];  // �������������� ����
	node *l;       // ��������� �� ���������� ��������
	node *r;       // ��������� �� ��������� ��������
};

void show(node *);
void sozd(node **);
node *del(node *);
void srt(node *);
node *srt_uk(node *);
node *napr(char c, node * s);

int main()
{
	setlocale(LC_ALL, "Russian");
	node *h;         // ��������� �� '���������' ������� ������
	h = nullptr;
	char l;
	while (1)
	{
		puts("��� ��������: 1-������� ������");
		puts("              2-����� ����������� ������");
		puts("              3-�������� �������� �� ������");
		puts("              4-���������� (������� ��������� �� ��������)");
		puts("              5-���������� (������� ���������� ���������)");
		puts("              0-�����");
		fflush(stdin);
		switch (getch())
		{
		case '1': sozd(&h); break;
		case '2': show(h); break;
		case '3': del(h); break;
		case '4': if (h) h = srt_uk(h); break;
		case '5': if (h) srt(h); break;
		case '0': return 0;
		}
	}
	return 0;
}

// ������� ��������/���������� � ������
// ���������� ����������� ������ �� �������� ����� � ������
void sozd(node **h)
{
	node *s1, *s2;
	if (!*h)
	{
		if (!(s1 = (node *)malloc(sizeof(node))))
		{
			puts("��� ��������� ������");
			return;
		}
		puts("������� ���������� � inf");
		scanf("%s", s1->inf);
		s1->l = s1->r = s1;
		*h = s1;
	}
	else s1 = (*h)->r;      // ������ ��� ����������
	do
	{
		if (!(s2 = (node *)malloc(sizeof(node))))
		{
			puts("��� ��������� ������");
			return;
		}
		puts("������� ���������� � inf");
		scanf("%s", s2->inf);
		s1->l = s2;
		s2->r = s1;
		s1 = s2;
		puts("���������� (y/n): ");
		fflush(stdin);
	} while (getch() == 'y');
	s2->l = *h;
	(*h)->r = s2;
}

// ������� ������ ����������� ������
void show(node *s)
{
	node *s1;
	char p;
	if (!s)
	{  puts("������ ������"); 
	   return;
	}
	s1 = s;
	puts("r - �� �������, l - ������ �������\n");
	fflush(stdin);
	switch (p = getch())
	{
      case 'r': case 'R':
	  case 'l': case 'L':
		do
		{
			printf("%s\n", s1->inf);
			s1 = napr(p, s1);
		} while (s1 != s);
		break;
	}
	puts("����� ������ ��������");
	return;
}

// ������� �������� �������� ������
node *del(node *s)
{
	node *s1;    // ��������� �� ��������� ����
	char in[50];
	if (!s)
	{
		puts("������ ������"); return s;
	}
	s1 = s;
	puts("������� ���������� � ��������� ����");
	scanf("%s", in);
	do
	{
		if (strcmp(s1->inf, in)) s1 = s1->r;
		else
		{
			if (s1->r == s1)      // ���� � ������ ����
			{
				free(s1); return nullptr;
			}
			if (s == s1) s = s->r;  // ����� ����� ����� � ������
			s1->l->r = s1->r;    // ���������� ���� s1 �� ������
			s1->r->l = s1->l;
			free(s1);          // �������� ���� s1
			return s;
		}
	} while (1);
	printf("������ � ����������� = %s � ������ ��� \n", in);
	return s;
}

// ���������� ���������� � ������
void srt(node *s)
{
	node *s1, *s2;
	char a[50], c;
	int i;
	puts("����������� r - �� �������, l - ������ �������\n");
	fflush(stdin);
	c = getch();
	s1 = s;                      // �������� ������� ��� ������
	do
	{
		strcpy(a, s1->inf);     // �������� ������. ��� ������
		s2 = s1;
		do
		{
			s2 = napr(c, s2);         // ����� ���� ��� ���������
			if (strcmp(a, s2->inf)>0) // ��������� � ������
			{
				strcpy(s1->inf, s2->inf);
				strcpy(s2->inf, a);
				strcpy(a, s1->inf);
			}
		} while (napr(c, s2) != s);
		s1 = napr(c, s1);;
	} while (napr(c, s1) != s);
}

node *srt_uk(node *s)
{	node *s1, *s2, *s3;
	int i;
	s1 = s;
	do
	{	s2 = s1->r; s3 = s1;
		do
		{	if (strcmp(s3->inf, s2->inf)>0)
				s3 = s2;
			s2 = s2->r;
		} while (s2 != s);
		if (s3 != s1)
		{	if (s == s1) s = s3; // ������������� ������ ����� � ������
			s3->l->r = s3->r;    // ���������� ��������
			s3->r->l = s3->l;    // s3  �� ������
			s1->l->r = s3;       // ��������� ������� s3
			s3->r = s1;          // ����� s1
			s3->l = s1->l;
			s1->l = s3;
		}
		else
			s1 = s1->r;
	} while (s1->r != s);
	return s;
}

node *napr(char c, node *s)
{
	switch (c)
	{
	case 'r': case 'R': return s->r;
	case 'l': case 'L': return s->l;
	}
}
