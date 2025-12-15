
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _person* position;
typedef struct _person {
    char name[30];
    char lastname[30];
    int yearOfBirth;
    position next;
} person;

int insert(position p) {
    position q = (position)malloc(sizeof(person));
    if (q == NULL) {
        printf("\nAllocation error!\n");
        return -1;
    }
    printf("\nEnter first name, last name, and year of birth:\t");
    scanf_s(" %s %s %d", q->name, q->lastname, &q->yearOfBirth);
    q->next = p->next;
    p->next = q;
    return 0;
}

int printList(position p) {
    printf("\nList:\n");
    if (p == NULL) {
        printf("\nThe list is empty!\n");
        return -1;
    }
    while (p != NULL) {
        printf(" %s %s %d\n", p->name, p->lastname, p->yearOfBirth);
        p = p->next;
    }
    return 0;
}

void deleteList(position p) {
    position temp;
    while (p != NULL) {
        temp = p;
        p = p->next;
        free(temp);
    }
}

int addElOnTheEnd(position p) {
    while (p->next != NULL) {
        p = p->next;
    }
    return insert(p);
}

position searchByLastname(position p) {
    char lastname[20];
    printf("\nEnter the last name of the person you are looking for:\t");
    scanf_s(" %s", lastname);

    while (p != NULL && strcmp(p->lastname, lastname) != 0) {
        p = p->next;
    }
    return p;
}

void deleteEl(position p) {
    position temp;
    char lastname[20];

    printf("\nEnter the last name of the person you want to delete from the list:\t");
    scanf_s(" %s", lastname);

    while (p->next != NULL && strcmp(p->next->lastname, lastname) != 0) {
        p = p->next;
    }
    if (p->next != NULL) {
        temp = p->next;
        p->next = temp->next;
        printf("\nThe person %s %s %d has been deleted.\n", temp->name, temp->lastname, temp->yearOfBirth);
        free(temp);
    }
    else {
        printf("\nThe person does not exist.\n");
    }
}

int addElAfter(position p) {
    char lastname[20];

    position temp = searchByLastname(p->next);
    if (temp == NULL) {
        printf("\nPerson not found!\n");
        return -1;
    }

    return insert(temp);
}

position searchElBefore(char* lastName, position p) {
    position previous = p;
    p = p->next;

    while (p != NULL && strcmp(p->lastname, lastName) != 0) {
        previous = p;
        p = p->next;
    }
    return (p == NULL) ? NULL : previous;
}

int addElBefore(position p) {
    char lastname[20];
    printf("\nEnter the last name of the person before whom you want to insert a new person:\t");
    scanf_s(" %s", lastname);

    position temp = searchElBefore(lastname, p);
    if (temp == NULL) {
        printf("\nPerson not found!\n");
        return -1;
    }

    return insert(temp);
}

int printListToFile(position p) {
    char fileName[30];
    FILE* fp;

    printf("\nEnter the file name:\t");
    scanf_s(" %s", fileName);

    fp = fopen(fileName, "w");
    if (fp == NULL) {
        printf("\nThe file could not be opened!\n");
        return -1;
    }

    if (p == NULL) {
        printf("\nThe list is empty!\n");
    }
    else {
        while (p != NULL) {
            fprintf(fp, "%s %s %d\n", p->name, p->lastname, p->yearOfBirth);
            p = p->next;
        }
    }
    fclose(fp);
    return 0;
}

int readListFromFile(position p) {
    position q;
    char fileName[30];
    FILE* fp;

    printf("\nEnter the file name:\t");
    scanf_s(" %s", fileName);

    fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("\nThe file could not be opened!\n");
        return -1;
    }

    while (1) {
        q = (position)malloc(sizeof(person));
        if (q == NULL) {
            printf("\nAllocation error!\n");
            fclose(fp);
            return -1;
        }

        if (fscanf(fp, " %29s %29s %d", q->name, q->lastname, &q->yearOfBirth) != 3) {
            free(q);
            break;
        }
        printf("%s %s %d\n", q->name, q->lastname, q->yearOfBirth);

        q->next = p->next;
        p->next = q;
    }
    fclose(fp);

    return 0;
}

int main() {
    person head;
    head.next = NULL;

    position personTemp = NULL;
    int choice = 1;
    int check = 0;

    while (choice) {
        printf("\n\nMenu:\n\n");
        printf(" 1 - Add at the beginning of the list\n 2 - Print list\n 3 - Add an element at the end of the list\n 4 - Search for an element by last name\n 5 - Delete an element\n");
        printf(" 6 - Add after an element\n 7 - Add before an element\n 8 - Sorted insert\n 9 - Write list to file\n 10 - Read list from file\n");
        printf(" 11 - Delete list\n 0 - Exit\n\n");

        printf("Selection:\t");
        scanf_s(" %d", &choice);

        switch (choice) {
        case 1:
            check = insert(&head);
            if (check == -1) {
                deleteList(&head);
                return 0;
            }
            break;

        case 2:
            check = printList(head.next);
            break;

        case 3:
            check = addElOnTheEnd(&head);
            if (check == -1) {
                deleteList(&head);
                return 0;
            }
            break;

        case 4:
            personTemp = searchByLastname(head.next);
            if (personTemp != NULL) {
                printf("\nThe found person %s %s %d\n", personTemp->name, personTemp->lastname, personTemp->yearOfBirth);
            }
            else {
                printf("\nThe person does not exist!\n");
            }
            break;

        case 5:
            deleteEl(&head);
            break;

        case 6:
            check = addElAfter(&head);
            if (check == -1) {
                deleteList(&head);
                return 0;
            }
            break;

        case 7:
            check = addElBefore(&head);
            if (check == -1) {
                deleteList(&head);
                return 0;
            }
            break;

        case 8:
            check = addElOnTheEnd(&head);
            if (check == -1) {
                deleteList(&head);
                return 0;
            }
            break;

        case 9:
            check = printListToFile(head.next);
            break;

        case 10:
            check = readListFromFile(&head);
            break;

        case 11:
            deleteList(&head);
            printf("\nThe list has been deleted!\n");
            break;
        case 0:
            deleteList(&head);
            printf("\nExiting!\n");
            break;

        default:
            printf("\nInvalid input!\n");
        }
    }

    return 0;
}
