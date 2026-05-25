# c_array

Dynamic array library for `int64_t` written in C11.
Supports push/pop, slicing, filtering, mapping, binary search and more.

## Build

```sh
make        # builds libarray.a
make test   # builds and runs tests
make clean  # removes build artifacts
```

## API

### Lifecycle

| Function | Description |
|---|---|
| `Vector* new_vector(size_t size)` | Allocate a new vector with given size. Returns `NULL` on failure. |
| `void free_vector(Vector* v)` | Free vector and its internal buffer. |
| `Vector* copy_vector(const Vector* v)` | Deep copy. Returns `NULL` on failure. |
| `Vector* move_vector(Vector* v)` | Move: copies data into new vector, frees original. |

### Modifying

| Function | Description |
|---|---|
| `bool push_back(Vector* v, int64_t val)` | Append element. Returns `false` on allocation failure. |
| `void pop_back(Vector* v)` | Remove last element. |
| `void pop(Vector* v, size_t index)` | Remove element at index, shift remaining left. |
| `void resize_vector(Vector* v, size_t new_size)` | Resize. Frees vector on allocation failure — check pointer after call. |
| `void fill_vector(Vector* v, int64_t val)` | Set every element to `val`. |
| `void reverse_vector(Vector* v)` | Reverse in place. |
| `void sort_vector(Vector* v)` | Sort ascending in place. |
| `void clear_vector(Vector* v)` | Set size to 0 without freeing memory. |
| `void map_vector(Vector* v, int64_t (*fn)(int64_t))` | Apply `fn` to every element in place. |
| `void filter_vector(Vector* v, bool (*fn)(int64_t))` | Remove elements for which `fn` returns `false`. |

### Producing new vectors

| Function | Description |
|---|---|
| `Vector* slice_vector(const Vector* v, size_t from, size_t to)` | New vector from `[from, to)`. Returns empty vector on invalid range. |
| `Vector* concat_vector(const Vector* a, const Vector* b)` | New vector with all elements of `a` followed by `b`. |

### Querying

| Function | Description |
|---|---|
| `int64_t sum_vector(const Vector* v)` | Sum of all elements. |
| `int64_t max_vector(const Vector* v)` | Maximum element. |
| `int64_t min_vector(const Vector* v)` | Minimum element. |
| `double avg_vector(const Vector* v)` | Average. Returns `0` for empty vector. |
| `int64_t find_vector(const Vector* v, int64_t val)` | Index of first occurrence, or `-1`. |
| `size_t count_vector(const Vector* v, int64_t val)` | Number of occurrences. |
| `int64_t binary_search(const Vector* v, int64_t val)` | Leftmost index in sorted vector, or `-1`. |
| `int64_t rbinary_search(const Vector* v, int64_t val)` | Rightmost index in sorted vector, or `-1`. |
| `bool check_if_vector(const Vector* v)` | Validate vector integrity. |

### Misc

| Function | Description |
|---|---|
| `void print_vector(const Vector* v, char separator)` | Print all elements separated by `separator`. |
| `void cstr_split(Vector* v, char* input, const char* delim)` | Parse delimited string of integers into vector. |

## Example

```c
#include "array.h"
#include <stdio.h>

int64_t double_it(int64_t x) { return x * 2; }
bool is_positive(int64_t x)  { return x > 0; }

int main(void) {
    Vector* v = new_vector(0);

    push_back(v, -1);
    push_back(v, 2);
    push_back(v, 3);

    filter_vector(v, is_positive);  /* [-1] removed */
    map_vector(v, double_it);       /* [4, 6] */

    printf("sum: %ld\n", sum_vector(v));  /* 10 */

    free_vector(v);
    return 0;
}
```
