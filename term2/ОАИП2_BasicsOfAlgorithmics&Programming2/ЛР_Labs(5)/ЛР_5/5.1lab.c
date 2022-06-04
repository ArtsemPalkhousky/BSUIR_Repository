#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>


//1. Реализовать односвязный список целочисленных значений с функцией добавления элемента в конец.
//По запросу с клавиатуры удалить из списка все элементы с повторяющимися значениями. 


typedef struct Node{ 
	int value;
	struct Node* next; 
}Node; 

//void clearList(Node* head){
//	Node* tmp; 
//	while (head != NULL) {
//		tmp = head;
//		head = head->next;
//		free(tmp);
//	}
//}

void push(Node** head, int value) {				//запись в начало списка
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->value = value;
	tmp->next = (*head);
	(*head) = tmp;
};

Node* getLast(Node* head){						//получение последнего элемента
	if (head == NULL) {
		return NULL;
	}
	while (head->next) {
		head = head->next;
	}
	return head;
}

Node* getPreLast(Node* head) {					//получение предпоследнего элемента
	if (head == NULL)
		exit(-2);
	if (head->next == NULL)
		return NULL;
	while (head->next->next)
		head = head->next;
	return head;
}

void pushBack(Node* head, int value) {			//запись элемента в конец
	Node* last = getLast(head);
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->value = value;
	tmp->next = NULL;
	last->next = tmp;
}

int pop(Node** head) {							//удаление головы
	Node* prev = NULL;
	int value;
	if (head == NULL)
		exit(-1);
	prev = (*head);
	value = prev->value;
	(*head) = (*head)->next;
	free(prev);
	return value;
}

void delete_same(Node* head){					//удаление повторяющихся элементов из списка
	Node* point_Fst, * point_Sec, * prev, * tmp;
	for (point_Fst = head; point_Fst != NULL; point_Fst = point_Fst->next) {
		prev = point_Fst;
		for (point_Sec = point_Fst->next; point_Sec != NULL;) {
			if (point_Sec->value == point_Fst->value) {
				tmp = prev->next = point_Sec->next;
				free(point_Sec);
				point_Sec = tmp;
				continue;
			}
			prev = point_Sec;
			point_Sec = point_Sec->next;
		}
	}
}

void printList(const Node* head) {				//вывод списка (с головы до ног)	
	while (head) {
		rewind(stdin);
		printf("%d", head->value);
		head = head->next;
		puts("");
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	Node* head = NULL;
	int data;
	char a;
	puts("Начало программы.\nВвод головы списка ");
	scanf_s("%d", &data);
	push(&head, data);
	while (1) {
		puts("\n1 - Add to the head, 2- Print, 3 - Add to the end, 4 - Delete same elements, 5 - Exit\n");
		rewind(stdin);
		switch (a = getchar()) {
		case '1': {
			puts("Ввод иинформации в голову списка");
			rewind(stdin);
			while (!scanf_s("%d", &data)) { puts("Повторите ввод"); rewind(stdin); };
			push(&head, data);
			break;
		};
		case'2': {
			puts("List:");
			printList(head);
			break;
		}
		case'3': {
			puts("Ввод информации в конец списка");
			rewind(stdin);
			while (!scanf_s("%d", &data)) { puts("Повторите ввод"); rewind(stdin); };
			pushBack(head, data);
			break;
		}
		case'4': {
			puts("Удаление из списка всех повторяющихся значений");
			delete_same(head);
			printList(head);
			break;
		};
		//case'5': {
		//	puts("Список пуст");
		//	clearList(head);
		//	break;
		//};
		case'5': return 0;
		}
	}
}