//      function.h
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


#ifndef _FUNCTION_H_
#define _FUNCTION_H_


#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "sym.h"


struct Function {
	int retvalue_type;
	int argc;
	int * args_types;
	void (*callback)(int, struct Symbol **, struct Symbol *);
	char * label;
};


struct Symbol * sym_func_alloc(char * label, int retvalue_type, int argc, int * args_types,
								void (*callback)(int, struct Symbol **, struct Symbol *));
void sym_func_free(struct Symbol * func);


#endif /* _FUNCTION_H_ */

