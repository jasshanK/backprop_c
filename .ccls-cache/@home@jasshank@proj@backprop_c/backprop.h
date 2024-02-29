#include <stdlib.h>

#define H 0.01f

enum operations {
    NIL,
    ADD,
    MUL,
};

struct element {
    struct element* op_elements[2];
    enum operations op;
    float value;
    float backprop;
};

struct metadata {
    float learning_rate;
    int op_count;
    struct element* op_chain[10];
};

struct element* create_element(float value);
struct element* add(struct element* first, struct element* second);
struct element* mul(struct element* first, struct element* second);
float compute_element(struct element* element);
void compute_chain(struct element* head, struct element* target);
void backprop(struct element* head);
