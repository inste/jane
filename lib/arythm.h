//      arythm.h
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

#ifndef _ARYTHM_H_
#define _ARYTHM_H_

#include <stdio.h>
#include <string.h>

#include "const.h"
#include "memory.h"
#include "error.h"
#include "stack.h"
#include "atom.h"
#include "workflow.h"
#include "sym.h"
#include "sym_rational_ops.h"
#include "symtable.h"
#include "postfix_interp.h"

int inf_check_brackets(char * expr);
int inf_get_priority(int op);
int smb_is_function(char * smb);
int is_digit(char ch);
int is_op(char ch);
int is_symbol(char ch);

void inf_push_elements_from_stack_to_workflow(struct WorkFlow * wf, struct Stack * stack, int prio);
struct WorkFlow * inf_transform_to_reverse_postfix(char * expr);


#endif /* _ARYTHM_H_ */
