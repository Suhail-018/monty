#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monty.h"

/**
 * add - Add the top two elements of the stack.
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number in the Monty bytecode file.
 *
 * Description: This fues of the top two elements on the stack
 */
void add(stack_t **stack, unsigned int line_number)
{
if (*stack == NULL || (*stack)->next == NULL)
{
fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
exit(EXIT_FAILURE);
}
(*stack)->next->n += (*stack)->n;
pop(stack);
}

