#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <stdio.h>

int ERROR;
int Catoi(char s) {
	switch (s) {
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	case 'T': return 10;
	case 'J': return 11;
	case 'Q': return 12;
	case 'K': return 13;
	case 'A': return 14;
	}
};

struct codeCARD {
	char maste;
	int rang;
};

struct combinations {
	struct codeCARD card[50];
	short int massivRang[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	short int massivMaste[4] = { 0, 0, 0, 0 };
	short int result_Combination[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
};

void print_Results(int index) {
	switch (index) {
	case 1: {printf("Старшая карта"); break; }
	case 2: {printf("Пара"); break; }
	case 3: {printf("Две пары"); break; }
	case 4: {printf("Сет"); break; }
	case 5: {printf("Стрит"); break; }
	case 6: {printf("Флеш"); break; }
	case 7: {printf("Фулл Хаус"); break; }
	case 8: {printf("Карэ"); break; }
	case 9: {printf("Стрит Флеш"); break; }
	case 10: {printf("Флеш Рояль"); break; }
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");
	printf("Колода состоит из 50 карт.\n");
	struct combinations* pokerPlayer;
	unsigned int maxI;
	puts("Введите количество игроков\n");
	while (!scanf_s("%u", &maxI)) rewind(stdin);
	pokerPlayer = (struct combinations*) calloc(maxI, sizeof(struct combinations));
	int* records;
	records = (int*)calloc(maxI, sizeof(int));
	int* noCards = (int*)calloc(maxI, sizeof(int));
	char checking;
	int i = 0;
	int a;
	int I;
	int checkRepeat = 0;
	//-----------------------------------------------Ввод-------------------------------------------------------------------
	for (I = 0; I < maxI; I++) {
		printf("%d-ый игрок\n", I+1);
		do
		{
			ERROR = 0;
			printf("Card №%d\n\n", records[I] + 1);
			puts("Введите ранг карты (2,3,4,5,6,7,8,9,T,J,Q,K,A:) ");
			rewind(stdin);
			checking = getchar();
			if (Catoi(checking) > 14 || Catoi(checking) < 2)
			{
				printf("Такой карты не существует\n");
				ERROR = 1;
			}
			else {
				pokerPlayer[I].card[records[I]].rang = Catoi(checking);
			}

			if (ERROR == 0) {
				puts("Введите масть (C S H D):");
				rewind(stdin);
				checking = getchar();
				if (checking != 'C' && checking != 'S' && checking != 'H' && checking != 'D')
				{
					printf("Такой карты не существует\n");
					ERROR = 1;
				}
				else
					pokerPlayer[I].card[records[I]].maste = checking;
			}

			if (ERROR == 0)
				for (i = 0; i < records[I]; i++) {
					if (pokerPlayer[I].card[records[I]].rang == pokerPlayer[I].card[i].rang)
						if (pokerPlayer[I].card[records[I]].maste == pokerPlayer[I].card[i].maste) {
							printf("НАРУШЕНИЕ!!!!! ERRRORRR. Повторная карта была обнаружена.");
							system("PAUSE");
							ERROR = 1;
							break;
						}
				}

			if (ERROR == 1) {
				puts("Переписать? (Да/нет) (1/0)");
				rewind(stdin);
				scanf_s("%d", &a);
				if (a == 1)
					continue;
				else
					break;
			}
			else {
				records[I]++;
				if (records[I] == 5) {
					system("CLS");
					break;
				}
			}
			puts("\n\n");
		} while (1);
		if (records[I] == 0)
			noCards[I] = 1;
	}


	//-----------------------------------------------Вывод------------------------------------------------------------------
	for (I = 0; I < maxI; I++) {
		printf("Рука %d-ого игрока:  %d карт(а/ы)\n", I + 1, records[I]);
		for (i = 0; i < records[I]; i++)
		{
			printf("%d. card: ", i + 1);
			switch (pokerPlayer[I].card[i].rang) {
			case 2: {printf("Two of "); pokerPlayer[I].massivRang[0]++; break; }
			case 3: {printf("Three of "); pokerPlayer[I].massivRang[1]++; break; }
			case 4: {printf("Four of "); pokerPlayer[I].massivRang[2]++; break; }
			case 5: {printf("Five of "); pokerPlayer[I].massivRang[3]++; break; }
			case 6: {printf("Six of "); pokerPlayer[I].massivRang[4]++; break; };
			case 7: {printf("Seven of ");  pokerPlayer[I].massivRang[5]++; break; };
			case 8: {printf("Eight of ");  pokerPlayer[I].massivRang[6]++; break; };
			case 9: {printf("Nine of "); pokerPlayer[I].massivRang[7]++; break; };
			case 10: {printf("Ten of ");  pokerPlayer[I].massivRang[8]++; break; };
			case 11: {printf("Jack of ");  pokerPlayer[I].massivRang[9]++; break; };
			case 12: {printf("Queen of ");  pokerPlayer[I].massivRang[10]++; break; };
			case 13: {printf("King of ");  pokerPlayer[I].massivRang[11]++; break; };
			case 14: {printf("Ace of ");  pokerPlayer[I].massivRang[12]++; break; };
			}
			switch (pokerPlayer[I].card[i].maste) {
			case 'C': {puts("clubs");  pokerPlayer[I].massivMaste[0]++; break; };
			case 'H': {puts("hearts");   pokerPlayer[I].massivMaste[1]++; break; };
			case 'D': {puts("diamonds");  pokerPlayer[I].massivMaste[2]++; break; };
			case 'S': {puts("spades");   pokerPlayer[I].massivMaste[3]++; break; };
			}
		}
		puts("");
	}



	for (I = 0; I < maxI; I++) { // для нескольких игроков
		if (noCards[I] == 1) {
			continue;
		}
		//-----------------------------------------Для парных комбинаций----------------------------------------------------
		int wasPairCombination = 0;
		for (i = 0; i < 13; i++) {
			if (pokerPlayer[I].massivRang[i] >= 2) {
				wasPairCombination = 1;
				if (pokerPlayer[I].massivRang[i] == 4) {
					pokerPlayer[I].result_Combination[7] = 1;	// карэ и выход из цикла
					break;
				}
				else
					if (pokerPlayer[I].massivRang[i] == 3) {
						pokerPlayer[I].result_Combination[3] = 1;   //сет и возможность ухода на фулл хаус
					}
					else
						if (pokerPlayer[I].massivRang[i] == 2)
							pokerPlayer[I].result_Combination[1] = 1;  // пара и уход на две пары/фулл хаус

				for (int j = 0; j < 13; j++) {
					if (j == i) continue;
					if (pokerPlayer[I].massivRang[j] >= 2) {
						if (pokerPlayer[I].massivRang[j] == 2 && pokerPlayer[I].result_Combination[3] == 1) {
							pokerPlayer[I].result_Combination[6] = 1;     //фулл хаус
							break;
						}
						else
							if (pokerPlayer[I].massivRang[j] == 3 && pokerPlayer[I].result_Combination[1] == 1) {
								pokerPlayer[I].result_Combination[6] = 1;    // фулл хаус
								break;
							}
							else
								if (pokerPlayer[I].result_Combination[1] == 1)	pokerPlayer[I].result_Combination[2] = 1;   //две пары
								else
									pokerPlayer[I].result_Combination[1] = 1; //пара
					}
				}
				break;
			}
		}

		//-----------------------------------------Для флешей и стритов-----------------------------------------------------
		int wasFLASH_or_STREET = 0;
		if (!wasPairCombination) {
			for (i = 0; i < 4; i++) {
				if (pokerPlayer[I].massivMaste[i] == 5) {
					pokerPlayer[I].result_Combination[5] = 1;
					wasFLASH_or_STREET++;
					break;
				}
			}

			int count = 1;
			for (i = 0; i < 9; i++) {           // просматриваем 8 карты потому что после 8-мой карты (10-КИ) стрита не будет.
				if (pokerPlayer[I].massivRang[i] == 1) {
					while (pokerPlayer[I].massivRang[i + count] == 1) {
						count++;
						if (count == 5) {
							pokerPlayer[I].result_Combination[4] = 1;
							wasFLASH_or_STREET++;
						}
					}
					break;
				}
			}

			if (wasFLASH_or_STREET == 2)					//если был стрит и флеш
				if (pokerPlayer[I].massivRang[12] == 1)					//если есть ТУЗ
					pokerPlayer[I].result_Combination[9] = 1;			//то флешрояль
				else
					pokerPlayer[I].result_Combination[8] = 1;			 // стритфлеш
		}

		//--------------------------------------------Для старшей карты-------------------------------------------------------	
		if (!wasPairCombination && !wasFLASH_or_STREET) {
			pokerPlayer[I].result_Combination[0] = 1;             // старшая карта
		}

	}
	for (I = 0; I < maxI; I++) {
		for (i = 10; i > 0; i--) {
			if (pokerPlayer[I].result_Combination[i - 1] == 1) {
				puts("");
				print_Results(i);
				break;
			}
		}
	}
	return 0;
}