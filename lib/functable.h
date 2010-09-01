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
#include "function.h"
#include "sym.h"
#include "rb_tree/dict.h"
#include "rb_tree/rb_tree.h"

rb_tree * functable_init(void);

int functable_is_func(rb_tree * functable, char * label);
void functable_register_function(rb_tree * functable, struct Function * func);
struct Symbol * functable_calling_func(rb_tree * functable, char * label, int argc, struct Symbol ** args);
struct Function * functable_get_function(rb_tree * functable, char * label);

void functable_shutdown(rb_tree * tree);


int functable_compare_func(const void * p1, const void * p2);
void functable_freeing_func(void * key, void * datum);


#endif /* _FUNCTABLE_H_ */
