#include "array.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

struct array* new_array(size_t size) {
	struct array* array = malloc(sizeof(struct array));

	if (!array) { return NULL; }

	array->size = size;
	array->capacity = size * 2;
	array->array = calloc(array->capacity, sizeof(int));

	if (!array->array) {
		free(array);
		return NULL;
	}

	return array;
}

void free_array(struct array* array) {
	free(array->array);
	free(array);
}

void print_array(const struct array* array, const char separator) {
	for (int i = 0; i < array->size; ++i) {
		printf("%d%c", array->array[i], separator);
	}
}

void resize_array(struct array* array, size_t new_size) {
	array->size = new_size;

	if (new_size <= array->capacity) { return; }

	array->capacity = new_size * 2;
	array->array = realloc(array, sizeof(int) * array->capacity);

	if (!array->array) {
		free(array);
		return;
	}

	return;
}

int sum_array(const struct array* array) {
	int result = 0;

	for (int i = 0; i < array->size; ++i) {
		result += array->array[i];
	}

	return result;
}

struct array* copy_array(const struct array* array) {
	struct array* new_arr = new_array(array->size);

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

int max_array(struct array* array) {
	int max = -pow(10, 12);

	for (int i = 0; i < array->size; ++i) {
		if (array->array[i] > max) { max = array->array[i]; }
	}

	return max;
}

struct array* move_array(struct array* array) {
	struct array* new_array = copy_array(array);
	free_array(array);

	return new_array;
}

void cstr_split(struct array* array, char* input, const char* delim) {
	char* token;
	char* rest = input;

	int i = 0;
	while (i < array->size && (token = strtok_r(rest, delim, &rest))) {
		array->array[i] = strtol(token, NULL, 10);
		++i;
	}
}

int binary_search(const struct array* array, int to_find) {
	int right_index = array->size - 1;
	int left_index = 0;
	int found = -1;

	while (left_index <= right_index) {
		int middle_index = (left_index + right_index) / 2;

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

int rbinary_search(const struct array* array, int to_find) {
	int right_index = array->size - 1;
	int left_index = 0;
	int found = -1;

	while (left_index <= right_index) {
		int middle_index = (left_index + right_index) / 2;

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
bool check_if_array_sorted(const struct array* array) {
	for (int i = 0; i < array->size - 1; ++i) {
		if (array->array[i] > array->array[i + 1]) return false;
	}

	return true;
}





















































