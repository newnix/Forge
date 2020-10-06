/*
 * Copyright (c) 2018, Exile Heavy Industries
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the disclaimer
 * below) provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * 
 * * Neither the name of the copyright holder nor the names of its contributors may be used
 *   to endorse or promote products derived from this software without specific
 *   prior written permission.
 * 
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS
 * LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */
/* Simple proof-of concept garbage collection system */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define ELEMENTS 25
#define cfree(x) free(x); x = NULL;

typedef struct resource_list_t {
	struct resource_list_t *prev; // Allows for backwards traversal
	struct resource_list_t *next;
	void *data; // Some dynamically allocated data
} rlist;

static void put_data(void *ptr);
static void pop_data(void);
static void clean_data(void);

/* Should allow access throughout this translation unit */
rlist dyndata = { .prev = NULL, .data = NULL, .next = NULL};
rlist *cursor = &dyndata;

/* Definitely not the best interface for real-world uses */
static void
put_data(void *ptr) {
	rlist *head;
	head = NULL;
	if ((head = calloc((size_t)1, sizeof(rlist))) == NULL) {
		return;
	}
	fprintf(stderr, "[%s]: Created new resource tracker at %p\n", __func__, (void *)head);
	head->prev = cursor;
	head->prev->next = head;
	head->data = ptr;
	head->next = NULL;
	fprintf(stderr, "\thead->prev = %p\n\thead->prev->next = %p\n\t"
			            "head->data = %p (%zu)\n\thead->next %p\n",
									(void *)head->prev, (void *)head->prev->next, (void *)head->data, 
									*(size_t *)(head->data), (void *)head->next);
	/* 
	 * Now that all pointers are updated,
	 * we can update cursor to point at the new struct
	 */
	cursor = head;
	return;
}

static void
pop_data(void) {
	if (cursor->prev == NULL || cursor->next != NULL) {
		/* 
		 * This interface doesn't make sense when not operating
		 * on the tail of the resource list
		 */
		return; // Again, terrible real-world API
	}
	fprintf(stdout, "[%s]: Deleting node at %p\n\t"
			            "cursor->prev = %p\n\t"
									"cursor->next = %p\n\t"
									"cursor->data = %p (%zu)\n",
									__func__, (void *)cursor, (void *)cursor->prev,
									(void *)cursor->next, (void *)cursor->data, *(size_t *)(cursor->data));
	cursor = cursor->prev;
	/* Delete the data and containing struct */
	cfree(cursor->next->data);
	cfree(cursor->next);
	return;
}

static void
clean_data(void) {
	static int_fast8_t i = 0;
	while(cursor->prev != NULL) {
		fprintf(stdout, "[%s]: Cleaning buffer %d at %p (data: %p)\n",
				__func__, i, cursor, cursor->data);
		if (i++ > ELEMENTS) {
			fprintf(stderr, "Something's very wrong, bailing out!\n");
			return;
		}
		pop_data();
	}
	if (cursor->data != NULL) {
		fprintf(stdout, "Cleaning last buffer at %p\n", cursor->data);
		cfree(cursor->data);
	}
	return;
}

int
main(void) {
	size_t ndata;
	size_t *value;
	ndata = ELEMENTS;
	value = NULL;

	/* Create `ndata` items to be tracked and cleaned */
	while(ndata-->0) {
		/* 
		 * We can continue assigning new buffers to `value` since
		 * the pointers are being tracked in the resource list.
		 */
		if ((value = calloc((size_t)1, sizeof(ndata))) == NULL) {
			fprintf(stdout, "Failed allocation, calling cleanup\n");
			clean_data();
			return(0);
		}
		arc4random_buf(value, sizeof(ndata));
		put_data(value);
		/* We can't free `value` here if it's going to be tracked by our resource list */
	}

	fprintf(stdout, "Now trying to run cleanup routine...\n");
	clean_data();
	return(0);
}
