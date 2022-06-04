#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <locale.h>

//	1. Реализовать структуру, представляющую элемент пользовательского интерфейса на экране настроек
//приложения.Структура содержит перечисление, отображающее тип настройки(переключатель, текстовое поле, 
//выбор из множества, слайдер) и объединение, хранящее текущее значение настройки(0 / 1 для
//переключателя, строку для текстового поля и выбора, число с плавающей запятой - для слайдера).
//Сделать возможность задать с клавиатуры настройки, изменить значение любого пункта, вывести значения всех пунктов.

//	2. Для текстового поля добавить типы(логин, пароль, телефон) и валидацию введенного значения.Добавить ко всем
//элементам поля бит : в фокусе элемент или нет, видим или нет, активен или нет, прозрачность от 0 до 100.
//Добавить к элементам координату левого верхнего угла и размеры, положение по оси Z.Для введенной точки 
//клавиатуры для выбранного элемента определить, видна ли эта точка с учетом положения по оси Z, флага
//видимости и значения прозрачности.

const int textfield_size = 10;
const int bunch_size = 5;
const int size_element = 10;


struct Switcher {
	int value;
};

struct TextField {
	char* text;
};
struct ChoiceFromBunch {
	char** variety;
	short int current_element;
};
struct Slider {
	float value;
};
const enum Types {
	all = -1, Switch, Text, Bunch, Slider
};

struct Settings {
	Types type;
	union {
		struct Switcher switcher;
		struct TextField textField;
		struct ChoiceFromBunch bunch;
		struct Slider slider;
	};
}set[4];

enum Types choose_Type();
void first_initialization(Settings* point, int i);
void show_current(Settings* point, int i);
void changes(Settings* point, int type);



int main() {
	setlocale(LC_ALL, "Russian");
	puts("Начало программы.");
	Settings* Pointer[4];
	for (int j = 0; j < 4; j++) {
		Pointer[j] = &set[j];
		first_initialization(Pointer[j], j);
	}
	enum Types a;
	do {
		rewind(stdin);
		printf(" 1 - Вывод настройки по отдельности\n 2 - Вывод всех настроек\n 3 - Внести изменения\n 0 - Закончить программу");
		char q = getchar();
		system("CLS");
		if (q == '1') { 
			a = choose_Type();
			show_current(Pointer[a], a);
		}
		if (q == '3') {
			a = choose_Type();
			changes(Pointer[a], a);
		}
		if (q == '2') { 
			for (int a = 0; a < 4; a++) {
				show_current(Pointer[a], a);
			}
		}
		if (q == '0') break;
	} while (1);
	return 0;
}

void first_initialization(Settings* pointer, int i) {
	switch (i) {
	case Switch: {
		pointer->switcher.value = 0;
		break;
	}
	case Text: {
		pointer->textField.text = (char*)calloc(textfield_size, sizeof(char));
		puts("Текстовое поле - введите имя");
		fgets(pointer->textField.text, textfield_size, stdin);
		break;
	}
	case Bunch: {
		pointer->bunch.current_element = 0;
		pointer->bunch.variety = (char**)malloc(bunch_size * sizeof(char*));
		puts("Задайте элементы множества.");
		for (int j = 0; j < bunch_size; j++) {
			pointer->bunch.variety[j] = (char*)calloc(size_element, sizeof(char));
			fgets(pointer->bunch.variety[j], size_element, stdin);
		}
		break;
	}
	case Slider: {
		pointer->slider.value = 0.00;
		break;
	}
	}
}

enum Types choose_Type() {
	puts("Тип настройки:\n    1.Swicher\n    2.TextField\n    3.ChoosefromBunch\n    4.Slider\n ");
	rewind(stdin);
	char a = getchar();
	system("CLS");
	switch (a) {
	case '1':  return Switch;
	case '2':  return Text;
	case '3':  return Bunch;
	case '4':  return Slider;
	};
}

void show_current(struct Settings* pointer, int type) {
	int i;
	switch (type) {
	case Switch: {
		puts("Переключатель");
		if (pointer->switcher.value == 1)
			printf("On\n");
		else printf("Off\n");
		break;
	};
	case Text: {
		printf("Текстовое поле\n ");
		printf("%s", pointer->textField.text);
		break;
	};
	case Bunch: {
		puts("Выбор из множества");
		for (i = 0; i < bunch_size; i++) {
			printf("%d - th ", i + 1);
			printf("%s", pointer->bunch.variety[i]);
			if (i == pointer->bunch.current_element)
				printf("       ^ This element is chosen\n");
		}
		break;
	};
	case Slider: {
		printf("Слайдер - %f\n", pointer->slider.value);
		break;
	};
	}
}

void changes(struct Settings* pointer, int type) {
	puts("Изменение...");
	int i;
	switch (type) {
	case Switch: {
		show_current(pointer, Switch);
		do {
			puts("Input(1/0) ");
			rewind(stdin);
			scanf_s("%d", &pointer->switcher.value);
		} while (pointer->switcher.value != 1 && pointer->switcher.value != 0);
		break;
	}
	case Text: {
		show_current(pointer, Text);
		printf("Input  ");
		rewind(stdin);
		fgets(pointer->textField.text, textfield_size, stdin);
		break;
	}
	case Bunch: {
		show_current(pointer, Bunch);
		puts(" 0 - перезаписать элементы мн-ва\n 1 - выбрать эл-нт из сущ-их");
		int a, v;
		scanf_s("%d", &a);
		switch (a) {
		case 0:
			puts("Input (max - 9) ");
			for (i = 0; i < bunch_size; i++) {
				printf("%d - ", i + 1);
				rewind(stdin);
				fgets(pointer->bunch.variety[i], size_element, stdin);
			}
		case 1: {
			puts("Input_Choose_Element(1 - 5) ");
			do {
				rewind(stdin);
				scanf_s("%d", &v);
			} while (v <= 0 && v > 5);
			pointer->bunch.current_element = v - 1;
		}
		}
		break;
	}
	case Slider: {
		show_current(pointer, Slider);
		puts("Input(from 0 to 1) ");
		scanf_s("%f", &pointer->slider.value);
		while (pointer->slider.value > 1 || pointer->slider.value < 0) {
			rewind(stdin);
			scanf_s("%f", &pointer->slider.value);
		}
		break;
	}
	}
	system("CLS");
}