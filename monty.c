#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monty.h"

/**
 * push - Push an element onto the stack
 * @stack: Pointer to the stack
 * @line_number: Line number in the Monty bytecode file
 * @value: Value to push onto the stack
 *
 * Description: This function creates a new node with the given value and
 * pushes it onto the stack.
 */

void push(stack_t **stack, int value)
{
stack_t *new_node;
new_node = malloc(sizeof(stack_t));
if (new_node == NULL)
{
fprintf(stderr, "Error: malloc failed\n");
exit(EXIT_FAILURE);
}
new_node->n = value;
new_node->prev = NULL;
new_node->next = *stack;

if (*stack != NULL)
{
(*stack)->prev = new_node;
}
*stack = new_node;
}
/**
 * pall - Print all values on the stack
 * @stack: Pointer to the stack
 * @line_number: Line number in the Monty bytecode file
 *
 * Description: This function prints all the integer values in the stack,
 * starting from the top of the stack.
 */
void pall(stack_t **stack)
{
stack_t *current;
current = *stack;
while (current != NULL)
{
printf("%d\n", current->n);
current = current->next;
}
}
/**
 * pop - Remove the top element from the stack.
 * @stack: Double pointer to the top of the stack.
 *
 * This function removes the top element from the stack. If the stack is empty,
 *  The memory occupied by the removed node is freed to prevent memory leaks.
 */
void pop(stack_t **stack)
{
stack_t *current;
current = *stack;
*stack = current->next;
free(current);
}
/**
 * swap - Swap the top two elements of the stack.
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number in the Monty bytecode file.
 *
 * Description: This function swaps the top two elements of the stack.
 * If the stack contains less than two elements, an error message is printed
 * to stderr, and the program exits with a failure status.
 */
void swap(stack_t **stack, unsigned int line_number)
{
int tmp;
if (stack == NULL || (*stack)->next == NULL)
{
fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
exit(EXIT_FAILURE);
}
tmp = (*stack)->n;
(*stack)->n = (*stack)->next->n;
(*stack)->next->n = tmp;
}

/**
 * main - Entry point of the Monty interpreter
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Description: This function reads and interprets Monty bytecode files,
 * executing the specified operations.
 * Return: EXIT_SUCCESS on successful execution, or EXIT_FAILURE on error
 */
int main(int argc, char *argv[])
{
FILE *file;
stack_t *stack;
char *opcode;
char *arg;
char line[1024];
int value;
unsigned int line_number = 0;
if (argc != 2)
{
fprintf(stderr, "Usage: monty file\n");
return (EXIT_FAILURE);
}
file = fopen(argv[1], "r");
if (file == NULL)
{
fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
return (EXIT_FAILURE);
}
stack = NULL;
while (fgets(line, sizeof(line), file))
{
line_number++;
opcode = strtok(line, " \t\n");
if (opcode == NULL || opcode[0] == '#')
{
continue;
}
if (strcmp(opcode, "push") == 0)
{
arg = strtok(NULL, " \t\n");
if (arg == NULL)
{
fprintf(stderr, "L%d: usage: push integer\n", line_number);
return (EXIT_FAILURE);
}
value = atoi(arg);
push(&stack, value);
}
else if (strcmp(opcode, "pall") == 0)
{
pall(&stack);
}
else if (strcmp(opcode, "pint") == 0)
{
if (stack == NULL)
{
fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
return (EXIT_FAILURE);
}
printf("%d\n", stack->n);
}
else if (strcmp(opcode, "pop") == 0)
{
if (stack == NULL)
{
fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
exit(EXIT_FAILURE);
}
pop(&stack);
}
else if (strcmp(opcode, "swap") == 0)
{
swap(&stack, line_number);
}
else if (strcmp(opcode, "add") == 0)
{
add(&stack, line_number);
}
else
{
fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
return (EXIT_FAILURE);
}
}
fclose(file);
return (0);
}
