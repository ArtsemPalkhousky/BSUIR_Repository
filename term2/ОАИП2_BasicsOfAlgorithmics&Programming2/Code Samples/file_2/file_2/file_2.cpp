#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <io.h>

//int main()
//{
//  setlocale(LC_ALL, "Russian");
//  FILE *f;
//  int ms[] = { 5, 7, 10, 13, 14 };
//  int i, j;
//  fpos_t l1, l2;              // ��� ������� � �����
//  f = fopen("aaa", "w+b");
//  fwrite(ms, sizeof(int), sizeof(ms) / sizeof(int), f); //
//  while (1)
//  {
//	scanf("%d", &i);
//	if (i == 999) break;            // ����� �� ���������
//	rewind(f);	                    // ��������� ���� � ������ ����� � �����
//	do                              // �������� ����� �����
//	{
//	    fgetpos(f, &l1);            // ���� �������� ���� ������������ �����
//	    fread(&j, sizeof(int), 1, f);
//		if (feof(f) || j>i)  break; // ��������� ����� ����� ��� ������� �����
//		                          	// ������� ��� ��������� � ����������.
//	} while (1);
//	rewind(f);
//	if (j<i)                      // EOF � � ����� ��� ����� > ��� ���������
//	{
//		fseek(f, 0, 2);               // ����� �� ����� �����
//		fwrite(&i, sizeof(int), 1, f); // �������� � ����� �����
//		continue;
//	}
//	fseek(f, -sizeof(int), 2);     // ���� �� ��������� ������� �����
//	do
//	{
//		fgetpos(f, &l2);            // ����� ���� ����� � ������� ��
//		fread(&j, sizeof(int), 1, f); // l2 ������� ���� ����� ������� > ��� i
//		rewind(f);
//		l2 += sizeof(int);
//		fsetpos(f, &l2);
//		fwrite(&j, sizeof(int), 1, f);
//		fseek(f, l2 - 2 * sizeof(int), 0);
//	} while (l1<l2 - sizeof(int));
//	fseek(f, l2 - sizeof(int), 0);
//	fwrite(&i, sizeof(int), 1, f);    // ������ i �� ����� ����� � ���������
//  }	                               // ���������� ����� ���� ����� ����
//  rewind(f);
//  do
//  {
//	  fread(&j, sizeof(int), 1, f);
//	  if(feof(f))  break;
//	  printf("%3d", j);
//  } while (1);
//  printf("\n");
//  fclose(f);
//  return 0;
//}

//============================================================================================

// ������� 2 �����(aa � bb) ��� ����������� �� �����������,
// ���������� �� � �������������� ��� ��������� ���������������

//int main()
//{
//  setlocale(LC_ALL, "Russian");
//  FILE *f1, *f2, *f3;
//  int i1, i2;
//  int m1[] = { 1, 2, 4, 5 },
//	  m2[] = { 1, 3 };
//	  char cc;
//  if (!(f1 = fopen("a", "w+b")) ||
//	  !(f2 = fopen("aa", "wb+")) ||
//	  !(f3 = fopen("aaa", "wb")))
//  {
//	  puts("error");
//	  return 0;
//  }
//  for (i1 = 0; i1<sizeof(m1) / sizeof(int); i1++) fwrite(&m1[i1], sizeof(int), 1, f1);
//  fwrite(m2, sizeof(m2), 1, f2);
//
//  rewind(f1); rewind(f2);
//  fread(&i1, sizeof(int), 1, f1);
//  fread(&i2, sizeof(int), 1, f2);
//  do
//  {
//	  while (!feof(f1) && i1<i2)
//	  {
//		  fwrite(&i1, sizeof(int), 1, f3);
//		  fread(&i1, sizeof(int), 1, f1);
//	  }
//	  if (feof(f1)) break;
//
//	  while (!feof(f2) && i1 >= i2)
//	  {
//		  fwrite(&i2, sizeof(int), 1, f3);
//		  fread(&i2, sizeof(int), 1, f2);
//	  }
//  } while (!feof(f2));
//
//  while (!feof(f1))
//  {
//	  fwrite(&i1, sizeof(int), 1, f3);
//	  fread(&i1, sizeof(int), 1, f1);
//  }
//
//  while (!feof(f2))
//  {
//	  fwrite(&i2, sizeof(int), 1, f3);
//	  fread(&i2, sizeof(int), 1, f2);
//  }
//
//  fclose(f1);
//  fclose(f2);
//  fclose(f3);
//
//  f3 = fopen("aaa", "rb");
//  while (1)
//  {
//	  fread(&i1, sizeof(int), 1, f3);
//	  if (feof(f3)) break;
//	  printf("%3d", i1);
//  }
//  printf("\n");
//  return 0;
//}

