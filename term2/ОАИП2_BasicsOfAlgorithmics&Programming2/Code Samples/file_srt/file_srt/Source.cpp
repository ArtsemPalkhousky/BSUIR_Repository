#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <io.h>
  
  // �������� � ��������� ���� ����� � ��������� �� ����������
  //  ����� "����� �����"

//int main()
//{
//  setlocale(LC_ALL, "Russian");
//  FILE *f;
//  fpos_t n1, n2, n3;
//  int i1, i2, i3, m[] = { 1, 7, 4, 3, 1, 2, 5 };
//  if (!(f = fopen("aa", "w+")))
//  {
//	  puts("���� �� ����� ���� ������");
//	  return 0;
//  }
//  for (i1 = 0; i1<sizeof(m)/sizeof(int); i1++) fprintf(f, "%2d", m[i1]);
//  rewind(f);
//  while (1)
//  {
//	  fgetpos(f, &n1);        // ����� ��������� �����
//	  fscanf(f, "%d", &i1);   // �������� �����
//	  if (feof(f)) break;
//	  n3 = n1; i3 = i1;       // ��� �������� ������� �� ����� min ��������
//	  while (1)
//	  {
//		  fgetpos(f, &n2);      // ����� � ����� ' ' ��������������� �����
//		  fscanf(f, "%d", &i2); // �������� ����� ���������� ��� ���������
//		  if (i3>i2)           // ������� ����� (�������) ��������
//		  {
//			  n3 = n2;
//			  i3 = i2;
//		  }
//		  if (feof(f)) break;
//	  }
//	  if (n1 != n3)
//	  {
//		  fsetpos(f, &n3);      //
//		  fprintf(f, "%2d", i1); //
//		  fsetpos(f, &n1);      //
//		  fprintf(f, "%2d", i3); //
//	  }
//	  n1 += 2;
//	  fsetpos(f, &n1);      //
//  }
//  rewind(f);
//  while (1)
//  {
//	  fscanf(f, "%d", &i1);
//	  printf("%3d", i1);
//	  if (feof(f)) break;
//  }
//  printf("\n");
//  fclose(f);
//  return 0;
// }

//   -------------------------  ������ ������� ����� � ���� ------------
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	FILE *f;
//	fpos_t n1, n2, n3;
//	int i1, i2, i3, ii, m[] = { 1, 7, 4, 3, 1, 2, 5 };
//	if (!(f = fopen("aa", "w+")))
//	{
//		puts("���� �� ����� ���� ������");
//		return 0;
//	}
//	for (i1 = 0; i1<sizeof(m) / sizeof(int); i1++) fprintf(f, "%d ", m[i1]);
//	rewind(f);
//	while (1)
//	{
//		fgetpos(f, &n1);        // ����� ��������� �����
//		fscanf(f, "%d", &i1);   // �������� �����
//		if (feof(f)) break;
//		n3 = n1; i3 = i1;       // ��� �������� ������� �� ����� min ��������
//		while (1)
//		{
//			fgetpos(f, &n2);      // ����� � ����� ' ' ��������������� �����
//			n2++;
//			ii=fscanf(f, "%d", &i2); // �������� ����� ���������� ��� ���������
//			// if (ii == EOF) break;
//			if (feof(f)) break;
//			if (i3>i2)           // ������� ����� (�������) ��������
//			{
//				n3 = n2;
//				i3 = i2;
//			}
//		}
//		if (n1 != n3)
//		{
//			fsetpos(f, &n3);      //
//			fprintf(f, "%d ", i1); //
//			fsetpos(f, &n1);      //
//			fprintf(f, "%d ", i3); //
//		}
//		n1 += 2;
//		fsetpos(f, &n1);      //
//	}
//	rewind(f);
//	while (1)
//	{
//		fscanf(f, "%d", &i1);
//		printf("%3d", i1);
//		if (feof(f)) break;
//	}
//	printf("\n");
//	fclose(f);
//	return 0;
//}


//====================================================================

// �������� � ��������� ���� ����� � ��������� �� ����������
//  ����� "��������"

