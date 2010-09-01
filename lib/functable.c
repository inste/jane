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

rb_tree * functable_init(void) {	
	dict_set_malloc((dict_malloc_func)jmalloc);
	dict_set_free((dict_free_func)jfree);
	return rb_tree_new((dict_compare_func)functable_compare_func, (dict_delete_func)functable_freeing_func);
}

void functable_freeing_func(void * key, void * datum) {
	if (datum != NULL)
		func_free((struct Function *)datum);
}

int functable_compare_func(const void * p1, const void * p2) {
	return strcmp((const char *)p1, (const char *)p2);
}

int functable_is_func(rb_tree * functable, char * label) {
	return (rb_tree_search(functable, label) != NULL) ? 1 : 0;
}

void functable_register_function(rb_tree * functable, struct Function * func) {
	if (functable_is_func(functable, func->label))
		warning("functable", "trying to register already registered function, overwriting");
	
	rb_tree_insert(functable, func->label, func, 1);
}

struct Function * functable_get_function(rb_tree * functable, char * label) {
	if (!functable_is_func(functable, label))
		error("functable", "trying to get unexisting function");
		
	return (struct Function *)rb_tree_search(functable, label);
}

struct Symbol * functable_calling_func(rb_tree * functable, char * label, int argc, struct Symbol ** args) {
	struct Symbol * retval;
	struct Function * func;
	int i;
	
	if (functable == NULL)
		error("functable", "uninitialiazed functable");
		
	func = (struct Function *)rb_tree_search(functable, label);
	if (argc != func->argc)
		error("functable", "parameters mismatch");
		
	for (i = 0; i < argc; ++i)
		if (args[i]->type != func->args_types[i])
			error("functable", "wrong types of parameters");
	
	retval = sym_alloc_shallow(func->retvalue_type, 0, NULL, NULL);
	func->callback(argc, args, retval);
	
	return retval;
}

void functable_shutdown(rb_tree * tree) {
	rb_tree_destroy(tree);
}