//============================================================================================

// ������� 2 ����� (aa � bb) �� ����������� � �� ��������
// ���������� �� � �������������� ��� ��������� ���������������

//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	FILE *f1, *f2, *f3;
//	int i1, i2, k, kk;
//	fpos_t n;
//	int m1[] = { 1, 2 },
//		m2[] = { 7, 5, 4, 3, 1 };
//	char cc;
//	if (!(f1 = fopen("a", "w+b")) ||
//		!(f2 = fopen("aa", "wb+")) ||
//		!(f3 = fopen("aaa", "wb")))
//	{
//		puts("error");
//		return 0;
//	}
//	for (i1 = 0; i1<sizeof(m1) / sizeof(int); i1++) fwrite(&m1[i1], sizeof(int), 1, f1);
//	fwrite(m2, sizeof(m2), 1, f2);
//
//	rewind(f1);
//	fread(&i1, sizeof(int), 1, f1);
//	k = sizeof(int);
//	fseek(f2, -k, 2);  
//	fgetpos(f2, &n);
//	fread(&i2, sizeof(int), 1, f2);
//	do
//	{
//		while (!feof(f1) && i1<i2)
//		{
//			fwrite(&i1, sizeof(int), 1, f3);
//			fread(&i1, sizeof(int), 1, f1);
//		}
//		if (feof(f1)) break;
//
//		while (n >= 0 && i1 >= i2)
//		{
//			fwrite(&i2, sizeof(int), 1, f3);
//			fseek(f2, -k * 2, 1);
//			fgetpos(f2, &n);
//			if (n<0) break;
//			fread(&i2, sizeof(int), 1, f2);
//		}
//	} while (n >= 0);
//
//	while (!feof(f1))
//	{
//		fwrite(&i1, sizeof(int), 1, f3);
//		fread(&i1, sizeof(int), 1, f1);
//	}
//
//	while (n >= 0)
//	{
//		fwrite(&i2, sizeof(int), 1, f3);
//		if (n<=0) break;
//		fseek(f2, -k*2, 1);
//		fgetpos(f2, &n);
//		fread(&i2, sizeof(int), 1, f2);
//	}
//
//	fclose(f1);
//	fclose(f2);
//	fclose(f3);
//
//	f3 = fopen("aaa", "rb");
//	while (1)
//	{
//		fread(&i1, sizeof(int), 1, f3);
//		if (feof(f3)) break;
//		printf("%3d", i1);
//	}
//	printf("\n");
//	return 0;
//}


//============================================================================================


#include <stdlib.h>
#include <string.h>

void add(char *);
void del(char *);
void print(char *);
void swap(FILE *ff, struct str, struct str, fpos_t *, fpos_t *);
void zamena(char *);

struct inf {
	char tp[15];        // ��������
	unsigned short pr;  // ���������
};
struct str {
	inf in;
	double hd;          // HDD
	int mem;            // ������
};

int main()
{
	setlocale(LC_ALL, "Russian");
	FILE *f;
	char name[] = "baza.txt";
	int i, k, pl;
	while (1)
	{
		puts("\n1- add \n2- \n3-del \n4-print \n5-end\n �������� ����� ������");
		scanf("%d", &k);
		switch (k)
		{
			case 1: add(name); break;
			case 3: del(name); break;
			case 2: zamena(name); break;
			case 4: print(name); break;
			case 5: return 0;
		}
	}
	return 0;
}

