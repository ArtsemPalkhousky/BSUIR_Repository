#include<ctime>
#include <iostream>
#include <chrono>
#include "Timer.h"
#include <iomanip>


const int m = 16;
const int n = 16;
const int iter = 1000000;
using namespace std;

int main()
{
	int a[n][m], b[n][m], c[n][m], i, j;
	double result = 0.0;

	cout << "matrica a:\n";
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			a[i][j] = rand() % 20;
			cout << a[i][j] << '\t';
		}
		cout << endl;
	}


	cout << "\nmatrica b:\n";
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			b[i][j] = rand() % 20;
			cout << b[i][j] << '\t';
		}
		cout << endl;
	}
	cout << endl;


	cout << "|" << setw(11) << "C++" << "|" << setw(11) << "ASM" << "|" << setw(11) << "MMX" << "|" << setw(11) << "XMM" << "|" << endl;

	do {
		Timer t;
		for (size_t k = 0; k < iter; k++)
		{
			for (i = 0; i < n; i++)
			{
				for (j = 0; j < m; j++)
				{
					c[i][j] = a[i][j] - b[i][j];
				}
			}
		}
		cout << "|" << fixed << setprecision(9) << t.elapsed() << endl;
		
		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < m; j++)
			{
				cout << "|" << setw(6) << c[i][j];
			}
			cout << "|" << endl;
		}

		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < m; j++)
			{
				c[i][j] = 0;
			}
		}

		t.reset();
		for (size_t k = 0; k < iter; k++)
		{
			for (i = 0; i < n; i++)
			{
				for (j = 0; j < m; j++)
				{
					int q = a[i][j];
					int w = b[i][j];
					int e = c[i][j];
					__asm
					{
						mov eax, q
						sub eax, w
						mov e, eax
					}
					c[i][j] = e;
				}
			}
		}
		cout << "|" << fixed << setprecision(9) << t.elapsed() << endl;
		
		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < m; j++)
			{
				cout << "|" << setw(6) << c[i][j];
			}
			cout << "|" << endl;
		}

		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < m; j++)
			{
				c[i][j] = 0;
			}
		}

		int64_t temp64a;
		int* pointerTemp64a = (int*)&temp64a;
		int64_t temp64b;
		int* pointerTemp64b = (int*)&temp64b;
		int64_t temp64c;
		int* pointerTemp64c = (int*)&temp64c;
		
		t.reset();
		for (size_t k = 0; k < iter; k++)
		{
			for (i = 0; i < n;i++)
			{
				for (j = 0; j < m;j++)
				{
					pointerTemp64a[0] = (a[i][j]);
					pointerTemp64a[1] = (a[i][j + 1]);
					pointerTemp64b[0] = (b[i][j]);
					pointerTemp64b[1] = (b[i][j + 1]);
					__asm
					{
						movq mm0, temp64a
						psubq mm0, temp64b
						movq temp64c, mm0
						EMMS
					}
					c[i][j++] = *(pointerTemp64c);
					c[i][j] = *((pointerTemp64c)+1);
				}
			}
		}
		cout << "|" << fixed << setprecision(9) << t.elapsed() << endl;
		
		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < m; j++)
			{
				cout << "|" << setw(6) << c[i][j];
			}
			cout << "|" << endl;
		}
		//__int128 temp128a;
		//int* pointerTemp128a = (int*)&temp128a;
		//__int128 temp128b;
		//int* pointerTemp128b = (int*)&temp128b;
		//__int128 temp128c;
		//int* pointerTemp128c = (int*)&temp128c;
		//for (int d = 0; d < iter; d++) {
		//	for (int i = 0; i < n; i++) {
		//		for (int j = 0; j < m; j++) {
		//			pointerTemp128a[0] = (a[i][j]);
		//			pointerTemp128a[1] = (a[i][j + 1]);
		//			pointerTemp128a[2] = (a[i][j + 2]);
		//			pointerTemp128a[3] = (a[i][j + 3]);
		//			pointerTemp128b[0] = (b[i][j]);
		//			pointerTemp128b[1] = (b[i][j + 1]);
		//			pointerTemp128b[2] = (b[i][j + 2]);
		//			pointerTemp128b[3] = (b[i][j + 3]);
		//			t.reset();
		//			__asm {
		//				movups xmm0, temp128a
		//				subps xmm0, temp128b
		//				movups temp128c, xmm0
		//			}
		//			c[i][j++] = *(pointerTemp128c);
		//			c[i][j++] = *((pointerTemp128c)+1);
		//			c[i][j++] = *((pointerTemp128c)+2);
		//			c[i][j] = *((pointerTemp128c)+3);
		//		}
		//	}
		//}
		//cout << '|' << fixed << setprecision(9) << t.elapsed() << '|';

		if (getchar() == 'q') 
		{
			break;
		}
	} while (true);

	return 0;
}