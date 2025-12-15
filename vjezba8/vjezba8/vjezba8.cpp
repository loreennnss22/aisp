#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



typedef struct _node {
    double value;
    struct _node* next;
} Node;


Node* createNode(double value);
int push(Node** head, double value);
int pop(Node** head, double* value);
int isEmpty(Node* head);
void freeStack(Node* head);

int isOperator(char c);
int performOperation(char op, double a, double b, double* result);

int evaluatePostfixFromFile(const char* filename, double* result);



Node* createNode(double value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return NULL;
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

int push(Node** head, double value) {
    Node* newNode = createNode(value);
    if (newNode == NULL)
        return -1;

    newNode->next = *head;
    *head = newNode;
    return 0;
}

int pop(Node** head, double* value) {
    if (isEmpty(*head))
        return -1;

    Node* temp = *head;
    *value = temp->value;
    *head = temp->next;
    free(temp);
    return 0;
}

int isEmpty(Node* head) {
    return head == NULL;
}

void freeStack(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int performOperation(char op, double a, double b, double* result) {
    switch (op) {
    case '+':
        *result = a + b;
        return 0;
    case '-':
        *result = a - b;
        return 0;
    case '*':
        *result = a * b;
        return 0;
    case '/':
        if (b == 0)
            return -1;
        *result = a / b;
        return 0;
    default:
        return -1;
    }
}

int evaluatePostfixFromFile(const char* filename, double* result) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Greska: Ne mogu otvoriti datoteku %s!\n", filename);
        return -1;
    }

    Node* stack = NULL;
    char buffer[256];

    while (fscanf(file, "%255s", buffer) == 1) {

     
        if (isdigit(buffer[0]) || (buffer[0] == '-' && isdigit(buffer[1]))) {
            double value = atof(buffer);
            if (push(&stack, value) != 0) {
                freeStack(stack);
                fclose(file);
                return -1;
            }
        }
     
        else if (isOperator(buffer[0]) && strlen(buffer) == 1) {
            double b, a, res;

            if (pop(&stack, &b) != 0 || pop(&stack, &a) != 0) {
                freeStack(stack);
                fclose(file);
                return -1;
            }

            if (performOperation(buffer[0], a, b, &res) != 0) {
                freeStack(stack);
                fclose(file);
                return -1;
            }

            if (push(&stack, res) != 0) {
                freeStack(stack);
                fclose(file);
                return -1;
            }
        }
        
        else {
            printf("Greska: Nepoznat simbol '%s'\n", buffer);
            freeStack(stack);
            fclose(file);
            return -1;
        }
    }

    fclose(file);


    if (stack == NULL || stack->next != NULL) {
        freeStack(stack);
        return -1;
    }

    pop(&stack, result);
    return 0;
}


int main() {
    const char* filename = "postfix.txt";
    double result;

    if (evaluatePostfixFromFile(filename, &result) == 0) {
        printf("Rezultat postfiks izraza: %.2lf\n", result);
    }
    else {
        printf("Postfiks izraz je neispravan!\n");
    }

    return 0;
}