void add(char *name)
{
	double a;
	str *s;
	FILE *f;
	if ((f = fopen(name, "ab")) == nullptr)
	{
		puts(" ������  �������� �����");
		return;
	}
	if ((s = (str *)calloc(1, sizeof(str))) == NULL)
	{
		puts("������ ��� ��������� ������");
		fclose(f);
		return;
	}
	do
	{
		fflush(stdin);
		puts("������� ��� ���������� ");
		gets(s->in.tp); if (!strcmp(s->in.tp, "")) break;
		puts("������� ������� ����. , �����  HDD   �  ������");
		scanf("%d", &(s->in.pr));
		scanf("%lf", &a);        // ???????/
		s->hd = a;
		scanf("%d", &s->mem);
		fwrite(s, sizeof(str), 1, f);   // �������� ��������� � ����� �����
	} while (1);
	fclose(f);
}

void del(char *name)
{
	FILE *f;
	str st, stt;
	long l;
	if ((f = fopen(name, "r+b")) == nullptr)
	{
		puts(" ������  �������� �����");
		return;
	}
	puts("\n������� ��� ���������� : "); scanf("%s", st.in.tp);
	puts("\n������� ������� ����.  : "); scanf("%d%", &st.in.pr);
	puts("\n������� �����  HDD     : "); scanf("%lf", &st.hd);
	puts("\n������� �����  ������  : "); scanf("%d",  &st.mem);
	do
	{
		fread(&stt, sizeof(str), 1, f);
		if (feof(f)) break;
		if (!strcmp(st.in.tp, stt.in.tp) && st.in.pr == stt.in.pr &&
			st.hd == stt.hd && st.mem == stt.mem)
		{                  // ������� ��������� ���������   sst
			do
			{
				fread(&stt, sizeof(str), 1, f);          // ������ ��������� ���-��
				if (feof(f)) break;
				l = ftell(f);                            // ������� �� ���������
				fseek(f, l - (long)(2 * sizeof(str)), 0);// �� 2 ���-�� ����� � ������ �����
				fwrite(&stt, sizeof(str), 1, f);         // � ������ ��������� ��-��
				fseek(f, l, 0);                          // ������� � ������� L
			} while (!feof(f));
		}
	} while(1);
	rewind(f);
	fseek(f, -sizeof(str), 2);
	l = ftell(f);
	chsize(fileno(f),l);
	fclose(f);
}

void print(char *name)
{
	FILE *f;
	str st;
	int k = 0;
	if ((f = fopen(name, "rb")) == nullptr)
	{
		puts(" ������  �������� �����");
		return;
	}
	puts("   ��� ����������    ���������     HDD    RAM");
	do
	{
		k++;              // ������� ����� ���������� �� ����� �������
		fread(&st, sizeof(str), 1, f);
		if (feof(f)) break;
		if (k >= 10)         // �������� 5 �������
		{
			k = 0;             // ����� �������
			getch();         // �������� ������ �� �����
			puts("   ��� ����������    ���������     HDD    RAM");
		}
		printf("\n%20s%10d%8.2lf%8d", st.in.tp, st.in.pr, st.hd, st.mem);
	} while (!feof(f));
	fclose(f);
}

void zamena(char *name)
{
	FILE *f;
	str st1,st2;
	fpos_t n1, n2;
	int k = 0;
	if ((f = fopen(name, "r+b")) == nullptr)
	{
		puts(" ������  �������� �����");
		return;
	}
	do
	{ 
		fgetpos(f,&n1);
		k=fread(&st1, sizeof(str), 1, f);
		if (feof(f)) break;
		fgetpos(f, &n2);
		k=fread(&st2, sizeof(str), 1, f);
		if (feof(f)) break;
		swap(f, st1, st2, &n1, &n2);
		n1 = n2 + sizeof(str);
		fsetpos(f,&n1);
	} while (1);
	fclose(f);
}

void swap(FILE *ff, struct str s1, struct str s2, fpos_t *l1, fpos_t *l2)
{
	if (!ff) return;
	fsetpos(ff, l1);
	fwrite(&s2, sizeof(str), 1, ff);    // ������ ���-�� �� ������� ������
	fsetpos(ff, l2);
	fwrite(&s1, sizeof(str), 1, ff);    // ������ ���-�� �� ������� ������
}