//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	FILE *f;
//	fpos_t n1, n2, n3;
//	int i1, i2, m[] = {7, 5, 1, 2, 3, 1 };
//	if (!(f = fopen("aa", "w+")))
//	{
//		puts("���� �� ����� ���� ������");
//		return 0;
//	}
//	for (i1 = 0; i1<sizeof(m)/sizeof(int); i1++) fprintf(f, "%2d", m[i1]);
//	// int nn = ftell(f);        //������ �����
//	rewind(f);
//	n1 = 0;                    // ������� ����� ���������� � ����������
//	while (n1<filelength(fileno(f)) - 2)
//	{
//		fseek(f, -4, 2);         // ����� � ������� �������������� �����
//		fgetpos(f, &n2);      // ���������� ����� � �����	
//		if (n1>n2) break;
//		while (1)
//		{
//			fscanf(f, "%d", &i1); // �������� ������� ����� ��� ���������
//			fscanf(f, "%d", &i2); // �������� ������� ����� ��� ���������
//			if (feof(f)) rewind(f);
//			if (i1>i2)           // ���� ������ i1 � i2
//			{
//				fsetpos(f, &n2);
//				fprintf(f, "%2d", i2);
//				fprintf(f, "%2d", i1);
//			}
//			n2 -= 2;              // ����� ��������� ���� �����
//			if (n1>n2) break;
//			fsetpos(f, &n2);     // ���� �� ��������� ����
//		}
//		n1 += 2;                // ���������� ������� ��������� �����
//	}
//	rewind(f);
//	while (1)
//	{
//		fscanf(f, "%d", &i1);
//		printf("%3d", i1);
//		if (feof(f)) break;
//	}
//	printf("\n");
//	fclose(f);
//	return 0;
//}

//==================================================================

// �������� � ��������� ���� ����� � ��������� �� ����������
//  ����� "�������"

//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	FILE *f;
//	fpos_t n1, n2, n3;
//	int i1, i2, i3, m[] = { 3, 1, 7, 2, 5, 1 };
//
//	if (!(f = fopen("aa", "w+")))
//	{
//		puts("���� �� ����� ���� ������");
//		return 0;
//	}
//	for (i1 = 0; i1<sizeof(m) / sizeof(int); i1++) fprintf(f, "%2d", m[i1]);
//	rewind(f);
//	fseek(f, 2, 0);
//	while (1)
//	{
//		fgetpos(f, &n1);
//		fscanf(f, "%d", &i1);  // ������� �������� ����� �� �����
//		if (feof(f)) rewind(f);
//		n2 = n1 - 2;
//		fsetpos(f, &n2);       // ����� �� 2 ����� � ������ �����
//		while (n2 >= 0)        // ���� �� ���������� ������ �����
//		{
//			fscanf(f, "%d", &i2); // �������� ����� ���������� ��� ���������
//			if (i1<i2)            // ����� �� i1 ������� ������� ��������
//			{
//				n2 += 2;    // ���������� ������ ��� ������ i2 (�� 2 ����� � �����)
//				fsetpos(f, &n2);    //
//				fprintf(f, "%2d", i2); // ����� i2 ������
//				n2 -= 2;   // ������� ����� (�� 2 ����� � ������)
//			}
//			else break;
//			n2 -= 2;       // � ������� ���������� �������� (� ������ �����)
//			if (n2 >= 0) fsetpos(f, &n2);  //
//		}
//		n2 += 2;
//		fsetpos(f, &n2);       //
//		fprintf(f, "%2d", i1); // ������� i1 � �������������� �������
//		n1 += 2;
//		if (n1 >= filelength(fileno(f))) break;
//		fsetpos(f, &n1);      // ������� � ������ ������ �������� i1
//	}
//	rewind(f);
//	while (1)
//	{
//		fscanf(f, "%d", &i1);
//		printf("%3d", i1);
//		if (feof(f)) break;
//	}
//	printf("\n");
//	fclose(f);
//	return 0;
//}


//====================================================================
// �������� � �������� ���� ����� � ��������� �� ����������
//  ����� "��������"

//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	FILE *f;
//	fpos_t n1, n2, n3;
//	int i1, i2, i3, m[] = { 1, 7, 2, 4, 1, 4, 1 };
//	if (!(f = fopen("aa", "w+b")))
//	{
//		puts("���� �� ����� ���� ������");
//		return 0;
//	}
//	fwrite(m, sizeof(m), 1, f);
//	rewind(f);
//	n3 = sizeof(int)*2;
//	n1 = 0;
//	while (1)
//	{   
//		fseek(f, -n3, 2);
//	    n2 = ftell(f);  
//		if (n1 > n2) break;
//		while (n1<=n2)
//		{
//			fsetpos(f, &n2);         // ������� ������������ �����
//			fread(&i1, sizeof(int), 1, f);   // �������� ����� ���������� ��� ���������
//			fread(&i2, sizeof(int), 1, f);   // �������� �����		 
//			if (i1>i2)              // ������
//			{
//				fsetpos(f, &n2);      // ������� ������������ �����
//				fwrite(&i2, sizeof(int), 1, f); // �������� �����
//				fwrite(&i1, sizeof(int), 1, f); // �������� ����� ���������� ��� ���������
//			}		
//			n2 -= sizeof(int);
//		}
//		n1 += sizeof(int);
//	}
//	rewind(f);
//	fread(m, sizeof(m), 1, f);
//	for (i1 = 0; i1<sizeof(m) / sizeof(int); printf("%3d", m[i1++]));
//	printf("\n");
//	fclose(f);
//	return 0;
//}



