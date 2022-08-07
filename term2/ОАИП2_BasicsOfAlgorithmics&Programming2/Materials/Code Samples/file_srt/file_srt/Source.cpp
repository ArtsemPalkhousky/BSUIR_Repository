#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <io.h>
  
  // записать в текстовый файл числа и выполнить их сортировку
  //  метод "через отбор"

//int main()
//{
//  setlocale(LC_ALL, "Russian");
//  FILE *f;
//  fpos_t n1, n2, n3;
//  int i1, i2, i3, m[] = { 1, 7, 4, 3, 1, 2, 5 };
//  if (!(f = fopen("aa", "w+")))
//  {
//	  puts("файл не может быть создан");
//	  return 0;
//  }
//  for (i1 = 0; i1<sizeof(m)/sizeof(int); i1++) fprintf(f, "%2d", m[i1]);
//  rewind(f);
//  while (1)
//  {
//	  fgetpos(f, &n1);        // адрес исходного числа
//	  fscanf(f, "%d", &i1);   // исходное число
//	  if (feof(f)) break;
//	  n3 = n1; i3 = i1;       // для контроля найдено ли новое min значение
//	  while (1)
//	  {
//		  fgetpos(f, &n2);      // адрес в файле ' ' предшествующего числу
//		  fscanf(f, "%d", &i2); // значение числа выбранного для сравнения
//		  if (i3>i2)           // найдено новое (меньшее) значение
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

//   -------------------------  второй вариант ввода в файл ------------
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	FILE *f;
//	fpos_t n1, n2, n3;
//	int i1, i2, i3, ii, m[] = { 1, 7, 4, 3, 1, 2, 5 };
//	if (!(f = fopen("aa", "w+")))
//	{
//		puts("файл не может быть создан");
//		return 0;
//	}
//	for (i1 = 0; i1<sizeof(m) / sizeof(int); i1++) fprintf(f, "%d ", m[i1]);
//	rewind(f);
//	while (1)
//	{
//		fgetpos(f, &n1);        // адрес исходного числа
//		fscanf(f, "%d", &i1);   // исходное число
//		if (feof(f)) break;
//		n3 = n1; i3 = i1;       // для контроля найдено ли новое min значение
//		while (1)
//		{
//			fgetpos(f, &n2);      // адрес в файле ' ' предшествующего числу
//			n2++;
//			ii=fscanf(f, "%d", &i2); // значение числа выбранного для сравнения
//			// if (ii == EOF) break;
//			if (feof(f)) break;
//			if (i3>i2)           // найдено новое (меньшее) значение
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

// записать в текстовый файл числа и выполнить их сортировку
//  метод "пузырька"

//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	FILE *f;
//	fpos_t n1, n2, n3;
//	int i1, i2, m[] = {7, 5, 1, 2, 3, 1 };
//	if (!(f = fopen("aa", "w+")))
//	{
//		puts("файл не может быть создан");
//		return 0;
//	}
//	for (i1 = 0; i1<sizeof(m)/sizeof(int); i1++) fprintf(f, "%2d", m[i1]);
//	// int nn = ftell(f);        //размер файла
//	rewind(f);
//	n1 = 0;                    // позиция числа выбранного к сортировке
//	while (n1<filelength(fileno(f)) - 2)
//	{
//		fseek(f, -4, 2);         // сдвиг в позицию предпослелнего числа
//		fgetpos(f, &n2);      // запоминаем адрес в файле	
//		if (n1>n2) break;
//		while (1)
//		{
//			fscanf(f, "%d", &i1); // значение первого числа для сравнения
//			fscanf(f, "%d", &i2); // значение второго числа для сравнения
//			if (feof(f)) rewind(f);
//			if (i1>i2)           // блок замены i1 с i2
//			{
//				fsetpos(f, &n2);
//				fprintf(f, "%2d", i2);
//				fprintf(f, "%2d", i1);
//			}
//			n2 -= 2;              // адрес следующей пары чисел
//			if (n1>n2) break;
//			fsetpos(f, &n2);     // УТПФ на следующую пару
//		}
//		n1 += 2;                // предвигаем позицию исходного числа
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

// записать в текстовый файл числа и выполнить их сортировку
//  метод "вставки"

//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	FILE *f;
//	fpos_t n1, n2, n3;
//	int i1, i2, i3, m[] = { 3, 1, 7, 2, 5, 1 };
//
//	if (!(f = fopen("aa", "w+")))
//	{
//		puts("файл не может быть создан");
//		return 0;
//	}
//	for (i1 = 0; i1<sizeof(m) / sizeof(int); i1++) fprintf(f, "%2d", m[i1]);
//	rewind(f);
//	fseek(f, 2, 0);
//	while (1)
//	{
//		fgetpos(f, &n1);
//		fscanf(f, "%d", &i1);  // выбрано исходное число из файла
//		if (feof(f)) rewind(f);
//		n2 = n1 - 2;
//		fsetpos(f, &n2);       // сдвиг на 2 байта к началу файла
//		while (n2 >= 0)        // пока не достигнуто начало файла
//		{
//			fscanf(f, "%d", &i2); // значение числа выбранного для сравнения
//			if (i1<i2)            // слева от i1 найдено большее значение
//			{
//				n2 += 2;    // вычисление адреса для записи i2 (на 2 байте в конец)
//				fsetpos(f, &n2);    //
//				fprintf(f, "%2d", i2); // сдвиг i2 вправо
//				n2 -= 2;   // возврат назад (на 2 байта в начало)
//			}
//			else break;
//			n2 -= 2;       // в позицию следующего элемента (к началу файла)
//			if (n2 >= 0) fsetpos(f, &n2);  //
//		}
//		n2 += 2;
//		fsetpos(f, &n2);       //
//		fprintf(f, "%2d", i1); // вставка i1 в освободившуюся позицию
//		n1 += 2;
//		if (n1 >= filelength(fileno(f))) break;
//		fsetpos(f, &n1);      // переход к выбору нового значения i1
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
// записать в бинарный файл числа и выполнить их сортировку
//  метод "пузырька"

