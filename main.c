//      main.c
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


#include "lib/arythm.h"

int main(int argc, char ** argv) {
	
	char * test;
	int i;
	struct WorkFlow * wf;
	rb_tree * symtab;
	struct Symbol * s, * q;
	
	test = malloc(1024);
	
	memstat_init();
//	jmm_init();
	symtab = symtable_init();
	
	
	strcpy(test, "2/3+3/6");
	
	if (inf_check_brackets(test))
		printf("Correct!\n");
	
	wf = inf_transform_to_reverse_postfix(test);

	puts(test);
	for(i = 0; i < wf->count; ++i) {
		printf("%d ", wf->ops[i].id);
	}
	puts("");
	for(i = 0; i < wf->count; ++i) {
		switch (wf->ops[i].id) {
			case SYM_NUM:		printf("%s", (char *)wf->ops[i].data); break;
			case SYM_SYMBOL:	printf("%s", (char *)wf->ops[i].data); break;
			case SYM_OPS_ADD:	printf("+"); break;
			case SYM_OPS_SUB:	printf("-"); break;
			case SYM_OPS_MUL:	printf("*"); break;
			case SYM_OPS_DIV:	printf("/"); break;
			case SYM_OPS_EXP:	printf("^"); break;
			case SYM_FUNC:		printf("%s", (char *)wf->ops[i].data); break;
			default:			break;
		}
		printf(" ");
	}
	puts("");
	
	s = process_postfix_workflow(wf, symtab);
	
	printf("%s = %ld/%ld\n", test, ((struct Rational *)s->data)->num, ((struct Rational *)s->data)->denom);
	
	sym_rational_normalize(s);
	
	printf("%s = %ld/%ld\n", test, ((struct Rational *)s->data)->num, ((struct Rational *)s->data)->denom);
	
	workflow_free(wf);
//	sym_free(s);
	
	
	strcpy(test, "(7*2)/12");
	wf = inf_transform_to_reverse_postfix(test);
	q = process_postfix_workflow(wf, symtab);
	
	printf("%s = %ld/%ld\n", test, ((struct Rational *)q->data)->num, ((struct Rational *)q->data)->denom);
	
	if (sym_rational_is_eq(s, q))
		printf("They are equal\n");
	
	sym_free(q);
	sym_free(s);
	workflow_free(wf);
	free(test);
	
	//printf("\n%lu\n", memstat_getstat()->allocations);
	
	symtable_shutdown(symtab);
	//memstat_debug();
	memstat_shutdown();
	
	return 0;
}
