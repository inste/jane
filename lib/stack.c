//      stack.c
//      
//      Copyright 2010 Ilya <ilya@laptop>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.

#include "stack.h"

/* Generalized stack with char* data */

/* stack_alloc(void), stack_push(), stack_isempty(), stack_pop(), stack_free() */

struct Stack * stack_alloc(void) {
	struct Stack * stack = (struct Stack *) jmalloc(sizeof(struct Stack));
	
	stack->allocated = PAGE_SIZE / sizeof(char *);
	stack->top = -1;
	stack->data = (char **) jmalloc(stack->allocated * sizeof(char *));
	return stack;
}

int stack_push(struct Stack * stack, char * datum) {
	char ** temp;
	if (stack == NULL)
		return -1;
		
	if (stack->allocated == stack->top) {
		temp = jrealloc((char **)stack->data, (stack->allocated += PAGE_SIZE / sizeof(char *)) * sizeof(char *));
		if (temp == NULL)
			return -1;
		stack->data = temp;
	}
	++stack->top;
	stack->data[stack->top] = datum;
	return 1;
}

int stack_isempty(struct Stack * stack) {
	if (stack == NULL)
		return -1;
	return (stack->top == -1) ? 1 : 0;
}

char * stack_pop(struct Stack * stack) {
	if (stack == NULL)
		return NULL;
	
	if (stack->top == -1)
		return NULL;

	return stack->data[stack->top--];
}

int stack_free(struct Stack * stack) {
	if (stack == NULL)
		return -1;
	
	jfree(stack->data);
	jfree(stack);
	return 0;
}

/* Stack with integers */

/* istack_* functions */


struct Stack * istack_alloc(void) {
	return stack_alloc();
}

int istack_push(struct Stack * stack, int datum) {
	int * pdat = (int *) jmalloc(sizeof(int));
	
	*pdat = datum;
	return stack_push(stack, (char *)pdat);
}

int istack_isempty(struct Stack * stack) {
	return stack_isempty(stack);
}

int istack_pop(struct Stack * stack) {
	int * pdat, dat;
	
	pdat = (int *)stack_pop(stack);
	dat = *pdat;
	jfree(pdat);
	return dat;
}

int istack_free(struct Stack * stack) {
	while (!istack_isempty(stack))
		istack_pop(stack);
	return stack_free(stack);
}

/* Stack with atoms */

/* astack_* functions */

struct Stack * astack_alloc(void) {
	return stack_alloc();
}

int astack_push(struct Stack * stack, struct Atom * atom) {
	return stack_push(stack, (char *) atom);
}

int astack_isempty(struct Stack * stack) {
	return stack_isempty(stack);
}

struct Atom * astack_pop(struct Stack * stack) {
	return (struct Atom *)stack_pop(stack);
}

int astack_free(struct Stack * stack) {
	return stack_free(stack);
}


/* Stack with symbols */

/* symstack_* functions */

struct Stack * symstack_alloc(void) {
	return stack_alloc();
}

int symstack_push(struct Stack * stack, struct Symbol * sym) {
	return stack_push(stack, (char *) sym);
}

int symstack_isempty(struct Stack * stack) {
	return stack_isempty(stack);
}

struct Symbol * symstack_pop(struct Stack * stack) {
	return (struct Symbol*)stack_pop(stack);
}

int symstack_free(struct Stack * stack) {
	return stack_free(stack);
}
