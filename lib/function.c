//      function.c
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


#include "function.h"

struct Symbol * sym_func_alloc(char * label, int retvalue_type, int argc, int * args_types,
								void (*callback)(int, struct Symbol **, struct Symbol *)) {
	struct Function * func = (struct Function *) jmalloc(sizeof(struct Function));
	size_t	len = strlen(label);
	
	if (argc == 0) {
		func->argc = 0;
		func->args_types = NULL;
	} else {
		func->argc = argc;
		func->args_types = (int *) jmalloc(sizeof(int) * argc);
		memcpy((char *)func->args_types, (char *)args_types, sizeof(int) * argc);
	}
	if (label == NULL)
		error("function", "invalid parameters");
	else {
		func->label = (char *) jmalloc(len + 1);
		memcpy(func->label, label, len);
		label[len] = '\0';
	}
	func->retvalue_type = retvalue_type;
	if (callback == NULL)
		error("function", "error in registering callback");
	else
		func->callback = callback;
	return sym_alloc_shallow(SYM_TYPE_FUNC, 1, func->label, (void *)func);
}


void sym_func_free(struct Symbol * func) {
	if ((((struct Function *)func->data)->args_types) != NULL)
		jfree(((struct Function *)func->data)->args_types);
	sym_free(func);
}
