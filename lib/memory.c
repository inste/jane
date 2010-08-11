//      memory.c
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


#include "memory.h"


/* Local heap statistics */


static struct MemStat jmemstat;


/* Internal */

void memstat_init(void) {
	jmemstat.allocations = 0;
	jmemstat.frees = 0;
	jmemstat.count = 0;
	jmemstat.mem_a = PAGE_SIZE / sizeof(struct MemItem);
	jmemstat.mem = (struct MemItem *)malloc(PAGE_SIZE);
}

void memstat_malloc(void * ptr, size_t size) {
	if (jmemstat.count == jmemstat.mem_a) {
		jmemstat.mem = (struct MemItem *) realloc(jmemstat.mem, (jmemstat.mem_a += PAGE_SIZE / sizeof(struct MemItem)) / sizeof(struct MemItem));
	}
	++jmemstat.count;
	++jmemstat.allocations;
	jmemstat.mem[jmemstat.count - 1].size = size;
	jmemstat.mem[jmemstat.count - 1].ptr = ptr;
	jmemstat.mem[jmemstat.count - 1].freed = 0;
}

void memstat_realloc(void * oldptr, void * newptr, size_t newsize) {
	int i;
	
	if (oldptr == NULL)
		memstat_malloc(newptr, newsize);
		
	for(i = 0; i < jmemstat.count; ++i) {
		if (jmemstat.mem[i].ptr == oldptr) {
			jmemstat.mem[i].ptr = newptr;
			jmemstat.mem[i].size = newsize;
			break;
		}
	}
}

void memstat_free(void * ptr) {
	int i;

	++jmemstat.frees;
	for(i = 0; i < jmemstat.count; ++i) {
		if (jmemstat.mem[i].ptr == ptr) {
			++jmemstat.mem[i].freed;
			break;
		}
	}
}

void memstat_shutdown(void) {
	free(jmemstat.mem);
}

const struct MemStat * memstat_getstat(void) {
	return &jmemstat;
}

void memstat_debug(void) {
	int i, b = 0;
	unsigned long size = 0;
	printf("----- Memory debug statistics -----\n");
	printf("Allocations: %lu, frees: %lu\n", jmemstat.allocations, jmemstat.frees);
	printf("Non-freed blocks:\n");
	for(i = 0; i < jmemstat.count; ++i) {
		size += jmemstat.mem[i].size;
		if (jmemstat.mem[i].freed == 0)
			printf("--> %d: ptr: %p, size: %d\n", ++b, jmemstat.mem[i].ptr, (int)jmemstat.mem[i].size);
	}
	if (b == 0)
		puts("All blocks are freed");
	printf("Total size of allocated memory: %lu bytes\n", size);
	printf("-----------------------------------\n");
}

/* Basic memory managment functions */

void * jmalloc(size_t size) {
	void * ptr;
	
	if (size == 0)
		error("memory", "trying to allocate zero-sized memory block");
	if ((ptr = malloc(size)) == NULL)
		error("memory", "error in memory allocation");
	memstat_malloc(ptr, size);
	return ptr;
}

void * jrealloc(void * ptr, size_t size) {
	void * newptr;
	
	if (ptr == NULL) {
		if (size == 0)
			error("memory", "wrong parameters of realloc()");
		else 
			warning("memory", "trying to allocate memory with realloc()");
	}
	if (size == 0)
		warning("memory", "trying to free memory with realloc()");
	if ((newptr = realloc(ptr, size)) == NULL)
		error("memory", "error in memory reallocation");
	memstat_realloc(ptr, newptr, size);
	return newptr;
}

void jfree(void * ptr) {
	if (ptr == NULL)
		error("memory", "trying to free already freed memory");
	memstat_free(ptr);
	free(ptr);
}

