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
    printf("\nUnesite ime, prezime i godinu roðenja:\t");
    scanf(" %s %s %d", q->name, q->lastname, &q->yearOfBirth);
    q->next = p->next;
    p->next = q;
    return 0;
}

int printList(position p) {
    printf("\nLista:\n");
    if (p == NULL) {
        printf("\nLista je prazna!\n");
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
    printf("\nUnesite prezime osobe koju trazite:\t");
    scanf(" %s", lastname);

    while (p != NULL && strcmp(p->lastname, lastname) != 0) {
        p = p->next;
    }
    return p;
}

void deleteEl(position p) {
    position temp;
    char lastname[20];

    printf("\nUnesite prezime osobe koju zelite obrisati iz liste:\t");
    scanf(" %s", lastname);

    while (p->next != NULL && strcmp(p->next->lastname, lastname) != 0) {
        p = p->next;
    }
    if (p->next != NULL) {
        temp = p->next;
        p->next = temp->next;
        printf("\nOsoba %s %s %d je izbrisana.\n", temp->name, temp->lastname, temp->yearOfBirth);
        free(temp);
    }
    else {
        printf("\nOsoba ne postoji.\n");
    }
}

int addElAfter(position p) {
    char lastname[20];
   

    position temp = searchByLastname(p->next);
    if (temp == NULL) {
        printf("\nOsoba nije pronadena!\n");
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
    printf("\nUnesite prezime osobe ispred koje zelite unijeti novu osobu:\t");
    scanf(" %s", lastname);

    position temp = searchElBefore(lastname, p);
    if (temp == NULL) {
        printf("\nOsoba nije pronadena!\n");
        return -1;
    }

    return insert(temp);
}
int printListToFile(position p) {
    char fileName[30];
    FILE* fp;

    printf("\nUnesite ime datoteke:\t");
    scanf(" %s", fileName);

    fp = fopen(fileName, "w");
    if (fp == NULL) {
        printf("\nDatoteka nije otvorena!\n");
        return -1;
    }

    if (p == NULL) {
        printf("\nLista je prazna!\n");
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

    printf("\nUnesite ime datoteke:\t");
    scanf(" %s", fileName);

    fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("\nDatoteka nije otvorena!\n");
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
        printf("\n\nIzbornik:\n\n");
        printf(" 1 - Unos na pocetak liste\n 2 - Ispisi listu\n 3 - Dodaj element na kraj liste\n 4 - Pronadi element po prezimenu\n 5 - Izbrisi element\n");
        printf(" 6 - Dodaj iza elementa\n 7 - Dodaj ispred elementa\n 8 - Sortirani unos\n 9 - Upisi listu u datoteku\n 10 - Procitaj listu iz datoteke\n");
        printf(" 11 - Brisi listu\n 0 - Izlaz\n\n");

        printf("Odabir:\t");
        scanf(" %d", &choice);

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
                printf("\nTrazena osoba %s %s %d\n", personTemp->name, personTemp->lastname, personTemp->yearOfBirth);
            }
            else {
                printf("\nTrazena osoba ne postoji!\n");
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
            printf("\nLista je obrisana!\n");
            break;
        case 0:
            deleteList(&head);
            printf("\nIzlaz!\n");
            break;

        default:
            printf("\nPogresan unos!\n");
        }
    }

    return 0;
}
