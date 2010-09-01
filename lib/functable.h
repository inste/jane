//      functable.h
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


#ifndef _FUNCTABLE_H_
#define _FUNCTABLE_H_

#include <stdio.h>

#include "memory.h"
#include "sym.h"
#include "symtable.h"
#include "function.h"


rb_tree * symtable_func_init(void); // Redefinition
void functable_freeing_func(void * key, void * datum);   // Redefinition for correct freeing of memory

int functable_is_func(rb_tree * functable, char * label);

int	functable_register_function(rb_tree * functable, struct Symbol * func);
struct Symbol * functable_calling_func(rb_tree * functable, char * label, int argc, struct Symbol ** args);

#endif /* _FUNCTABLE_H_ */
