// ��������������� �������
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
struct zap
{
	char inf[50];
	zap *pr;   // ��������� �� ������. ��-�
	zap *nx;   // ��������� �� �������. ��-�
};
void add(zap **, zap **);
void insert(zap **);
void del_any(zap **, zap **, char *);
void see(zap *, int);
void sort(zap **, zap **);

int main()
{
	setlocale(LC_ALL, "Russian");
	zap *t, *h;         // ��������� �� ����� � ������ �������
	char l, *st;
	st = (char *)malloc(10);
	t = h = nullptr;
	while (1)
	{
		puts("��� ��������: 1-������� �������");
		puts("              2-����� ����������� �������");
		puts("              3-������� ������ �������� � �������");
		puts("              4-�������� ������ �������� �� �������");
		puts("              5-���������� �������");
		puts("              0-��������");
		fflush(stdin);
		switch (getch())
		{
		case '1': add(&t, &h); break;
		case '2':
			puts("0-�������� � ������\n1- �������� � ������");
			l = getch();
			if (l == '0') see(t, 0);  // �������� � ������ �������
			else see(h, 1);        // �������� � ������ �������
			break;
		case '3': if (t)         // ������� �� �����
			insert(&t);           // ���������� �� ������ �������
			break;
		case '4': if (t)
		{
					  gets(st);
					  del_any(&t, &h, st);
		} break;
		case '5': if (t) sort(&t, &h); break;
		case '0': return 0;
		default: printf("������, ��������� \n");
		}
	}
}

// ������� �������� �������  � ���������� (������) � ����� �������
void add(zap **pt, zap **ph)
{
	zap *n;
	puts("�������� ������� \n");
	do
	{
		if (!(n = (zap *)calloc(1, sizeof(zap))))
		{
			puts("��� ��������� ������");
			return;
		}
		puts("������� ���������� � inf");
		scanf("%s", n->inf);
		if (!*pt || !*ph)   // ������� ��� �� �������
		{
			*pt = n;          // ��������� �� ����� �������
			*ph = n;          // ��������� �� ������ �������
		}
		else
		{
			n->nx = *pt;     // ��������� �� ������� (�����) �������
			(*pt)->pr = n;   // ����� ��������� �� ����� �������
			*pt = n;         // ����������� ��������� ������ �� ����� �������
		}
		puts("���������� (y/n): ");
		fflush(stdin);
	} while (getch() == 'y');
}

// ������� ������ ����������� �������
// ����� �������� � ������ (i==0) ��� ������ (i==1)
void see(zap *p, int i)
{
	puts("����� ����������� ������� \n");
	if (!p)
	{
		puts("������� �����");
		return;
	}
	do
	{
		printf("%s\n", p->inf);
		if (!i) p = p->nx;  // �������� � ������ �������
		else p = p->pr;    // �������� � ������ �������
	} while (p);
	return;
}

// ������� ���������� �������� � �������  (�� ������ �������)
// ���������� �������� ��������� ������ ���� ������� �����������
// � ������ �� �����������  [ (�����) 1 2 5 7 9 (������)  �������� 4 ]
void insert(zap **ptr)
{
	zap *p = *ptr, *n;
	char s[50];
	puts("������� ���������� � ��� ����������\n");
	gets(s);
	while (p && strcmp(p->inf, s)<0) p = p->nx;
	if (!(n = (zap *)calloc(1, sizeof(zap))))
	{
		puts("��� ��������� ������");
		return;
	}
	strcpy(n->inf, s);       // �������� s n->inf
	p->pr->nx = n;    // ���������� ��-� ������� ��������� �� �������� ��-� (n)
	n->nx = p;        // ����� ������� ��������� �� ���������. ������� ������� p
	n->pr = p->pr;	  // ����� ������� ��������� �� ���������. ������� ������� p
	p->pr = n;        // ����������� ��-� ������� ��������� �� �������� ��-�
}

// ������� �������� ������ ������ �������� �������
// pt- ��������� �� �����  ph- �� ������ �������
void del_any(zap **pt, zap **ph, char *st)
{
	zap *p = *pt;
	if (!*pt || !*ph)
	{
		puts("������� �����");
		return;
	}
	if (p->nx == NULL &&       // � ������� ������ ���� �������
		(!strcmp(p->inf, st) || *st == '\0'))
	{
		free(p);
		*pt = *ph = nullptr;       // ������� �����
		return;
	}
	while (p && strcmp(p->inf, st)) p = p->nx;
	if (!strcmp(p->inf, st))  // ������ ������� �� �������  st
	{
		if (p == *pt)             // ��������� ������� - ����� �������
		{
			*pt = (*pt)->nx;       // ����� ��������� �� ����� �������
			(*pt)->pr = nullptr;
		}
		else if (p == *ph)        // ��������� ������� - ������ �������
		{
			*ph = (*ph)->pr;      // ����� ��������� �� ������ �������
			(*ph)->nx = nullptr;
		}
		else
		{
			p->pr->nx = p->nx;     // ������� �������  pr
			p->nx->pr = p->pr;
		}
		free(p);                // ������� �������  pr  �������
	}
}

// ������� ���������� ����������� �������
void sort(zap **t, zap **h)
{
	zap *s1, *s2, *s3;

	for (s2 = *h; s2; s2 = s2->pr)
	for (s1 = *t; s1->nx; s1 = s1->nx)
	{
		if (strcmp(s1->nx->inf, s1->inf)>0)
		{
			s3 = s1->nx;                   // s3- ������� ��������� �� s1
			if (!s1->pr) *t = s1->nx;       // ����������� ������ �������
			s1->nx = s1->nx->nx;           // s1-nx ��������� ����� �������
			if (s1->nx) s1->nx->pr = s1;    // s1->nx ���� ��� �������������
			else s2 = *h = s1;               // s1->nx==NULL -��������� ������
			s3->pr = s1->pr;
			s3->nx = s1;
			if (s3->pr) s3->pr->nx = s3;
			s1->pr = s3;
			s1 = s1->pr;                   // ����� ��� s1=s1->nx � ����� for
		}
	}
	puts("���������� ���������");
}
