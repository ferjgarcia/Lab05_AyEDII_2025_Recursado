#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"

typedef struct s_node {
    list_elem elem;
    struct s_node *next;
} node;

list empty() {
    list l = NULL;

    return l;
}

list addl (list_elem e, list l) {
    node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));

    if (new_node == NULL) {
        fprintf(stderr, "Error: Al asignar memoria para new_node 'addl'\n");
        exit(EXIT_FAILURE);
    }
    

    new_node->elem = e;
    new_node->next = l;

    l = new_node;

    return l;
}

bool is_empty(list l) {
    return l == NULL;
}

list_elem head(list l) {
    assert(l != NULL);
    list_elem e = l->elem;
    return e;
}

list tail(list l) {
    assert(l != NULL);
    node *new_node = NULL;
    new_node = l;

    l = l->next;

    free(new_node);

    return l;
}

list addr (list l, list_elem e) {
    node *new_node= NULL;
    new_node = malloc(sizeof(struct s_node));

    if (new_node == NULL) {
        fprintf(stderr, "Error: Al asignar memoria para new_node 'addr'\n");
        exit(EXIT_FAILURE);
    }

    new_node->elem = e;
    new_node->next = NULL;

    if(is_empty(l)) {
        l = new_node;
    } else {
        node *temp = l;
        while (temp->next != NULL) {
            temp = temp->next;
        }
    
        temp->next = new_node;
    }

    return l;
}

unsigned int length(list l) {
    unsigned int i = 0;
    node *new_node = NULL;
    new_node = l;

    while (new_node != NULL) {
        new_node = new_node->next;
        i++;
    }
    
    return i;
}
// debiera hacer un copy list de l1 para no modificarlo?? esta bien hacer el copy?
// a copy1 no debiera primero asignarle null??
list concat_list(list l1, list l2) {
    list copy1 = copy_list(l1);
    list copy2 = copy_list(l2);

    if (l1 == NULL) {
        return copy2;
    } else if (l2 == NULL) {
        return copy1;
    } else {
        node *iter = copy1;

        while (iter->next != NULL) {
            iter = iter->next;
        }
        
        iter->next = copy2;

        return copy1;
    }       
}

list_elem index(list l, unsigned int n) {
    assert(n <= length(l)-1);
    node *new_node = NULL;
    new_node = l;
    n = n-1;

    while (n > 0) {
        new_node = new_node->next;
        n--;
    }
    
    return new_node->elem;
}

list take(list l, unsigned int n) {
    if (n == 0) {
        return NULL;
    } else if(n == length(l)) {
        return l;
    }
    
    list new_l = copy_list(l);
    node *iter = new_l;
    n--;

    while (n > 0) {
        iter = iter->next;
        n--;
    }

    node *kill = iter->next;
    iter->next = NULL;

    while (kill != NULL) {
        node *temp = kill->next;
        free(kill);
        kill = temp;
    }

    return new_l;   
}

list drop(list l, unsigned int n) {
    if (n == 0) {
        return l;
    } else if(n == length(l)) {
        return NULL;
    }
    
    list new_l = copy_list(l);
    node *kill = new_l;

    while (n > 0) {
        node *temp = kill->next;
        free(kill);
        kill = temp;
        n--;
    }

    return kill; 
}

list copy_list(list l) {
    if (l == NULL) {
        return NULL;
    }

    // Creamos el primer nodo de la nueva lista
    list new_list = malloc(sizeof(node));

    if (new_list == NULL) {
        fprintf(stderr, "Error: Al asignar memoria para new_node 'copy_list'\n");
        exit(EXIT_FAILURE);
    }


    new_list->elem = l->elem;
    new_list->next = NULL;

    node *src = l->next;        // apuntador a la lista original
    node *dest = new_list;      // apuntador a la copia actual

    while (src != NULL) {
        dest->next = malloc(sizeof(node));

        if (dest->next == NULL) {
            fprintf(stderr, "Error: Al asignar memoria para dest_next 'copy_list'\n");
            exit(EXIT_FAILURE);
        }

        dest = dest->next;
        dest->elem = src->elem;
        dest->next = NULL;
        src = src->next;
    }

    return new_list;
}

void destroy (list l) {
    if (l != NULL) {
        node *new_node, *temp = NULL;
        new_node = l;

        while (new_node != NULL) {
            temp = new_node->next;
            free(new_node);
            new_node = temp;
        }

        l = NULL;
    }
}

void print_list(list l) {
    node *current = l;
    while (current != NULL) {
        printf("%d ", current->elem);
        current = current->next;
    }
    printf("\n");
}
