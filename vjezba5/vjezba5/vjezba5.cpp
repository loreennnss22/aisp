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
        printf("Greska pri alokaciji memorije!\n");
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
    if (p == NULL) {
        printf("Lista je prazna!\n");
        return;
    }

    while (p != NULL) {
        printf("%d ", p->number);
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

position unionLists(position L1, position L2) {
    position head = (position)malloc(sizeof(node));
    if (head == NULL) {
        printf("Greska pri alokaciji (union)!\n");
        return NULL;
    }
    head->next = NULL;

    while (L1 != NULL && L2 != NULL) {
        int value;

        if (L1->number < L2->number) {
            value = L1->number;
            L1 = L1->next;
        }
        else if (L1->number > L2->number) {
            value = L2->number;
            L2 = L2->next;
        }
        else {
            value = L1->number;
            L1 = L1->next;
            L2 = L2->next;
        }

        if (pushSorted(head, value) == -1) {
            deleteList(head);
            return NULL;
        }
    }

    while (L1 != NULL) {
        if (pushSorted(head, L1->number) == -1) {
            deleteList(head);
            return NULL;
        }
        L1 = L1->next;
    }

    while (L2 != NULL) {
        if (pushSorted(head, L2->number) == -1) {
            deleteList(head);
            return NULL;
        }
        L2 = L2->next;
    }

    position result = head->next;
    free(head);
    return result;
}

position intersectLists(position L1, position L2) {
    position head = (position)malloc(sizeof(node));
    if (head == NULL) {
        printf("Greska pri alokaciji (presjek)!\n");
        return NULL;
    }
    head->next = NULL;

    while (L1 != NULL && L2 != NULL) {
        if (L1->number < L2->number)
            L1 = L1->next;
        else if (L1->number > L2->number)
            L2 = L2->next;
        else {
            if (pushSorted(head, L1->number) == -1) {
                deleteList(head);
                return NULL;
            }
            L1 = L1->next;
            L2 = L2->next;
        }
    }

    position result = head->next;
    free(head);
    return result;
}



int main() {
    node head1 = { 0, NULL };
    node head2 = { 0, NULL };
    position result = NULL;

    int choice, number;

    while (1) {
        printf("\nIzbornik:\n");
        printf("1 - Unos L1\n2 - Unos L2\n3 - Ispis L1\n4 - Ispis L2\n");
        printf("5 - Unija\n6 - Presjek\n0 - Izlaz\n");
        printf("Odabir: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Unos L1 (0 za kraj):\n");
            while (1) {
                scanf("%d", &number);
                if (number == 0) break;
                if (pushSorted(&head1, number) == -1)
                    return 1;
            }
            break;

        case 2:
            printf("Unos L2 (0 za kraj):\n");
            while (1) {
                scanf("%d", &number);
                if (number == 0) break;
                if (pushSorted(&head2, number) == -1)
                    return 1;
            }
            break;

        case 3:
            printList(head1.next);
            break;

        case 4:
            printList(head2.next);
            break;

        case 5:
            deleteList(result);
            result = unionLists(head1.next, head2.next);
            if (result == NULL) return 1;
            printList(result);
            break;

        case 6:
            deleteList(result);
            result = intersectLists(head1.next, head2.next);
            if (result == NULL) return 1;
            printList(result);
            break;

        case 0:
            deleteList(head1.next);
            deleteList(head2.next);
            deleteList(result);
            printf("Izlaz!\n");
            return 0;

        default:
            printf("Pogresan unos!\n");
        }
    }
}

