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
        srand((unsigned)time(NULL));

        CircularStack stack;
        int max_size;
        int choice;
        int value, priority;

        printf("Unesite maksimalni broj elemenata stoga: ");
        scanf_s("%d", &max_size);

        startStack(&stack, max_size);

        Node* pq = NULL;

        do {
            printf("\n IZBORNIK \n");
            printf("1 - Push na stog\n");
            printf("2 - Pop sa stoga\n");
            printf("3 - Push u red s prioritetom\n");
            printf("4 - Pop iz reda\n");
            printf("0 - Izlaz\n");
            printf("Odabir: ");
            scanf("%d", &choice);

            switch (choice) {

            case 1:
                printf("Unesite vrijednost: ");
                scanf("%d", &value);

                if (isStackFull(&stack)) {
                    printf("Stog je pun!\n");
                }
                else {
                    pushStack(&stack, value);
                }
                break;

            case 2:
                value = popStack(&stack);
                if (value == -1) {
                    printf("Neuspjesno uklanjanje sa stoga.\n");
                }
                break;

            case 3:
                printf("Unesite vrijednost: ");
                scanf("%d", &value);
                printf("Unesite prioritet: ");
                scanf("%d", &priority);

                pq = push(pq, value, priority);
                break;

            case 4:
                if (isEmpty(pq)) {
                    printf("Red je prazan!\n");
                }
                else {
                    pq = pop(pq);
                }
                break;

            case 0:
                printf("Izlaz iz programa.\n");
                break;

            default:
                printf("Pogresan unos!\n");
            }

        } while (choice != 0);

        return 0;
    }
