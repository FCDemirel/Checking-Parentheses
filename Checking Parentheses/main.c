#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

struct Stack {
    int top;
    char items[MAX_SIZE];
};

void initialize(struct Stack *stack);
int isEmpty(const struct Stack *stack);
int isFull(const struct Stack *stack);
void push(struct Stack *stack, char item);
char pop(struct Stack *stack);
int isMatching(char opening, char closing);
void checkParenthesesErrors(const char *filename);

int main() {
    char filename[100];

    printf("Enter the filename: ");
    scanf("%s", filename);

    checkParenthesesErrors(filename);

    return 0;
}

// To initialize the stack
void initialize(struct Stack *stack) {
    stack->top = -1;
}

// To check if the stack is empty
int isEmpty(const struct Stack *stack) {
    return stack->top == -1;
}

// To check if the stack is full
int isFull(const struct Stack *stack) {
    return stack->top == MAX_SIZE - 1;
}

// To push an element onto the stack
void push(struct Stack *stack, char item) {
    if (isFull(stack)) {
        printf("Stack is full\n");
        exit(EXIT_FAILURE);
    }
    stack->items[++stack->top] = item;
}

// To pop an element from the stack
char pop(struct Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return stack->items[stack->top--];
}

// To check if two parentheses form a matching pair
int isMatching(char opening, char closing) {
    return (opening == '(' && closing == ')') ||
           (opening == '{' && closing == '}') ||
           (opening == '[' && closing == ']');
}

// To check for parentheses errors in the code
void checkParenthesesErrors(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("File not found");
        exit(EXIT_FAILURE);
    }

    struct Stack stack;
    initialize(&stack);

    char ch;
    int line = 1;

    // To read file
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            line++;
        } else if (ch == '(' || ch == '{' || ch == '[') {
            push(&stack, ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (isEmpty(&stack) || !isMatching(pop(&stack), ch)) {
                if (isEmpty(&stack)) {
                    printf("Extra %c at line %d\n", ch, line);
                } else {
                    printf("Mismatched %c at line %d\n", ch, line);
                }
            }
        }
    }

    // To check for any remaining opening parentheses
    while (!isEmpty(&stack)) {
        printf("Missing %c at line %d\n", pop(&stack), line);
    }

    fclose(file);
}
