#pragma once

typedef struct Node {
	uint32_t value;
	struct Node* next;
	struct Node* prev;
		
}Node;

typedef struct List {
	Node* first;
	Node* last;
	int n;
} List;
List *create_List();
int count(List *l);
void append(List* l, int value);
void printList(List* l);
Node *create_Node(int value);
void destroyList(List*l);