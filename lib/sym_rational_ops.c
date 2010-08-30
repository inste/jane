//      sym_rational_ops.c
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


#include "sym_rational_ops.h"

struct Symbol * sym_rational_alloc(char * label, long int num, long int denom) {
	struct Rational i;
	i.num = num;
	i.denom = denom;
	return sym_alloc_deep(SYM_TYPE_RATIONAL, 0, label, &i, sizeof(struct Rational)); 
}

struct Symbol * sym_rational_tmp_alloc(long int num, long int denom) {
	return sym_rational_alloc(NULL, num, denom);
}

struct Symbol * sym_rational_add(struct Symbol * sym1, struct Symbol * sym2) {
	struct Rational * i = (struct Rational *) jmalloc(sizeof(struct Rational));

	i->num = ((struct Rational *)sym1->data)->num * ((struct Rational *)sym2->data)->denom + 
			 ((struct Rational *)sym2->data)->num * ((struct Rational *)sym1->data)->denom;
	i->denom = ((struct Rational *)sym1->data)->denom * ((struct Rational *)sym2->data)->denom;
	return sym_rational_normalize(sym_alloc_shallow(SYM_TYPE_RATIONAL, 0, NULL, i));
}

struct Symbol * sym_rational_sub(struct Symbol * sym1, struct Symbol * sym2) {
	struct Rational * i = (struct Rational *) jmalloc(sizeof(struct Rational));

	i->num = ((struct Rational *)sym1->data)->num * ((struct Rational *)sym2->data)->denom - 
			 ((struct Rational *)sym2->data)->num * ((struct Rational *)sym1->data)->denom;
	i->denom = ((struct Rational *)sym1->data)->denom * ((struct Rational *)sym2->data)->denom;
	return sym_rational_normalize(sym_alloc_shallow(SYM_TYPE_RATIONAL, 0, NULL, i));
}

struct Symbol * sym_rational_mul(struct Symbol * sym1, struct Symbol * sym2) {
	struct Rational * i = (struct Rational*) jmalloc(sizeof(struct Rational));

	i->num = ((struct Rational *)sym1->data)->num * ((struct Rational *)sym2->data)->num; 
	i->denom = ((struct Rational *)sym1->data)->denom * ((struct Rational *)sym2->data)->denom;
	return sym_rational_normalize(sym_alloc_shallow(SYM_TYPE_RATIONAL, 0, NULL, i));
}

struct Symbol * sym_rational_div(struct Symbol * sym1, struct Symbol * sym2) {
	struct Rational * i = (struct Rational *) jmalloc(sizeof(struct Rational));

	i->num = ((struct Rational *)sym1->data)->num * ((struct Rational *)sym2->data)->denom;
	i->denom = ((struct Rational *)sym1->data)->denom * ((struct Rational *)sym2->data)->num;
	return sym_rational_normalize(sym_alloc_shallow(SYM_TYPE_RATIONAL, 0, NULL, i));
}

struct Symbol * sym_rational_duplicate(struct Symbol * src) {
	
	return sym_alloc_deep(src->type, src->is_constant, src->label, src->data, sizeof(struct Rational));
}

struct Symbol * sym_rational_normalize(struct Symbol * src) {
	int i = ((struct Rational *)src->data)->denom;
	
	for(; i > 1; --i)
		if (((((struct Rational *)src->data)->denom % i) == 0) && ((((struct Rational *)src->data)->num % i) == 0)) {
			((struct Rational *)src->data)->denom /= i;
			((struct Rational *)src->data)->num /= i;
		}
	
	return src;
}

int sym_rational_is_eq(struct Symbol * sym1, struct Symbol * sym2) {	
	sym_rational_normalize(sym1);
	sym_rational_normalize(sym2);
	
	return ( 
			 (((struct Rational *)sym1->data)->num == (((struct Rational *)sym2->data)->num)) &&
			 (((struct Rational *)sym1->data)->denom == (((struct Rational *)sym2->data)->denom))
		   ) ? 1 : 0;
}

void sym_rational_free(struct Symbol * isym) {
	sym_free(isym);
}
