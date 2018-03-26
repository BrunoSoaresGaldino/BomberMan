
#include "../include/list.h"

List *ListNew( )
{
    
    return calloc( 1 , sizeof(List) );
    
}

void *ListDestroy( List *list, bool free_data )
{
    
    Node    *node = list->first;
    Node    *aux;
    
    while( node )
    {
        
        aux = node;
        node = node->next;
        
        if( free_data )
        {
            aux->free_callback( aux->data );
        }
        
        free( aux );
    }
    
    free( list );
    
}

void ListInsert( List *list , void *data , void *free_callback )
{
    
    Node *node = calloc( 1, sizeof(Node) );// alloca memoria e incializa com zeros
    
    
    if( node )
    {
    
        node->data = data;
        node->free_callback = free_callback;
        

        if( list->first  == NULL )// lista vazia
        {
            list->current = list->first = list->last = node;
        }
        
        else// insere sempre ao final
        {
            node->previous = list->last;
            list->last = list->last->next = node;
        }
        
        list->len++;
        
    }
    
}

void ListRemoveByIndex( List *list, unsigned int index, bool free_data )
{
    
    Node    *node;
    int     i = 1;
 
    node = list->first;
    
    if( node && index < list->len )
    {
        
        if( index )// index diferente de zero
        {
        
            while( node )//o laço passa de nó em nó
            {   
            
                if( i == index )
                {   
                    if( node == list->last )
                    {
                        list->last = node->previous;
                    }
            
                    node->previous->next = node->next;
                    break;
                    
                }

                node = node->next;
                i++;
            }
    
        }
        else// indice zero
        {
            list->first = node->next;
        }

        if( node->next )
        {
            node->next->previous = node->previous;
        }
        
        if( list->current == node )
        {
            list->current = node->next;
        }
        
        if( free_data )
        {
            node->free_callback( node->data );
        }

        
        free( node );
        list->len--;
        
    }
    
}

void *ListGetNext( List *list )
{   
    
    void *data;
    
    
    if( list->current == NULL )
    {
        data = NULL;
        list->current = list->first;
    }
    
    else
    {
        data = list->current->data;
        list->current = list->current->next;
    }
    
    
    return data;
    
}

bool ListIsEmpty( List *list )
{
    return list->len == 0;
}

int ListLenght( List *list)
{
    
    return list->len;
    
}