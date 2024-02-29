#include <stdio.h>

#include "backprop.h"

struct metadata metadata = { .learning_rate = H, .op_count = 0, .op_chain = {0} };

int main() {
    struct element* a = create_element(3);
    struct element* b = create_element(4);
    struct element* c = add(a, b);

    struct element* d = create_element(4);
    struct element* e = mul(c, b);
    struct element* f = mul(e, d);

    printf("a: %f\n", a->value);
    printf("b: %f\n", b->value);
    printf("c: %f\n", c->value);
    printf("d: %f\n", d->value);
    printf("e: %f\n", e->value);
    printf("f: %f\n", f->value);
    
    backprop(f);
    printf("\nbackprop\n");
    printf("a: %f\n", a->backprop);
    printf("b: %f\n", b->backprop);
    printf("c: %f\n", c->backprop);
    printf("d: %f\n", d->backprop);
    printf("e: %f\n", e->backprop);
    printf("f: %f\n", f->backprop);

    return 0;
}

