//      stdlib_arythm_ops.c
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


#include "stdlib_arythm_ops.h"

void stdlib_arythm_register(rb_tree * functable) {
	stdlib_arythm_rcmp_register(functable);
}

void stdlib_arythm_rcmp_register(rb_tree * functable) {
	struct Function * func;
	struct Symbol * sym;
	int * types = (int *) jmalloc(sizeof(int) * 2);
	
	types[0] = types[1] = SYM_TYPE_RATIONAL;
	func = sym_func_alloc("rcmp", SYM_TYPE_RATIONAL, 2, types, (_callback)rcmp);
	sym = sym_alloc_deep(SYM_TYPE_FUNC, 1, func->label, (void *)func, sizeof(struct Function));
	functable_register_function(functable, sym);
}


void rcmp(int result_type, struct Symbol ** params, struct Symbol * result) {
	struct Rational * r = (struct Rational *)result->data;
	
	r->denom = 1;
	r->num = sym_rational_is_eq(params[0], params[1]);
}
