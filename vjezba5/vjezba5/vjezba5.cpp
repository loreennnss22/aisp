#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>


typedef struct _node* position;
typedef struct _node {
    int number; 
    position next;
} node;


int pushSorted(position p, int number) {
    position q = (position)malloc(sizeof(node));
    if (q == NULL) {
        printf("\nAllocation error!\n");
        return -1;
    }

    q->number = number;
    q->next = NULL;


    while (p->next != NULL && p->next->number < number) {
        p = p->next;
    }

    
    q->next = p->next;
    p->next = q;

    return 0;
}


void printList(position p) {
    if (p == NULL || p->next == NULL) {
        printf("\nLista je prazna!\n");
        return;
    }

    while (p != NULL) {
        printf("%d ", p->number);
        p = p->next;
    }
    printf("\n");
}


position unionLists(position L1, position L2) {
    position result = (position)malloc(sizeof(node)); 
    if (result == NULL) {
        printf("\nAllocation error in unionLists!\n");
        return NULL;  
    }
    

    result->next = NULL;


    while (L1 != NULL && L2 != NULL) {
        if (L1->number < L2->number) {
            pushSorted(result, L1->number);
            L1 = L1->next;
        }
        else if (L1->number > L2->number) {
            pushSorted(result, L2->number);
            L2 = L2->next;
        }
        else {
            pushSorted(result, L1->number);
            L1 = L1->next;
            L2 = L2->next;
        }
    }

    
    while (L1 != NULL) {
        pushSorted(result, L1->number);
        L1 = L1->next;
    }

    
    while (L2 != NULL) {
        pushSorted(result, L2->number);
        L2 = L2->next;
    }

    return result->next;
}


position intersectLists(position L1, position L2) {
    position result = (position)malloc(sizeof(node));  
    if (result == NULL) {
        printf("\nAllocation error in intersectLists!\n");
        return NULL; 
    }
    result->next = NULL;

    
    while (L1 != NULL && L2 != NULL) {
        if (L1->number < L2->number) {
            L1 = L1->next;
        }
        else if (L1->number > L2->number) {
            L2 = L2->next;
        }
        else {
            pushSorted(result, L1->number);
            L1 = L1->next;
            L2 = L2->next;
        }
    }

    return result->next;
}

void deleteList(position p) {
    position temp;
    while (p != NULL) {
        temp = p;
        p = p->next;
        free(temp);
    } //nez ugl delete list sredit i too
}


int main() {
    node head1, head2;
    head1.next = NULL;
    head2.next = NULL;

    int choice;
    int number;
    position result = NULL;
    int exitLoop = 1;
    while (exitLoop != 0) {
        printf("\nIzbornik:\n\n");
        printf("1 - Unos brojeva u listu L1\n");
        printf("2 - Unos brojeva u listu L2\n");
        printf("3 - Ispis liste L1\n");
        printf("4 - Ispis liste L2\n");
        printf("5 - Unija lista L1 i L2\n");
        printf("6 - Presjek lista L1 i L2\n");
        printf("0 - Izlaz\n\n");

        printf("Odabir:\t");
        scanf(" %d", &choice);

        switch (choice) {
        case 1:
            printf("\nUnesite brojeve za listu L1 (0 za kraj):\n");
            while (1) {
                printf("Unesite broj: ");
                scanf("%d", &number);
                if (number == 0) break;
                pushSorted(&head1, number); 
            }
            break;
        case 2:
            printf("\nUnesite brojeve za listu L2 (0 za kraj):\n");
            while (1) {
                printf("Unesite broj: ");
                scanf("%d", &number);
                if (number == 0) break;
                pushSorted(&head2, number);
            }
            break;
        case 3:
            printf("\nLista L1:\n");
            printList(head1.next);
            break;
        case 4:
            printf("\nLista L2:\n");
            printList(head2.next);
            break;
        case 5:
            deleteList(result);
            result = unionLists(head1.next, head2.next);
            printf("\nUnija lista:\n");
            printList(result);
            break;
        case 6:
            deleteList(result);
            result = intersectLists(head1.next, head2.next);
            printf("\nPresjek lista:\n");
            printList(result);
            break;
        case 0:
            deleteList(head1.next);
            deleteList(head2.next);
            deleteList(result);
            printf("\nIzlaz!\n");
            return 0;
        default:
            printf("\nPogrešan unos!\n");
            break;
        }
    }
}

