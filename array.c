#include "array.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

Vector* new_vector(const size_t size) {
	Vector* array = malloc(sizeof(Vector));

	if (!array) { return NULL; }

	array->size = size;
	array->capacity = size * 2;
	array->array = calloc(array->capacity, sizeof(int64_t));

	if (!array->array) {
		free(array);
		return NULL;
	}

	return array;
}

void free_vector(Vector* array) {
	free(array->array);
	free(array);
}

void print_vector(const Vector* array, const char separator) {
	for (int i = 0; i < array->size; ++i) {
		printf("%ld%c", array->array[i], separator);
	}
}

void resize_vector(Vector* array, const size_t new_size) {
	array->size = new_size;

	if (new_size <= array->capacity) { return; }

	array->capacity = new_size * 2;
	array->array = realloc(array, sizeof(int64_t) * array->capacity);

	if (!array->array) {
		free(array);
		return;
	}

	return;
}

int64_t sum_vector(const Vector* array) {
	int64_t result = 0;

	for (int i = 0; i < array->size; ++i) {
		result += array->array[i];
	}

	return result;
}

bool push_back(Vector* array, const int64_t value) {
	++array->size;

	if (array->size >= array->capacity) {
		array->capacity *= 2;
		array->array = realloc(array->array, sizeof(int64_t) *
												 array->capacity);

		if (!array->array) { free(array); return false; }

		array->array[array->size] = value;

		return true;
	}

	array->array[array->size] = value;

	return true;
}

Vector* copy_vector(const Vector* array) {
	Vector* new_arr = new_vector(array->size);

	if (!new_arr->array) {
		free(new_arr);
		return NULL;
	}

	if (!new_arr) {
		return NULL;
	}

	for (int i = 0; i < new_arr->size; ++i) {
		new_arr->array[i] = array->array[i];
	}

	return new_arr;
}

int64_t max_vector(const Vector* array) {
	int64_t max = -pow(10, 12);

	for (int i = 0; i < array->size; ++i) {
		if (array->array[i] > max) { max = array->array[i]; }
	}

	return max;
}

Vector* move_vector(Vector* array) {
	Vector* new_array = copy_vector(array);
	free_vector(array);

	return new_array;
}

void cstr_split(Vector* array, char* input, const char* delim) {
	char* token;
	char* rest = input;

	int i = 0;
	while (i < array->size && (token = strtok_r(rest, delim, &rest))) {
		array->array[i] = strtol(token, NULL, 10);
		++i;
	}
}

int64_t binary_search(const Vector* array, const int64_t to_find) {
	int64_t right_index = array->size - 1;
	size_t left_index = 0;
	int64_t found = -1;

	while (left_index <= right_index) {
		size_t middle_index = (left_index + right_index) / 2;

		if (array->array[middle_index] == to_find) {
			found = middle_index;
			right_index = middle_index - 1;
		}
		if (array->array[middle_index] > to_find) {
			right_index = middle_index - 1;
		}
		if (array->array[middle_index] < to_find) {
			left_index = middle_index + 1;
		}
	}

	return found;
}

int64_t rbinary_search(const Vector* array, int64_t to_find) {
	size_t right_index = array->size - 1;
	size_t left_index = 0;
	int64_t found = -1;

	while (left_index <= right_index) {
		size_t middle_index = (left_index + right_index) / 2;

		if (array->array[middle_index] == to_find) {
			found = middle_index;
			left_index = middle_index + 1;
		}
		if (array->array[middle_index] > to_find) {
			right_index = middle_index - 1;
		}
		if (array->array[middle_index] < to_find) {
			right_index = middle_index + 1;
		}
	}

	return found;
}

/*dontuseitplease*/
bool check_if_vector_sorted(const Vector* array) {
	for (int i = 0; i < array->size - 1; ++i) {
		if (array->array[i] > array->array[i + 1]) return false;
	}

	return true;
}

void pop_back(Vector* array) {
	if (!array->size) return;
	array->array[--array->size] = 0;
}

void pop(Vector* self, const size_t index) {
	if (index < 0 || index >= self->size) { return; }

	if (index == self->size - 1 || self->size == 1) {
		pop_back(self);
		return;
	}

	--self->size;
	memmove(&self->array[index], &self->array[index + 1],
				 (self->size - index - 1) * sizeof(*self->array));

	return;
}





















































