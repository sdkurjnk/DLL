#include <stdio.h>
#include <stdlib.h>

struct list
{
    struct list *after;
    struct list *before;
    int index;
};
typedef struct list base_node;

int init(void *ptr)
{
    base_node **head = (base_node **)ptr;
    if (*head == NULL) {
        *head = (base_node *)malloc(sizeof(base_node));
        if (*head == NULL) return 0;
    }

    (*head)->index = 0;
    (*head)->before = NULL;
    (*head)->after = NULL;

    return 1;
}

int indexing(void *ptr)
{
    base_node **head = (base_node **)ptr;
    if (*head == NULL) return 0;

    base_node *p = *head;
    while(p->before != NULL){
        p = p->before;
    }
    int index = 0;
    while(p != NULL){
        p->index = index++;
        p = p->after;
    }
    return 1;
}

int append(void *ptr, int i)
{
    base_node **head = (base_node **)ptr;
    if (i == 1){ // Forward
        base_node *newNode = (base_node *)malloc(sizeof(base_node));
        newNode->before = *head; newNode->after = NULL;

        if (*head != NULL){
            (*head)->after = newNode;
            newNode->index = (*head)->index + 1;
        } 
        else{
            newNode->index = 0;
        }

        *head = newNode;
        indexint(&head);
        return 1;
    }
    else if (i == -1){ // Backward
        base_node *newNode = (base_node *)malloc(sizeof(base_node));
        newNode->after = *head; newNode->before = NULL;

        if (*head != NULL){
            (*head)->before = newNode;
        }

        *head = newNode;
        indexing((base_node **)&head);
        return 1;
    }
    else{
        return 0;
    }
}

int move(void *ptr, int i)
{
    base_node **head = (base_node **)ptr;
    if (*head == NULL) return 0;

    base_node *p = *head;

    while(p->before != NULL){
        p = p->before;
    }

    while(p != NULL){
        if (p->index == i){
            *head = p;
            return 1;
        }
        p = p->after;
    }

    return 0;
}

int del(void *ptr) //Delete next node
{
    base_node **head = (base_node **)ptr;
    base_node *target = (*head)->after;
    if (target == NULL) return 0;

    base_node *A = (target)->after; base_node *B = (target)->before;

    if (A != NULL) A->before = B;
    if (B != NULL) B->after = A;

    free(target);
    indexing(head);

    return 1;
}
