//      workflow.c
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

#include "workflow.h"

struct WorkFlow * workflow_init(void) {
	struct WorkFlow * wf = (struct WorkFlow *) jmalloc(sizeof(struct WorkFlow));
	
	wf->count = 0;
	wf->ops = NULL;
	return wf;
}

struct WorkFlow * workflow_add_atom(struct WorkFlow * wf, struct Atom * atom) {
	
	if (wf->ops == NULL)
		wf->ops = (struct Atom *) jmalloc(++wf->count * sizeof(struct Atom));
	else
		wf->ops = (struct Atom *) jrealloc(wf->ops, ++wf->count * (sizeof(struct Atom)));
	wf->ops[wf->count - 1].id = atom->id;
	wf->ops[wf->count - 1].data = atom->data;
	return wf;
}

int workflow_free(struct WorkFlow * wf) {
	int i;
	if (wf == NULL)
		return -1;
	
	for(i = 0; i < wf->count; ++i)
		if (wf->ops[i].data != NULL)
			jfree(wf->ops[i].data);
		
	jfree(wf->ops);
	jfree(wf);
	return 1;
}
