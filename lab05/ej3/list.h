#ifndef _LIST_H
#define _LIST_H

typedef int list_elem;

typedef struct s_node {
    list_elem elem;
    node *next
} *node;

typedef node *list;

#endif //_LIST_H