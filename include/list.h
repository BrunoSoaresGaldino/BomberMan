
#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdbool.h>


typedef struct Node
{
    void           *data;
    void           (*free_callback)( void *);// callback para libração dos dados
    struct Node    *next;
    struct Node    *previous;
    
} Node;

typedef struct
{
    Node    *first;
    Node    *last;
    Node    *current;
    size_t  len;
    
    
} List;


List *ListNew( );

void *ListDestroy( List *list, bool free_data);

void ListInsert( List *list , void *data , void *free_callback );

void ListRemoveByIndex( List *list, unsigned int index, bool free_data );

void *ListGetNext( List *list );

bool ListIsEmpty( List *list );

int ListLenght( List *list);

#endif