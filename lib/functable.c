//      functable.c
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


#include "functable.h"

rb_tree * symtable_func_init(void) {	
	dict_set_malloc((dict_malloc_func)jmalloc);
	dict_set_free((dict_free_func)jfree);
	return rb_tree_new((dict_compare_func)symtable_compare_func, (dict_delete_func)functable_freeing_func);
}

void functable_freeing_func(void * key, void * datum) {
	if (datum != NULL)
		sym_func_free(datum);
}

int	functable_register_function(rb_tree * functable, struct Symbol * func) {
	if (symtable_search_for_symbol(functable, func->label) != NULL)
		warning("functable", "trying to register already registered function, overwriting");
	
	rb_tree_insert(functable, func->label, func, 1);
}

struct Symbol * functable_calling_func(rb_tree * functable, char * label, int argc, struct Symbol ** args) {
	struct Symbol * symfunc, * retval;
	struct Function * func;
	
	if (functable == NULL)
		error("functable", "uninitialiazed functable");
		
	symfunc = symtable_search_for_symbol(functable, label);
	if (symfunc == NULL)
		error("functable", "calling undefined function");
		
	func = (struct Function *)symfunc->data;
	
	retval = sym_alloc_shallow(func->retvalue_type, 0, NULL, NULL);
	func->callback(argc, args, retval);
	
	return retval;
}
