#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <stdbool.h>

struct array {
	size_t size;
	size_t capacity;
	int* array;
};

/* Function returns NULL if it couldn`t malloc memory */
extern struct array* new_array(const size_t size);

extern void free_array(struct array* array);

/* Function frees array if it couldn`t reallocate memory
 * So check array before you use it next time.
 */
extern void resize_array(struct array*, size_t new_size);

extern int sum_array(const struct array* array);

/* Function returns NULL if couldn`t malloc memory for
 * new object of array
 */
extern struct array* copy_array(const struct array* array);

/* Moves old array to new array */
/* It will return NULL if it couldn`t allocate memory for some reason */
extern struct array* move_array(struct array* array);

extern void print_array(const struct array*, const char separator);
extern void cstr_split(struct array*, char*, const char*);

/* returns -1 if couldn`t find element */
extern int binary_search(const struct array*, int);
extern bool check_if_array_sorted(const struct array*);

#endif
