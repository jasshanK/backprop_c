#include <stdio.h>
#include <stdlib.h>

#define H 0.01f

enum operations {
    LABEL,
    ADD,
    MUL,
};

struct base {
    struct base* first_element;
    struct base* second_element;
    enum operations op;
    float value;
    float backprop;
};

struct metadata {
    float learning_rate;
    int element_count;
};

struct metadata metadata = { .learning_rate = H, .element_count = 0 };

struct base* create_base(float value);
struct base* add(struct base* first, struct base* second);
struct base* mul(struct base* first, struct base* second);
float compute(struct base* head);
void backprop(struct base* head);

int main() {
    struct base* a = create_base(3);
    struct base* b = create_base(4);
    struct base* c = add(a, b);

    struct base* d = create_base(4);
    struct base* e = mul(c, b);

    printf("a: %f\n", a->value);
    printf("b: %f\n", b->value);
    printf("c: %f\n", c->value);
    printf("d: %f\n", d->value);
    printf("e: %f\n", e->value);

    backprop(e);
    printf("\nbackprop\n");
    printf("a: %f\n", a->backprop);
    printf("b: %f\n", b->backprop);
    printf("c: %f\n", c->backprop);
    printf("d: %f\n", d->backprop);
    printf("e: %f\n", e->backprop);

    return 0;
}

struct base* create_base(float value) {
    struct base* new_base = malloc(sizeof(struct base));

    new_base->first_element = NULL;
    new_base->second_element = NULL;
    new_base->op = LABEL;
    new_base->value = value;
    new_base->backprop = 0;

    return new_base;
};

struct base* add(struct base* first, struct base* second) {
    struct base* result = create_base(0);

    result->first_element = first;
    result->second_element = second;
    result->op = ADD;
    result->value = first->value + second->value;

    return result;
};

struct base* mul(struct base* first, struct base* second) {
    struct base* result = create_base(0);

    result->first_element = first;
    result->second_element = second;
    result->op = MUL;
    result->value = first->value * second->value;

    return result;
};

float compute(struct base* head) {
    float result = 0;




    return result;
};

// 1. find every instance of an element, increment that instance 
// 2. compute graph 
// 3. calculate backprop
// does this mean I need to keep track of all the elements? 
// Yes, need to do one pass to find elements, or keep track of them as they are added 
// what is the best way to find every instance? 
void backprop(struct base* head) {
    int element_count = 0;


}
/* 
 * dL/dh = (f(a+h) - f(a)) / h
 */
// recursion time boiz
// this implemenation assumes an element is only used once in the chain 
//void backprop(struct base* head) {
//    if (head->op == LABEL) {
//        return;
//    }
//
//    float first_value = head->first_element->value;
//    float second_value = head->second_element->value;
//
//    float pre_increment = 0;
//    float post_increment = 0; 
//
//    pre_increment = compute(head);
//    
//    head->first_element->value += H;
//    post_increment = compute(head);
//    head->first_element->backprop += (post_increment - pre_increment) / H;
//
//    head->first_element->value = first_value;
//    backprop(head->first_element);
//    
//    head->second_element->value += H;
//    post_increment = compute(head);
//    head->second_element->backprop += (post_increment - pre_increment) / H;
//    
//    head->second_element->value = second_value;
//    backprop(head->second_element);
//}
//float compute(struct base* head) {
//    float result = 0;
//
//    switch(head->op) {
//        case ADD:
//            result = head->first_element->value + head->second_element->value;
//            break;
//        case MUL:
//            result = head->first_element->value * head->second_element->value;
//            break;
//        default:
//            break;
//    };
//
//    return result;
//};
