#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node_t
{
    int data;
    struct node_t* next;
    struct node_t* prev;
} node_t;

typedef struct
{
    node_t* head;
    node_t* tail;
    size_t size;
} abstract_data_t;

node_t* create_node_t(int data)
{
    node_t* node = (node_t*)malloc(sizeof(node_t));
    if (node == NULL){
        printf("EROR");
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void push_f(abstract_data_t* deque, int data)
{
    node_t* node = create_node_t(data);
    if (deque->size == 0)
    {
        deque->head = node;
        deque->tail = node;
    }
    else
    {
        deque->tail->next = node;
        deque->tail->next->prev = deque->tail;
        deque->tail = node;
    }
    deque->size++;
    return;
}

void print(const abstract_data_t* deque)
{
    if (deque->size > 0)
    {
        node_t* current = deque->head;
        while (current != NULL){
            printf("%d ", current->data);
            current = current->next;
        }
    printf("\n");
    }
    printf("size: %d ", deque->size);
    if (deque->head == NULL && deque->tail == NULL)
    {
        printf("head: NULL ");
        printf("tail: NULL ");
    }else
    {
        printf("head: %d ", deque->tail->data);
        printf("tail: %d ", deque->tail->data);
    }
    printf("\n\n");
}

// // рекомендуемые прототипы функций:
abstract_data_t* make_copy(const abstract_data_t *deque)
{
    abstract_data_t* deque_copy = (abstract_data_t*)malloc(sizeof(abstract_data_t));
    if (deque_copy == NULL){
        printf("EROR");
    }
    deque_copy->head = NULL;
    deque_copy->tail = NULL;
    deque_copy->size = 0;
    node_t* current = deque->head;
    while (current != NULL){
        push_f(deque_copy, current->data);
        current = current->next;
    }
    
    return deque_copy;
}

abstract_data_t* make_from_array(const int arr[], size_t size)
{
    abstract_data_t* deque = (abstract_data_t*)malloc(sizeof(abstract_data_t));
    if (deque == NULL){
        printf("EROR");
    }
    deque->head = NULL;
    deque->tail = NULL;
    deque->size = 0;
    
    for (int i = 0; i < size; i++)
    {
        push_f(deque, arr[i]);
    }
    
    return deque;
}

abstract_data_t* make_of_size(size_t size)
{
    abstract_data_t* deque = (abstract_data_t*)malloc(sizeof(abstract_data_t));
    if (deque == NULL){
        printf("EROR");
    }
    for (int i = 0; i < size; i++)
    {
        push_f(deque, 0);
    }
    
    return deque;
}

abstract_data_t* make_empty()
{
    abstract_data_t* deque = (abstract_data_t*)malloc(sizeof(abstract_data_t));
    if (deque == NULL){
        printf("EROR");
    }
    deque->head = NULL;
    deque->tail = NULL;
    deque->size = 0;
    
    return deque;
}

void clear(abstract_data_t *deque)
{
    node_t* current = deque->head;
    while (current != NULL){
        node_t* next = current->next;
        free(current);
        current = next;
        }
    deque->size = 0;
    deque->head = NULL;
    deque->tail = NULL;
}


int at(const abstract_data_t *deque, int step)
{
    node_t* current;
    if (step >= 0)
    {
        current = deque->head;
        for(int i = 0; i < step && current->next != NULL; i++)
        {
            current = current->next;
        }
    }else
    {
        current = deque->tail;
        for(int i = 1; i < -step && current->prev != NULL; i++)
        {
           current = current->prev;
        }
    }
    
    return current->data;
}

bool is_equal(const abstract_data_t *deque_1, const abstract_data_t *deque_2)
{
    node_t* current1;
    node_t* current2;
    if(deque_1->size > deque_2->size)
    {
        current1 = deque_2->head;
        current2 = deque_1->head;
    }else
    {
        current1 = deque_1->head;
        current2 = deque_2->head;
    }
    while (current1 != NULL){
        if(current1->data != current2->data)
        {
            return false;
        }
        current1 = current1->next;
        current2 = current2->next;
    }
    return true;
}

int main(int argc, char const *argv[])
{
    // код для проверки правильности выполнения задания:
    int array[] = {1, 4, 7, 9};

    abstract_data_t* a = make_from_array(array, 4);

    assert(9 == at(a, 3));
    assert(9 == at(a, -1));
    assert(9 == at(a, 13));
    assert(1 == at(a, -13));

    abstract_data_t* b = make_copy(a);

    assert(is_equal(a, b));

    clear(a);
    clear(b);
    
    //ТЕСТЫ:
    // abstract_data_t* deque_1 = make_of_size(5);
    // print(deque_1);
    
    // abstract_data_t* deque_2 = make_copy(deque_1);
    // print(deque_2);
    
    // int array[] = {1, 4, 7, 9};
    // abstract_data_t* deque_3 = make_from_array(array, 4);
    // print(deque_3);
    
    // abstract_data_t* deque_4 = make_empty();
    // print(deque_4);
    
    // if(is_equal(deque_1, deque_2) == true)
    // {
    //     printf("Правда \n\n");
    // }else
    // {
    //     printf("Неправда \n\n");
    // }
    // clear(deque_1);
    // print(deque_1);
    // print(deque_2);
    
    // printf("at: %d \n\n", at(deque_3, 1));
    
    
}
