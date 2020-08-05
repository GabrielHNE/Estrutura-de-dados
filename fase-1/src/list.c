#include "./list.h"

List * initList(){
    List * list = (List *) malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;

    return list;
}

//it's used only for "private" functions
static Node * newNode(void * data){
    Node * new_node = (Node *) malloc(sizeof(Node));

    new_node->data = data;
    
    //those are set later
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void pushBack(List * list, void * data){

    if(list->head == NULL){
        list->head = newNode(data);

        list->tail = list->head;

        list->length = 1; //this is where we start the counter list length;
    }else {
        Node * new_node = newNode(data);

        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
        
        list->length ++;
    }
}

void pushFront(List * list, void * data){

    if(list->head == NULL){
        list->head = newNode(data);

        list->tail = list->head;

        list->length = 1; //this is where we start the counter list length;
    }else {
        Node * new_node = newNode(data);
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
        
        list->length ++;
    }
}

void printList(Node *node, void (*fptr)(void *)) { 
    while (node){ 
        (*fptr)(node->data); 
        node = node->next; 
    } 
} 

void printInt(void * d){
    printf("%d\n", *(int *)d);
}

void printfFloat(void * f){
    printf("%f\n", *(float *)f);
}

void printChar(void * c){
    printf("%c\n", *(char *)c);
}

void deleteNode(Node * node, void (*callback)(void *)){
    Node * aux;
    
    aux = node->prev;
    aux->next = node->next;

    //limpa a data do node. Pode ser NULL se nao for alocada na stack
    if((*callback)){
        (*callback)(node->data);
    }

    free(node);
}

void freeList(List * list){

    //only free the nodes;
    if(list){
        Node * node = list->head;
        while(node){
            Node * tmp = node;
            node = node->next;
            tmp->next = NULL;
            tmp->prev = NULL;
            free(tmp);
        }
    }

    free(list);
}

//