//====================================================================

// �������� � �������� ���� ����� � ��������� �� ����������
//  ����� "�������"

//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	FILE *f;
//	fpos_t n1, n2, n3;
//	int i1, i2, i3, m[] = { 2, 4, 3, 5, 1, 6 };
//	if (!(f = fopen("aa", "w+b")))
//	{
//		puts("���� �� ����� ���� ������");
//		return 0;
//	}
//	fwrite(m, sizeof(int), sizeof(m) / sizeof(int), f);
//	fseek(f, sizeof(int), 0);   // ���� �� ������ ������� �����
//	while (1)
//	{
//		fgetpos(f, &n1);       // ���������� ������� ������������ ��������
//		n3 = n1;
//		fread(&i1, sizeof(int), 1, f);  // ������� �������� ����� �� �����
//		if (feof(f)) break;    // ������� ��� �������� �����
//		n2 = n1 - sizeof(int);              // ������� ����������� ��������
//		fsetpos(f, &n2);       // ����� ���� �� ��� ������� (�� 1 int � ������ �����)
//		while (n2 >= 0)          // ���� �� ���������� ������ �����
//		{
//		    fgetpos(f, &n2);     // 
//			fread(&i2, sizeof(int), 1, f); // �������� ����� ���������� ��� ���������
//			if (i1<i2)           // ����� �� i1 ������� ������� ��������
//			{
//				n3 = n2;
//				n2 += sizeof(int);  // ���������� ������ ��� ������ i2
//				fsetpos(f, &n2);
//				fwrite(&i2, sizeof(int), 1, f); // ����� i2 ������ (� ����� �����)
//				n2 -= 2 * sizeof(int);
//				if (n2 >= 0) fsetpos(f, &n2);
//			}
//			else break;
//		}
//
//		fsetpos(f, &n3);              // ����� ���� � ������� n2
//		fwrite(&i1, sizeof(int), 1, f); // ������� i1 � �������������� �������
//
//		n1 += sizeof(int);     // ���������� ������� ���������� i1
//		if (n1 >= filelength(fileno(f))) break; // �������� �� ��������� �����
//		fsetpos(f, &n1);      // ���� �� ����� ������� i1 � ��������������
//	}
//	rewind(f);
//	printf("\n");
//	while (1)
//	{
//		fread(&i1, sizeof(int), 1, f);
//		if (feof(f)) break;
//		printf("%3d", i1);
//	}
//	printf("\n");
//	fclose(f);
//	return 0;
//}


//====================================================================
// �������� � �������� ���� ����� � ��������� �� ����������
//  ����� "��������"

int main()
{
	setlocale(LC_ALL, "Russian");
	FILE *f;
	int i1, i2, m[] = { 1, 4, 1, 3, 4, 5, 1, 6, 1, 7, 7 };
	fpos_t i, b, c, d;
	if (!(f = fopen("aa", "w+b")))
	{
		puts("���� �� ����� ���� ������");
		return 0;
	}
	fwrite(m, sizeof(m), 1, f);
	c = 0;
	b = ftell(f) - sizeof(int);   //����� �������� �� ������� ���������
	d = ftell(f) - sizeof(int);   //����� ���������� �������� ��� ���������� ������ ������
	rewind(f);
	while (c<=d)
	{
		i = d - sizeof(int);
		while (i>=c)
		{
			fsetpos(f, &i);         // ������� ������������ �����
			fread(&i1, sizeof(int), 1, f);   // �������� ����� ���������� ��� ���������
			fread(&i2, sizeof(int), 1, f);   // �������� �����		 
			if (i1>i2)              // ������
			{
				b = i;
				fsetpos(f, &i);      // ������� ������������ �����
				fwrite(&i2, sizeof(int), 1, f); // �������� �����
				fwrite(&i1, sizeof(int), 1, f); // �������� ����� ���������� ��� ���������
			}		
			i -= sizeof(int);
		}
		i = c = b + sizeof(int);
		while (i<d)
		{
			fsetpos(f, &i);         // ������� ������������ �����
			fread(&i1, sizeof(int), 1, f);   // �������� ����� ���������� ��� ���������
			fread(&i2, sizeof(int), 1, f);   // �������� �����		 
			if (i1>i2)              // ������
			{
				b = i;
				fsetpos(f, &i);      // ������� ������������ �����
				fwrite(&i2, sizeof(int), 1, f); // �������� �����
				fwrite(&i1, sizeof(int), 1, f); // �������� ����� ���������� ��� ���������
			}
			i += sizeof(int);
		}
		d = b;
	}
	rewind(f);
	fread(m, sizeof(m), 1, f);
	for (i1 = 0; i1<sizeof(m) / sizeof(int); printf("%3d", m[i1++]));
	printf("\n");
	fclose(f);
	return 0;
}

