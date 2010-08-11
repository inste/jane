//      sym.h
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

#ifndef _SYM_H_
#define _SYM_H_

#include <stdio.h>
#include <string.h>

#include "const.h"
#include "memory.h"

struct Symbol {
	int type;
	int is_constant;
	char * label;
	void * data;
};

struct Symbol * sym_alloc_shallow(int type, int is_constant, char * label, void * data);
struct Symbol * sym_alloc_deep(int type, int is_constant, char * label, void * data, int data_size);
void sym_set_constant(struct Symbol * sym);
void sym_set_variable(struct Symbol * sym);
int sym_is_constant(struct Symbol * sym);
void sym_free(struct Symbol * sym);

#endif
