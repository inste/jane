//      arythm.c
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

#include "arythm.h"

int inf_check_brackets(char * expr) {
	struct Stack * stack = stack_alloc();
	int i = -1, res;
	
	while (expr[++i] != '\0')
		switch (expr[i]) {
			case '(':	stack_push(stack, NULL);
						break;
			case ')':	if (!stack_isempty(stack))
							stack_pop(stack);
						else {
							stack_free(stack);
							return 0;
						}
						break;
			default:	break;
		}
	res = stack_isempty(stack);
	stack_free(stack);
	return res;
}

int inf_get_priority(int op) {
	switch (op) {
		case	SYM_OPS_EXP		:	return PRIO_HIGHER;
		case	SYM_OPS_MUL		:	return PRIO_UPPER_MIDDLE;
		case	SYM_OPS_DIV		:	return PRIO_UPPER_MIDDLE;
		case	SYM_OPS_ADD		:	return PRIO_MIDDLE;
		case	SYM_OPS_SUB		:	return PRIO_MIDDLE;
		default					:	break;
	}
	return -1;
}

int smb_is_function(char * smb) {
	if (strcmp(smb, "sqr") == 0)
		return 1;
	return 0;
}

int is_digit(char ch) {
	return ((ch >= '0') && (ch <= '9')) ? 1 : 0;
}

int is_op(char ch) {
	return ((ch == '(') || (ch == ')') || (ch == '+') || (ch == '-') || (ch == '*') || (ch == '/') || (ch == '^')) ? 1 : 0;
}


int is_symbol(char ch) {
	return (((ch >= 'A') && (ch <= 'Z')) || ((ch >= 'a') && (ch <= 'z')) || (ch == '_')) ? 1 : 0;
}


void inf_push_elements_from_stack_to_workflow(struct WorkFlow * wf, struct Stack * stack, int prio) {
	struct Atom * atom;
	int stop = 0;
	
	while (!astack_isempty(stack) && !stop) {
		atom = astack_pop(stack);				
		if (atom->id == SYM_BRK_OPEN) {
			astack_push(stack, atom);
			break;
		} else {
			if (prio <= inf_get_priority(atom->id)) {
				workflow_add_atom(wf, atom);
				atom_free(atom);
			} else {
				astack_push(stack, atom);
				++stop;
			}
		} 
	}
}


struct WorkFlow * inf_transform_to_reverse_postfix(char * expr) {
	struct WorkFlow * wf = workflow_init();
	struct Stack * stack = astack_alloc();
	struct Atom * atom;
	int i = 0, last = 0, len = strlen(expr), stop;
	char * nmb;
	
	while (expr[i] != '\0') {
		
		if ((is_digit(expr[i]) || is_symbol(expr[i]))) {
			++i;
			continue;
		} else {
			nmb = (char *) jmalloc(len);
			strncpy(nmb, expr + last, i - last);
			nmb[i - last] = '\0';

			if (is_symbol(nmb[0])) {
				if (smb_is_function(nmb)) {
					atom = atom_alloc(SYM_FUNC, nmb);
					astack_push(stack, atom);
				} else {
					atom = atom_alloc(SYM_SYMBOL, nmb);
					workflow_add_atom(wf, atom);
					atom_free(atom);	
				}
			} else {
				if (!is_op(nmb[0]) && (nmb[0] != '\0')) {
					atom = atom_alloc(SYM_NUM, nmb);
					workflow_add_atom(wf, atom);
					atom_free(atom);		
				} else
					jfree(nmb);
			}
			
			last = i + 1;
			switch (expr[i]) {
				case '(' :	atom = atom_alloc(SYM_BRK_OPEN, NULL);
							astack_push(stack, atom);
							break;
				case ')' :	stop = 0;
							while (!stop) {
								if (!astack_isempty(stack)) {
									atom = astack_pop(stack);
									if (atom->id != SYM_BRK_OPEN) {
										workflow_add_atom(wf, atom);
										atom_free(atom);
									} else {
										stop = 1;
										atom_free(atom);
										if (!astack_isempty(stack)) {
											atom = astack_pop(stack);
											if (atom->id == SYM_FUNC) {
												workflow_add_atom(wf, atom);
												atom_free(atom);
											} else
												astack_push(stack, atom);
										}
									}
								} else
									stop = 1;
							}
							break;
				case '^' :	atom = atom_alloc(SYM_OPS_EXP, NULL);
							inf_push_elements_from_stack_to_workflow(wf, stack, inf_get_priority(SYM_OPS_EXP));
							astack_push(stack, atom);
							break;
				case '*' :	atom = atom_alloc(SYM_OPS_MUL, NULL);
							inf_push_elements_from_stack_to_workflow(wf, stack, inf_get_priority(SYM_OPS_MUL));
							astack_push(stack, atom);
							break;
				case '/' :	atom = atom_alloc(SYM_OPS_DIV, NULL);
							inf_push_elements_from_stack_to_workflow(wf, stack, inf_get_priority(SYM_OPS_DIV));
							astack_push(stack, atom);
							break;
				case '+' :	atom = atom_alloc(SYM_OPS_ADD, NULL);
							inf_push_elements_from_stack_to_workflow(wf, stack, inf_get_priority(SYM_OPS_ADD));
							astack_push(stack, atom);
							break;
				case '-' :	atom = atom_alloc(SYM_OPS_SUB, NULL);
							inf_push_elements_from_stack_to_workflow(wf, stack, inf_get_priority(SYM_OPS_SUB));
							astack_push(stack, atom);
							break;
				default:
							break;
			}
		}
		++i;
	}

	nmb = (char *) jmalloc(len);
	strncpy(nmb, expr + last, len - last);
	nmb[len - last] = '\0';

	if (is_symbol(nmb[0])) {
		if (smb_is_function(nmb)) {
			atom = atom_alloc(SYM_FUNC, nmb);
			astack_push(stack, atom);
		} else {
			atom = atom_alloc(SYM_SYMBOL, nmb);
			workflow_add_atom(wf, atom);
			atom_free(atom);	
		}
	} else {	
		if (!is_op(nmb[0]) && (nmb[0] != '\0')) {
			atom = atom_alloc(SYM_NUM, nmb);
			workflow_add_atom(wf, atom);
			atom_free(atom);		
		} else
			jfree(nmb);
	}
	
	while (!stack_isempty(stack)) {
		atom = astack_pop(stack);
		workflow_add_atom(wf, atom);
		atom_free(atom);
	}
	astack_free(stack);
	return wf;
}
