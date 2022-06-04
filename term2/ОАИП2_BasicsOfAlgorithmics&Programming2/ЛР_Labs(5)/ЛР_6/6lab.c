#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>

//1. Реализовать кольцо целочисленных значений размером 10 элементов, функцию 
//добавления и вывода элементов. После каждого добавления выводить среднее 
//арифметическое 10 - ти последних значений : при добавлении 11 - го элемента, 
//этот элемент перетирает первый, 12 - й перетирает 2 - й и т.д. 

//2. Реализовать очередь символов от “a” до “d”, функции push_back, 
//pop_front.Завести три очереди(A, B и C).Максимальный размер очереди - 
//5 элементов.Все очереди изначально наполняются случайным образом.
//Завести изначально пустую очередь D.Каждую итерацию можно выбрать очередь 
//A, B или C. Из этой очереди достается первый с головы элемент и кладется в 
//очередь D.Если в очереди D находятся 3 одинаковых элемента подряд, то они удаляются.
//Каждую итерацию в одну из очередей A, B или C с учетом максимального размера очереди 
//случайным образом добавляется новый элемент.Выводить элементы всех очередей после каждой итерации.

typedef struct Node {
	int value;
	Node* left;
	Node* right;
}Node;

void add(Node** head, int value);
void add_clockwise(Node* head, int value, int position);
void print_clockwise(Node* head);
void find_average(Node* head);

int main() {
	int i, value = 0;
	puts("START.\n  Ring includes 10 elements ");
	Node* head = NULL;
	for (i = 0; i < 10; i++){
		printf("Value of %d-th's element: ", i + 1);
		rewind(stdin);
		scanf_s("%d", &value);
		add(&head, value);
	}
	print_clockwise(head);
	int j = 10;
	while (1){
		find_average(head);
		puts("\n0 - end, 1 - add");
		rewind(stdin);
		char a = getchar();
		if (a == '0')
			break;
		printf_s("Value of %d-th element:", i + 1);
		scanf_s("%d", &value);
		add_clockwise(head, value, i - j);
		//add(&head, value);
		print_clockwise(head);
		i++;
		if (i - j == 10)
			j += 10;
	}
	return 0;
}

void add(Node** head, int value) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->value = value;
	new_node->left = NULL;
	new_node->right = NULL;
	if (*head == NULL) {
		*head = new_node;
		new_node->left = new_node;
		new_node->right = new_node;
		return;
	}
	Node* current_tail = (*head)->right;
	(*head)->right = new_node;
	current_tail->left = new_node;
	new_node->left = *head;
	new_node->right = current_tail;
}

void print_clockwise(Node* head) {
	Node* node = head;
	do {
		printf(" %d ", node->value);
		node = node->left;
	} while (node != head);
}

void add_clockwise(Node* head, int value, int position) {
	int i;
	Node* current;
	current = head;
	for (i = 0; i < position; i++) {
		current = current->left;
	}
	current->value = value;
}

void find_average(Node* head) {
	float average = 0;
	Node* current;
	current = head;
	do {
		average += current->value;
		current = current->left;
	} while (current != head);
	average = average / 10;
	printf_s("\nAverage of 10 last integers = %f", average);
}