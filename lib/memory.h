//      memory.h
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


#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "const.h"
#include "error.h"

struct MemItem {
	size_t size;
	unsigned int freed;
	void * ptr;
};

struct MemStat {
	unsigned long allocations;
	unsigned long frees;
	unsigned long count;
	unsigned long mem_a;
	struct MemItem * mem;
};

/* Internal operations */

void memstat_init(void);
void memstat_malloc(void * ptr, size_t size);
void memstat_realloc(void * oldptr, void * newptr, size_t newsize);
void memstat_free(void * ptr);
void memstat_shutdown(void);
void memstat_debug(void);
const struct MemStat * memstat_getstat(void);


/* Basic memory managment functions */

void * jmalloc(size_t size);
void * jrealloc(void * ptr, size_t size);
void jfree(void * ptr);


#endif /* _MEMORY_H_ */
