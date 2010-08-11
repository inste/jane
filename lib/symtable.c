//      symtable.c
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

#include "symtable.h"

rb_tree * symtable_init(void) {	
	dict_set_malloc((dict_malloc_func)jmalloc);
	dict_set_free((dict_free_func)jfree);
	return rb_tree_new((dict_compare_func)symtable_compare_func, (dict_delete_func)symtable_freeing_func);
}

void symtable_add_replace_symbol(rb_tree * tree, struct Symbol * sym) {
	rb_tree_insert(tree, sym->label, sym, 1);
}

struct Symbol * symtable_search_for_symbol(rb_tree * tree, char * label) {
	return rb_tree_search(tree, label);
}

void symtable_shutdown(rb_tree * tree) {
	rb_tree_destroy(tree);
}

int symtable_compare_func(const void * p1, const void * p2) {
	return strcmp((const char *)p1, (const char *)p2);
}

void symtable_freeing_func(void * key, void * datum) {
	if (datum != NULL)
		sym_free(datum);
}

int v(void * key, void * d) {
	printf("'%s', value: %d\n", (char *) key, *(int *)(((struct Symbol *)d)->data));
	return 1;
}

/*

int main(void) {
	rb_tree * s;
	int i;
	
	memstat_init();
	jmm_init();
	s = symtable_init();
	
	i = 15;
	symtable_add_replace_symbol(s, sym_alloc_deep(SYM_TYPE_INTEGER, 0, "a", &i, sizeof(int)));
	
	i = 35;
	symtable_add_replace_symbol(s, sym_alloc_deep(SYM_TYPE_INTEGER, 0, "q", &i, sizeof(int)));
	
	i = 16;
	symtable_add_replace_symbol(s, sym_alloc_deep(SYM_TYPE_INTEGER, 0, "myvar", &i, sizeof(int)));	
	
	rb_tree_walk(s, (dict_visit_func)v);
	
	symtable_shutdown(s);
	jmm_shutdown();
	memstat_shutdown();
	return 0;
}
*/
