//      postfix_interp.h
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


#ifndef _POSTFIX_INTERP_H_
#define _POSTFIX_INTERP_H_

#include <stdio.h>

#include "memory.h"
#include "stack.h"
#include "atom.h"
#include "workflow.h"
#include "sym.h"
#include "symtable.h"
#include "sym_rational_ops.h"
#include "function.h"
#include "functable.h"


struct Symbol * process_postfix_workflow(struct WorkFlow * wf, rb_tree * symtab, rb_tree * functab); 


#endif /* _POSTFIX_INTERP_H_ */
