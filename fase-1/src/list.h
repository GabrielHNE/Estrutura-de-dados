#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>

// created headers
#include "./utils.h"

typedef struct Node {
    void * data;

    //
    struct Node *next;
    struct Node *prev; 
} Node;

typedef struct List {
    struct Node * head;
    struct Node * tail;

    size_t length;
} List;

/* inicia uma lista generica */
List * initList();

/*
    Coloca data no final da lista list
*/
void pushBack(List * list, void * data);

/*
    Coloca data no inicio da lista list
*/
void pushFront(List * list, void * data);

/*
    Printa os dados encontrados em node. Deve-se passar como argumento uma função que realize os print dos 
    dados que estao guardados no nó da lista.
*/
void printList(Node *node, void (*fptr)(void *));
void printInt(void * d);
void printFloat(void * f);
void printChar(void * c);

/*
    Deleta um nó na lista. (*callnack) e um ponteiro para a funcao utilizada para limpar os dados genericos da lista
*/
void deleteNode(Node * node, void (*callback)(void *));

/*
    Destroi a lista, liberando todos os espaço alocados. Deve-se chamar deleteNode com o callback para
    os dados genericos alocados antes.
*/
void freeList(List * list);


#endif //LIST_H