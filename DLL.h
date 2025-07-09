#include <stdio.h>
#include <stdlib.h>

struct list
{
    struct list *after;
    struct list *before;
    int index;
};
typedef struct list base_node;

int init(base_node **head)
{
    if ((*head) == NULL) return 0;
    (*head)->index = 0;
    (*head)->before = NULL;
    (*head)->after = NULL;
}

int indexing(base_node **head)
{
    if ((*head) == NULL) return 0;

    while((*head)->before != NULL){
        (*head) = (*head)->before;
    }
    int index = 0;
    while((*head) != NULL){
        (*head)->index = index++;
        (*head) = (*head)->after;
    }
    return 1;
}

int append(base_node **head, int i)
{
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

int move(base_node **head, int i)
{
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

int del(base_node **head) //Delete next node
{
    base_node *target = (*head)->after;
    if (target == NULL) return 0;

    base_node *A = (target)->after; base_node *B = (target)->before;

    if (A != NULL) A->before = B;
    if (B != NULL) B->after = A;

    free(target);
    indexing((base_node **)&head);

    return 1;
}
