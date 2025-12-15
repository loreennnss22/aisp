#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct node {
    int data;
    int priority;
    struct node* next;
} Node;


typedef struct {
    Node* top;
    int size;
    int max_size;
} CircularStack;


void startStack(CircularStack* stack, int max_size) {
    stack->top = NULL;
    stack->size = 0;
    stack->max_size = max_size;
}

int isStackEmpty(CircularStack* stack) {
    return stack->size == 0;
}

int isStackFull(CircularStack* stack) {
    return stack->size == stack->max_size;
}

void pushStack(CircularStack* stack, int data) {
    if (isStackFull(stack)) {
        printf("Stog je pun!\n");
        return;
    }


    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;

    if (isStackEmpty(stack)) {
        new_node->next = new_node;  
        stack->top = new_node;
    }
    else {
        new_node->next = stack->top->next;
        stack->top->next = new_node;
    }
    

    stack->top = new_node;
    stack->size++;
    printf("Element %d dodan na stog.\n", data);
}

int popStack(CircularStack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stog je prazan!\n");
        return -1;
    }
    Node* temp = stack->top;
    int popped_data = temp->data;


    if (stack->size == 1) {
        stack->top = NULL;
    }
    else {
        Node* current = stack->top;
        while (current->next != stack->top) {
            current = current->next;
        }
        current->next = stack->top->next;
        stack->top = stack->top->next;
    }

    free(temp);
    stack->size--;
    printf("Element %d uklonjen sa stoga.\n", popped_data);
    return popped_data;
}


Node* newNode(int d, int p) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = d;
    temp->priority = p;
    temp->next = NULL;
    return temp;
}


Node* push(Node* head, int d, int p) {
    Node* start = head;
    Node* temp = newNode(d, p);

    if (head == NULL || head->priority > p) {
        temp->next = head;
        head = temp;
    }
    else {
        while (start->next != NULL && start->next->priority <= p) {
            start = start->next;
        }
        temp->next = start->next;
        start->next = temp;
    }
    printf("Element %d prioriteta %d dodan u red.\n", d, p);
    return head;
}


Node* pop(Node* head) {
    if (head == NULL) {
        printf("Red je prazan!\n");
        return NULL;
    }
    Node* temp = head;
    head = head->next;
    printf("Element %d uklonjen iz reda.\n", temp->data);
    free(temp);
    return head;
}


int isEmpty(Node* head) {
    return head == NULL;
}


int main() {
    srand(time(NULL));  

    
    int max_size;
    printf("Unesite maksimalni broj elemenata stoga: ");
    scanf("%d", &max_size);
    CircularStack stack;
    startStack(&stack, max_size);
    
    printf("\nStog:\n");

    for (int i = 0; i < 3; i++) {
        int element = rand() % 91 + 10;  
        pushStack(&stack, element);
    }

    
    popStack(&stack);
    popStack(&stack);

    printf("\nRed:\n");

    Node* pq = NULL;

    
    for (int i = 0; i < 5; i++) {
        int element = rand() % 91 + 10;  
        int priority = rand() % 5 + 1;   
        pq = push(pq, element, priority);
    }

    
    while (!isEmpty(pq)) {
        pq = pop(pq);  
    }

    return 0;
}