//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	FILE *f;
//	fpos_t n1, n2, n3;
//	int i1, i2, i3, m[] = { 1, 7, 2, 4, 1, 4, 1 };
//	if (!(f = fopen("aa", "w+b")))
//	{
//		puts("файл не может быть создан");
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
//			fsetpos(f, &n2);         // позиция считываемого числа
//			fread(&i1, sizeof(int), 1, f);   // значение числа выбранного для сравнения
//			fread(&i2, sizeof(int), 1, f);   // исходное число		 
//			if (i1>i2)              // замена
//			{
//				fsetpos(f, &n2);      // позиция считываемого числа
//				fwrite(&i2, sizeof(int), 1, f); // исходное число
//				fwrite(&i1, sizeof(int), 1, f); // значение числа выбранного для сравнения
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

// записать в бинарный файл числа и выполнить их сортировку
//  метод "вставки"

//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	FILE *f;
//	fpos_t n1, n2, n3;
//	int i1, i2, i3, m[] = { 2, 4, 3, 5, 1, 6 };
//	if (!(f = fopen("aa", "w+b")))
//	{
//		puts("файл не может быть создан");
//		return 0;
//	}
//	fwrite(m, sizeof(int), sizeof(m) / sizeof(int), f);
//	fseek(f, sizeof(int), 0);   // УТПФ на второй элемент файла
//	while (1)
//	{
//		fgetpos(f, &n1);       // запоминаем позицию считываемого элемента
//		n3 = n1;
//		fread(&i1, sizeof(int), 1, f);  // выбрано исходное число из файла
//		if (feof(f)) break;    // выбраны все элементы файла
//		n2 = n1 - sizeof(int);              // позиция предыдущего элемента
//		fsetpos(f, &n2);       // сдвиг УТПФ на эту позицию (на 1 int к началу файла)
//		while (n2 >= 0)          // пока не достигнуто начало файла
//		{
//		    fgetpos(f, &n2);     // 
//			fread(&i2, sizeof(int), 1, f); // значение числа выбранного для сравнения
//			if (i1<i2)           // слева от i1 найдено большее значение
//			{
//				n3 = n2;
//				n2 += sizeof(int);  // вычисление адреса для записи i2
//				fsetpos(f, &n2);
//				fwrite(&i2, sizeof(int), 1, f); // сдвиг i2 вправо (к концу файла)
//				n2 -= 2 * sizeof(int);
//				if (n2 >= 0) fsetpos(f, &n2);
//			}
//			else break;
//		}
//
//		fsetpos(f, &n3);              // сдвиг УТПФ в позицию n2
//		fwrite(&i1, sizeof(int), 1, f); // вставка i1 в освободившуюся позицию
//
//		n1 += sizeof(int);     // вычисление позиции следующего i1
//		if (n1 >= filelength(fileno(f))) break; // проверка на окончание файла
//		fsetpos(f, &n1);      // УТПФ на новый элемент i1 к упорядочиванию
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
// записать в бинарный файл числа и выполнить их сортировку
//  метод "пузырька"

int main()
{
	setlocale(LC_ALL, "Russian");
	FILE *f;
	int i1, i2, m[] = { 1, 4, 1, 3, 4, 5, 1, 6, 1, 7, 7 };
	fpos_t i, b, c, d;
	if (!(f = fopen("aa", "w+b")))
	{
		puts("файл не может быть создан");
		return 0;
	}
	fwrite(m, sizeof(m), 1, f);
	c = 0;
	b = ftell(f) - sizeof(int);   //номер элемента на котором остановка
	d = ftell(f) - sizeof(int);   //номер стартового элемента для сортировки справа налево
	rewind(f);
	while (c<=d)
	{
		i = d - sizeof(int);
		while (i>=c)
		{
			fsetpos(f, &i);         // позиция считываемого числа
			fread(&i1, sizeof(int), 1, f);   // значение числа выбранного для сравнения
			fread(&i2, sizeof(int), 1, f);   // исходное число		 
			if (i1>i2)              // замена
			{
				b = i;
				fsetpos(f, &i);      // позиция считываемого числа
				fwrite(&i2, sizeof(int), 1, f); // исходное число
				fwrite(&i1, sizeof(int), 1, f); // значение числа выбранного для сравнения
			}		
			i -= sizeof(int);
		}
		i = c = b + sizeof(int);
		while (i<d)
		{
			fsetpos(f, &i);         // позиция считываемого числа
			fread(&i1, sizeof(int), 1, f);   // значение числа выбранного для сравнения
			fread(&i2, sizeof(int), 1, f);   // исходное число		 
			if (i1>i2)              // замена
			{
				b = i;
				fsetpos(f, &i);      // позиция считываемого числа
				fwrite(&i2, sizeof(int), 1, f); // исходное число
				fwrite(&i1, sizeof(int), 1, f); // значение числа выбранного для сравнения
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

