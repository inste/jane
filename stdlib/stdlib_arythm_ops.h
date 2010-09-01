//      stdlib_arythm_ops.h
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


#ifndef _STDLIB_ARYTHM_OPS_
#define _STDLIB_ARYTHM_OPS_

#include <stdio.h>

#include "../lib/error.h"
#include "../lib/memory.h"
#include "../lib/sym.h"
#include "../lib/sym_rational_ops.h"
#include "../lib/function.h"
#include "../lib/functable.h"

/* Registering stdlib arythm functions */

void stdlib_arythm_register(rb_tree * functable);

void stdlib_arythm_rcmp_register(rb_tree * functable);

void rcmp(int result_type, struct Symbol ** params, struct Symbol * result);


#endif /*  _STDLIB_ARYTHM_OPS_  */
