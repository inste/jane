//      atom.h
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

#ifndef _ATOM_H_
#define _ATOM_H_

#include <stdio.h>
#include <stdlib.h>

#include "const.h"
#include "memory.h"

struct Atom {
	unsigned char id; // SYM_* code of content
	void * data;
};

struct Atom * atom_alloc(unsigned int code, void * data);
int atom_free(struct Atom * atom);

#endif /* _ATOM_H_ */
