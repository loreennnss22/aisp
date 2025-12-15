#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _node* position;
typedef struct _node {
    int value;
    position next;
} node;



position createNode() {
    position q = (position)malloc(sizeof(node));
    if (q == NULL) {
        printf("\nGreska pri alokaciji memorije!\n");
        return NULL;
    }

    q->value = rand() % 91 + 10;  
    q->next = NULL;
    return q;
}

void printList(position p) {
    if (p == NULL) {
        printf("\nLista je prazna!\n");
        return;
    }

    while (p != NULL) {
        printf("%d ", p->value);
        p = p->next;
    }
    printf("\n");
}

void deleteList(position p) {
    position temp;
    while (p != NULL) {
        temp = p;
        p = p->next;
        free(temp);
    }
}



int push(position head) {
    position q = createNode();
    if (q == NULL)
        return -1;

    q->next = head->next;
    head->next = q;

    printf("\nDodan: %d\n", q->value);
    return 0;
}

int pop(position head) {
    if (head->next == NULL) {
        printf("\nStog je prazan!\n");
        return -1;
    }

    position temp = head->next;
    head->next = temp->next;

    printf("\nIzbacen: %d\n", temp->value);
    free(temp);
    return 0;
}



int enqueue(position head) {
    position q = createNode();
    if (q == NULL)
        return -1;

    position p = head;
    while (p->next != NULL)
        p = p->next;

    p->next = q;
    printf("\nDodan: %d\n", q->value);
    return 0;
}

int dequeue(position head) {
    if (head->next == NULL) {
        printf("\nRed je prazan!\n");
        return -1;
    }

    position temp = head->next;
    head->next = temp->next;

    printf("\nIzbacen: %d\n", temp->value);
    free(temp);
    return 0;
}


int main() {
    node stackHead;
    node queueHead;

    stackHead.next = NULL;
    queueHead.next = NULL;

    int choice = 1;
    srand((unsigned)time(NULL));

    while (choice) {
        printf("\n\n IZBORNIK \n");
        printf("1 - Dodaj element na stog.\n");
        printf("2 - Izbaci element sa stoga.\n");
        printf("3 - Ispis stoga.\n");
        printf("4 - Dodaj element u red.\n");
        printf("5 - Izbaci element iz reda.\n");
        printf("6 - Ispis reda.\n");
        printf("7 - OBRISI SVE\n");
        printf("0 - IZLAZ\n\n");

        printf("Odabir: ");
        scanf(" %d", &choice);

        switch (choice) {
        case 1:
            push(&stackHead);
            break;

        case 2:
            pop(&stackHead);
            break;

        case 3:
            printList(stackHead.next);
            break;

        case 4:
            enqueue(&queueHead);
            break;

        case 5:
            dequeue(&queueHead);
            break;

        case 6:
            printList(queueHead.next);
            break;

        case 7:
            deleteList(stackHead.next);
            deleteList(queueHead.next);
            stackHead.next = NULL;
            queueHead.next = NULL;
            printf("\nSve liste su obrisane!\n");
            break;

        case 0:
            deleteList(stackHead.next);
            deleteList(queueHead.next);
            printf("\nIzlaz iz programa.\n");
            break;

        default:
            printf("\nPogresan unos!\n");
        }
    }

    return 0;
}
