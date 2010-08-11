//      postfix_interp.c
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


#include "postfix_interp.h"

void process_operator(struct Stack * symstack, rb_tree * symtab, int operator) {
	struct Symbol * symres, * syml, * symr;

	if (!symstack_isempty(symstack))
		symr = symstack_pop(symstack);
	else
		error("postfix_interp", " (symr) stack is empty");
	if (!symstack_isempty(symstack))
		syml = symstack_pop(symstack);
	else
		error("postfix_interp", " (syml) stack is empty");
	
	switch (operator) {
		case	SYM_OPS_ADD:	symres = sym_rational_add(syml, symr);
								break;
		case	SYM_OPS_SUB:	symres = sym_rational_sub(syml, symr);
								break;
		case	SYM_OPS_MUL:	symres = sym_rational_mul(syml, symr);
								break;
		case	SYM_OPS_DIV:	symres = sym_rational_div(syml, symr);
								break;
		default:				break;
	}								
	
	sym_rational_free(syml);
	sym_rational_free(symr);
	symstack_push(symstack, symres);
}

struct Symbol * process_postfix_workflow(struct WorkFlow * wf, rb_tree * symtab) {
	struct Stack * symstack = symstack_alloc();
	struct Symbol * s;
	int i;
	
	for(i = 0; i < wf->count; ++i) {
		switch (wf->ops[i].id) {
			case	SYM_NUM:		s = sym_rational_tmp_alloc(atoi((char *)wf->ops[i].data), 1);
									symstack_push(symstack, s);
									break;
			case	SYM_SYMBOL:		s = symtable_search_for_symbol(symtab, (char *)wf->ops[i].data);
									if (s == NULL)
										error("postfix_interp", " search in symtable failed: not found");
									else
										symstack_push(symstack, s);
									break;
			default:				process_operator(symstack, symtab, wf->ops[i].id);
									break;
		}
	}
	
	if (symstack_isempty(symstack))
		error("postfix_interp", " free stack");
		
	s = symstack_pop(symstack);
	symstack_free(symstack);
	return s;
}

