//      sym_rational_ops.h
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


#ifndef _SYM_RATIONAL_OPS_H_
#define _SYM_RATIONAL_OPS_H_

#include <stdio.h>

#include "sym.h"

struct Rational {
	long int num;
	long int denom;
};

struct Symbol * sym_rational_alloc(char * label, long int num, long int denom);
struct Symbol * sym_rational_tmp_alloc(long int num, long int denom);
struct Symbol * sym_rational_add(struct Symbol * sym1, struct Symbol * sym2);
struct Symbol * sym_rational_sub(struct Symbol * sym1, struct Symbol * sym2);
struct Symbol * sym_rational_mul(struct Symbol * sym1, struct Symbol * sym2);
struct Symbol * sym_rational_div(struct Symbol * sym1, struct Symbol * sym2);

struct Symbol * sym_rational_duplicate(struct Symbol * src);
struct Symbol *	sym_rational_normalize(struct Symbol * src);

int sym_rational_is_eq(struct Symbol * sym1, struct Symbol * sym2);
void sym_rational_free(struct Symbol * isym);

#endif /* _SYM_RATIONAL_OPS_H_ */
