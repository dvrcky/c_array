#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct Vector {
	size_t size;
	size_t capacity;
	int64_t* array;
} Vector;

/* Function returns NULL if it couldn`t malloc memory */
extern Vector* new_vector(const size_t);

extern void free_vector(Vector*);
extern void pop_back(Vector*);
extern bool push_back(Vector*, const int64_t);

/* Function frees array if it couldn`t reallocate memory
 * So check array before you use it next time.
 */
extern void resize_vector(Vector*, size_t);

extern int64_t sum_vector(const Vector*);
extern int64_t max_vector(const Vector*);

/* Function returns NULL if couldn`t malloc memory for
 * new object of array
 */
extern Vector* copy_vector(const Vector*);

/* Moves old array to new array */
/* It will return NULL if it couldn`t allocate memory for some reason */
extern Vector* move_vector(Vector*);

extern void print_vector(const Vector*, const char);
extern void cstr_split(Vector*, char*, const char*);

/* returns -1 if couldn`t find element */
extern int64_t binary_search(const Vector*, int64_t);
extern int64_t rbinary_search(const Vector*, int64_t);
extern bool check_if_vector(const Vector*);

#endif
