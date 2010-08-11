//      stack.h
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

#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "const.h"
#include "memory.h"
#include "atom.h"
#include "sym.h"

/* Generalized stack with char* data */

/* stack_alloc(void), stack_push(), stack_isempty(), stack_pop(), stack_free() */

struct Stack {
	int allocated;
	int top;
	char ** data;
};

struct Stack * stack_alloc(void);
int stack_push(struct Stack * stack, char * datum);
int stack_isempty(struct Stack * stack);
char * stack_pop(struct Stack * stack);
int stack_free(struct Stack * stack);

/* Stack with integers */

/* istack_* functions */

struct Stack * istack_alloc(void);
int istack_push(struct Stack * stack, int datum);
int istack_isempty(struct Stack * stack);
int istack_pop(struct Stack * stack);
int istack_free(struct Stack * stack);

/* Stack with atoms */

/* astack_* functions */

struct Stack * astack_alloc(void);
int astack_push(struct Stack * stack, struct Atom * atom);
int astack_isempty(struct Stack * stack);
struct Atom * astack_pop(struct Stack * stack);
int astack_free(struct Stack * stack); 

/* Stack with symbols */

/* symstack_* functions */

struct Stack * symstack_alloc(void);
int symstack_push(struct Stack * stack, struct Symbol * sym);
int symstack_isempty(struct Stack * stack);
struct Symbol * symstack_pop(struct Stack * stack);
int symstack_free(struct Stack * stack); 


#endif /* _STACK_H_ */
