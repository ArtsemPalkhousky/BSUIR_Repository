#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

unsigned long msTimer = 0;

int hour;
int min;
int sec;

int setHour;
int setMin;
int setSec;

int value;
int input;

void interrupt(*oldPeriodicInt)(...);   // Указатель на старый обработчик прерывания
void interrupt newPeriodicInt(...);

int intToBCD(int);
int BCDToInt(int);
void showTime();
void setTime();
void setDelay();

void main()
{
clrscr();

while (input != 27)
{
printf("\nInput:\n[1] Get time\n[2] Set time\n[3] Delay\n[Esc] Exit\n\n");
input = getch();

switch (input)
{
case '1':
{
showTime();
break;
}

case '2':
{
setTime();
break;
}

case '3':
{
setDelay();
break;
}

case 27:
break;
}
}
}

void interrupt newPeriodicInt(...)
{
msTimer++;  // Счётчик миллисекунд

outp(0x70, 0x0C); // Если регистр C не будет прочитан после IRQ 8,
inp(0x71);        // тогда прерывание не случится снова

outp(0x20, 0x20); // Посылаем контроллеру прерываний (master) сигнал EOI
outp(0xA0, 0x20); // Посылаем второму контроллеру прерываний (slave) сигнал EOI

}

int BCDToInt(int number)		//перевод числа в bcd code
{
number = number;
return (((number / 0x10) * 10) + (number % 0x10));
}

int intToBCD(int number)		//перевод из bcd в десятичное
{
number = number;
return (((number / 10) * 0x10) + (number % 10));
}

void showTime()
{
do   // Ожидание, пока часы заняты
{
outp(0x70, 0x0A);
} while (inp(0x71) & 0x80); // 0x80 = 10000000, пока 7-й бит - 1, часы заняты

outp(0x70, 4); //Текущий час
hour = inp(0x71);
printf("%d:", BCDToInt(hour));
do   // Ожидание, пока часы заняты
{
outp(0x70, 0x0A);
} while (inp(0x71) & 0x80); // 0x80 = 10000000, пока 7-й бит - 1, часы заняты

outp(0x70, 2); //Текущая минута
min = inp(0x71);
printf("%d:", BCDToInt(min));
do   // Ожидание, пока часы заняты
{
outp(0x70, 0x0A);
} while (inp(0x71) & 0x80); // 0x80 = 10000000, пока 7-й бит - 1, часы заняты

outp(0x70, 0); //Текущая секунда
sec = inp(0x71);
printf("%d\n", BCDToInt(sec));
}

void setTime()
{
do   // Ожидание, пока часы заняты
{
outp(0x70, 0x0A);
} while (inp(0x71) & 0x80); // 0x80 = 10000000, пока 7-й бит - 1, часы заняты

outp(0x70, 0x0B);
value = inp(0x71) | 0x80; // читаем регистр состояния B, заменяем 7-й бит на 1 для запрещения обновления часов
outp(0x70, 0x0B);
outp(0x71, value); // Записываем новое значение в регистр B, обновление часов запрещено

printf("Enter time\n");
printf("Hours:");
scanf("%d", &setHour);
printf("Minutes:");
scanf("%d", &setMin);
printf("Seconds:");
scanf("%d", &setSec);

outp(0x70, 0x04);
outp(0x71, intToBCD(setHour));
outp(0x70, 0x02);
outp(0x71, intToBCD(setMin));
outp(0x70, 0x00);
outp(0x71, intToBCD(setSec));


do   // Ожидание, пока часы заняты
{
outp(0x70, 0x0A);
} while (inp(0x71) & 0x80); // 0x80 = 10000000, пока 7-й бит - 1, часы заняты

outp(0x70, 0x0B);
value = inp(0x71) & 0x7F; // читаем регистр состояния B, заменяем 7-й бит на 0 для разрешения обновления часов
outp(0x71, value); // Записываем новое значение в регистр B, обновление часов разрешено
}

void setDelay()
{
unsigned long delayMS = 0;


disable();  // Запретить прерывания
oldPeriodicInt = getvect(0x70);
setvect(0x70, newPeriodicInt);
enable();   // Разрешить прерывания

printf("Enter delay in ms: ");
scanf("%ld", &delayMS);

printf("Start time:");
showTime();

// Размаскирование линии сигнала запроса от RTC
value = inp(0xA1);
outp(0xA1, value & 0xFE);        // 0xFE = 11111110, бит 0 в 0, чтобы разрешить прерывания от RTC
 
//включение периодического прерывания
outp(0x70, 0x0B);                // Выбираем регистр B
value = inp(0x71);               // Читаем содержимое регистра B
outp(0x70, 0x0B);                // Выбираем регистр B
outp(0x71, value | 0x40);        // 0x40 = 01000000, 6-й бит регистра B устанавливаем в 1

msTimer = 0;
while (msTimer != delayMS) {};   // Задержка
printf("%ldms passed\n", delayMS);
setvect(0x70, oldPeriodicInt);   // Восстанавливаем старый обработчик

outp(0x70, 0x0B);
value = inp(0x71) & 0x7F; // читаем регистр состояния B, заменяем 7-й бит на 0 для разрешения обновления часов
outp(0x71, value); // Записываем новое значение в регистр B, обновление часов разрешено

printf("End time:");
showTime();
}
