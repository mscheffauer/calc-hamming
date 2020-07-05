#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"


List *create_List(){
	//allocate list
	List *l = (List*) malloc(sizeof(List));	
	if (l == NULL){
		return NULL;
	}
	l->first = NULL;
	l->last = NULL;
	l->n = 0;
	
	return l;
}

void printList(List* l){
	Node* temp = NULL;
	
	
	printf("%d\n",l->first->value);
	temp = l->first->next;
	
	for (int i=0; i<(l->n-1);i++ ){
		
		printf("%d\n",temp->value);
		temp = temp->next;
    }
	
}

void destroyList(List*l){

	Node* nodetoFree;
	if (l->first != NULL){
		nodetoFree = l->first;
	}
	//free nodes in list
	if (nodetoFree->next == NULL){
		free(nodetoFree);
	}
	while (nodetoFree->next != NULL){	
		nodetoFree = nodetoFree->next;
		
		free(nodetoFree->prev);
	}
	
	//free list
	if (l!= NULL)
	{
		free(l);
	}

	
}


Node *create_Node (int value){	
	Node *n =(Node*) malloc(sizeof(Node));
	
	if (n == NULL){
		return NULL;
	}
	//alle werte initialisieren
	n->value = value;
	n->next = NULL;
	n->prev = NULL;
	
	return n;
}
void append(List* l, int value){
	Node* new_Node = create_Node(value);
	
	if (new_Node == NULL){
		printf("memory exhausted\n");
	}else{
		if (l->last != NULL){
			l->last->next = new_Node;
		}
		
		new_Node->prev = l->last;	//next of new node is current first of list
		
			//new last of list is new node
		l->last = new_Node;
		if (l->n==0){
			l->first = new_Node;
		}
		
		l->n++;
	}
	
	
}