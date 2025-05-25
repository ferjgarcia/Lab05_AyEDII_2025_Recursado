#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "counter.h"

struct _counter {
    unsigned int count;
};

counter counter_init(void) {
    counter c = NULL;
    c = malloc(sizeof(struct _counter));

    if (c == NULL) {
        fprintf(stderr, "Error al asignar memoria para c");
    }

    c->count = 0;

    return c;
}

void counter_inc(counter c) {
    c->count++;
}

bool counter_is_init(counter c) {
    assert(c != NULL);
    return c->count == 0;
}

void counter_dec(counter c) {
    assert(!counter_is_init(c));
    c->count--;
}

counter counter_copy(counter c) {
    counter new_c = NULL;
    new_c = counter_init();
    new_c->count = c->count;

    return new_c;
}

void counter_destroy(counter c) {
    free(c);
    c = NULL;
}
