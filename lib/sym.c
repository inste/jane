//      sym.c
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


#include "sym.h"

struct Symbol * sym_alloc_shallow(int type, int is_constant, char * label, void * data) {
	struct Symbol * sym;
	
	sym = (struct Symbol *) jmalloc(sizeof(struct Symbol));
	sym->type = type;
	sym->is_constant = is_constant;
	sym->label = label;
	sym->data = data;
	return sym;
}

struct Symbol * sym_alloc_deep(int type, int is_constant, char * label, void * data, int data_size) {
	struct Symbol * sym;
	
	sym = sym_alloc_shallow(type, is_constant, NULL, NULL);
	sym->label = (char *) jmalloc(strlen(label) + 1);
	strcpy(sym->label, label);
	sym->data = jmalloc(data_size);
	memcpy((char *)sym->data, (char *)data, data_size);
	return sym;
}

void sym_set_constant(struct Symbol * sym) {
	sym->is_constant = 1;
}

void sym_set_variable(struct Symbol * sym) {
	sym->is_constant = 0;
}

int sym_is_constant(struct Symbol * sym) {
	return sym->is_constant;
}

void sym_free(struct Symbol * sym) {
	if (sym->label != NULL)
		jfree(sym->label);
	if (sym->data != NULL)
		jfree(sym->data);
	jfree(sym);
}
