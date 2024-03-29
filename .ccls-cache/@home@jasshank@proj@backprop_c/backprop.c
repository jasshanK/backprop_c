#include "backprop.h"

extern struct metadata metadata; 

struct element* create_element(float value) {
    struct element* new_element = malloc(sizeof(struct element));

    new_element->op_elements[0] = 0;
    new_element->op_elements[1] = 0;
    new_element->op = NIL;
    new_element->value = value;
    new_element->grad = 0;

    return new_element;
};

struct element* add(struct element* first, struct element* second) {
    struct element* result = create_element(0);

    metadata.op_chain[metadata.op_count] = result; metadata.op_count += 1;

    result->op_elements[0] = first;
    result->op_elements[1] = second;
    result->op = ADD;
    result->grad = 0;

    result->value = first->value + second->value;

    return result;
};

struct element* mul(struct element* first, struct element* second) {
    struct element* result = create_element(0);

    metadata.op_chain[metadata.op_count] = result;
    metadata.op_count += 1;

    result->op_elements[0] = first;
    result->op_elements[1] = second;
    result->op = MUL;
    result->grad = 0;

    result->value = first->value * second->value;

    return result;
};

float compute_element(struct element* element) {
    float result = 0;
    float first = element->op_elements[0]->value;
    float second = element->op_elements[1]->value;

    switch(element->op) {
        case ADD:
            result = first + second;
            break;
        case MUL:
            result = first * second;
            break;
        default:
            break;
    }

    return result;
};

void compute_chain(struct element* head, struct element* target) {
    if (head->op == NIL) {
        return;
    }
    
    compute_chain(head->op_elements[0], target);
    compute_chain(head->op_elements[1], target);
    
    if (head != target) {
        head->value = compute_element(head);
    }

    return;
}

/* 
 * dL/dx = (f(a+x) - f(a)) / x
 */
void grad(struct element* head) {
    const int op_count = metadata.op_count;
    const float dx = metadata.dx;
    const float pre_increment = head->value;
    
    float pre_grad = 0;
    for (int i = 0; i < op_count; i++) {
        struct element* current = metadata.op_chain[i];
        
        for (int j = 0; j < 2; j++) {
            pre_grad = current->op_elements[j]->value;

            current->op_elements[j]->value += dx;
            compute_chain(head, current->op_elements[j]);
            current->op_elements[j]->grad = (head->value - pre_increment) / dx;

            current->op_elements[j]->value = pre_grad;
            compute_chain(head, current->op_elements[j]);
        }
    }
}
