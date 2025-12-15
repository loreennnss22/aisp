#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>

typedef struct Term {
    int coeff;
    int exp;
    struct Term* next;
} Term;

Term* add_term(Term* head, int coeff, int exp) {
    Term* new_term = (Term*)malloc(sizeof(Term));
    if (new_term == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return NULL;  
    }
    new_term->coeff = coeff;
    new_term->exp = exp;
    new_term->next = head;
    return new_term;
}

Term* load_polynomial(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file.\n");
        return NULL;
    }

    Term* head = NULL;
    int coeff, exp;

    while (fscanf(file, "%d %d", &coeff, &exp) ==2) {
        head = add_term(head, coeff, exp);
    }

    fclose(file);
    return head;
}

Term* add_polynomials(Term* p1, Term* p2) {
    Term* result = NULL;
    Term* temp1 = p1;
    Term* temp2;

    while (temp1) {
        result = add_term(result, temp1->coeff, temp1->exp);
        temp1 = temp1->next;
    }

   
    while (p2) {
        temp2 = result;
        int found = 0;

        
        while (temp2) {
            if (temp2->exp == p2->exp) {
                temp2->coeff += p2->coeff;
                found = 1;
                break;
            }
            temp2 = temp2->next;
        }

        
        if (!found) {
            result = add_term(result, p2->coeff, p2->exp);
        }

        p2 = p2->next;
    }

    return result;
}

Term* multiply_polynomials(Term* p1, Term* p2) {
    Term* result = NULL;

    for (Term* temp1 = p1; temp1; temp1 = temp1->next) {
        for (Term* temp2 = p2; temp2; temp2 = temp2->next) {
            int coeff = temp1->coeff * temp2->coeff;
            int exp = temp1->exp + temp2->exp;

           
            Term* temp = result;
            int found = 0;
            while (temp) {
                if (temp->exp == exp) {
                    temp->coeff += coeff;
                    found = 1;
                    break;
                }
                temp = temp->next;
            }
            if (!found) {
                result = add_term(result, coeff, exp);
            }
        }
    }

    return result;
}

void print_polynomial(Term* head) {
    Term* temp = head;
    while (temp) {
        printf("%dx^%d ", temp->coeff, temp->exp);
        if (temp->next && temp->next->coeff >= 0) printf("+ ");
        temp = temp->next;
    }
    printf("\n");
}

void free_polynomial(Term* head) {
    Term* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Term* p1 = load_polynomial("polynomial1.txt");
    Term* p2 = load_polynomial("polynomial2.txt");


    if (p1 == NULL || p2 == NULL) {
        printf("Greska: Polinomi nisu ispravno ucitani.\n");
        free_polynomial(p1);
        free_polynomial(p2);
        return 1;
    }

    printf("Polinom 1: ");
    print_polynomial(p1);

    printf("Polinom 2: ");
    print_polynomial(p2);

    Term* sum = add_polynomials(p1, p2);
    if (sum == NULL) {
        printf("Greska pri zbrajanju polinoma.\n");
        free_polynomial(p1);
        free_polynomial(p2);
        return 1;
    }

    printf("Zbroj: ");
    print_polynomial(sum);

    Term* product = multiply_polynomials(p1, p2);
    if (product == NULL) {
        printf("Greska pri mnozenju polinoma.\n");
        free_polynomial(p1);
        free_polynomial(p2);
        free_polynomial(sum);
        return 1;
    }

    printf("Umnozak: ");
    print_polynomial(product);

    free_polynomial(p1);
    free_polynomial(p2);
    free_polynomial(sum);
    free_polynomial(product);

    return 0;
}