#include <stdio.h>

#include "backprop.h"

struct metadata metadata = { .dx = DX,  .op_count = 0, .op_chain = {0} };

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
    
    grad(f);
    printf("\nbackprop\n");
    printf("a: %f\n", a->grad);
    printf("b: %f\n", b->grad);
    printf("c: %f\n", c->grad);
    printf("d: %f\n", d->grad);
    printf("e: %f\n", e->grad);
    printf("f: %f\n", f->grad);

    return 0;
}

