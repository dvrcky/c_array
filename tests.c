#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include "array.h"

/* helpers */
static Vector* make(int64_t* vals, size_t n) {
    Vector* v = new_vector(n);
    for (size_t i = 0; i < n; ++i) v->array[i] = vals[i];
    return v;
}

/* ------------------------------------------------------------------ */
void test_new_free(void) {
    Vector* v = new_vector(4);
    assert(v != NULL);
    assert(v->size == 4);
    assert(v->capacity >= 4);
    free_vector(v);

    Vector* z = new_vector(0);
    assert(z != NULL);
    free_vector(z);

    printf("PASS test_new_free\n");
}

void test_push_pop_back(void) {
    Vector* v = new_vector(0);
    push_back(v, 10);
    push_back(v, 20);
    push_back(v, 30);
    assert(v->size == 3);
    assert(v->array[0] == 10);
    assert(v->array[1] == 20);
    assert(v->array[2] == 30);

    pop_back(v);
    assert(v->size == 2);
    assert(v->array[1] == 20);

    free_vector(v);
    printf("PASS test_push_pop_back\n");
}

void test_pop(void) {
    int64_t vals[] = {1, 2, 3, 4, 5};
    Vector* v = make(vals, 5);

    pop(v, 2); /* remove 3 */
    assert(v->size == 4);
    assert(v->array[0] == 1);
    assert(v->array[1] == 2);
    assert(v->array[2] == 4);
    assert(v->array[3] == 5);

    pop(v, 0); /* remove 1 */
    assert(v->size == 3);
    assert(v->array[0] == 2);

    pop(v, v->size - 1); /* remove last */
    assert(v->size == 2);

    free_vector(v);
    printf("PASS test_pop\n");
}

void test_sum(void) {
    int64_t vals[] = {1, 2, 3, 4, 5};
    Vector* v = make(vals, 5);
    assert(sum_vector(v) == 15);
    free_vector(v);
    printf("PASS test_sum\n");
}

void test_max_min(void) {
    int64_t vals[] = {3, -1, 7, 2, -5};
    Vector* v = make(vals, 5);
    assert(max_vector(v) == 7);
    assert(min_vector(v) == -5);
    free_vector(v);
    printf("PASS test_max_min\n");
}

void test_avg(void) {
    int64_t vals[] = {1, 2, 3, 4, 5};
    Vector* v = make(vals, 5);
    double a = avg_vector(v);
    assert(a > 2.99 && a < 3.01);
    free_vector(v);

    Vector* empty = new_vector(0);
    assert(avg_vector(empty) == 0.0);
    free_vector(empty);

    printf("PASS test_avg\n");
}

void test_reverse(void) {
    int64_t vals[] = {1, 2, 3, 4, 5};
    Vector* v = make(vals, 5);
    reverse_vector(v);
    assert(v->array[0] == 5);
    assert(v->array[1] == 4);
    assert(v->array[4] == 1);
    free_vector(v);

    /* single element — no crash */
    int64_t one[] = {42};
    Vector* s = make(one, 1);
    reverse_vector(s);
    assert(s->array[0] == 42);
    free_vector(s);

    /* empty — no crash */
    Vector* e = new_vector(0);
    reverse_vector(e);
    free_vector(e);

    printf("PASS test_reverse\n");
}

void test_fill(void) {
    Vector* v = new_vector(5);
    fill_vector(v, 7);
    for (size_t i = 0; i < v->size; ++i) assert(v->array[i] == 7);
    free_vector(v);
    printf("PASS test_fill\n");
}

static int64_t triple(int64_t x) { return x * 3; }

void test_map(void) {
    int64_t vals[] = {1, 2, 3};
    Vector* v = make(vals, 3);

    map_vector(v, triple);

    assert(v->array[0] == 3);
    assert(v->array[1] == 6);
    assert(v->array[2] == 9);
    free_vector(v);
    printf("PASS test_map\n");
}

static bool is_even(int64_t x) { return x % 2 == 0; }

void test_filter(void) {
    int64_t vals[] = {1, 2, 3, 4, 5, 6};
    Vector* v = make(vals, 6);

    filter_vector(v, is_even);

    assert(v->size == 3);
    assert(v->array[0] == 2);
    assert(v->array[1] == 4);
    assert(v->array[2] == 6);
    free_vector(v);
    printf("PASS test_filter\n");
}

void test_slice(void) {
    int64_t vals[] = {10, 20, 30, 40, 50};
    Vector* v = make(vals, 5);

    Vector* s = slice_vector(v, 1, 4); /* [20, 30, 40] */
    assert(s->size == 3);
    assert(s->array[0] == 20);
    assert(s->array[1] == 30);
    assert(s->array[2] == 40);
    free_vector(s);

    /* invalid range */
    Vector* bad = slice_vector(v, 3, 1);
    assert(bad->size == 0);
    free_vector(bad);

    /* out of bounds */
    Vector* oob = slice_vector(v, 2, 10);
    assert(oob->size == 0);
    free_vector(oob);

    free_vector(v);
    printf("PASS test_slice\n");
}

void test_concat(void) {
    int64_t a[] = {1, 2, 3};
    int64_t b[] = {4, 5, 6};
    Vector* va = make(a, 3);
    Vector* vb = make(b, 3);
    Vector* c  = concat_vector(va, vb);

    assert(c->size == 6);
    for (size_t i = 0; i < 6; ++i) assert(c->array[i] == (int64_t)(i + 1));

    free_vector(va); free_vector(vb); free_vector(c);
    printf("PASS test_concat\n");
}

void test_copy_move(void) {
    int64_t vals[] = {5, 10, 15};
    Vector* v  = make(vals, 3);
    Vector* cp = copy_vector(v);

    assert(cp->size == v->size);
    for (size_t i = 0; i < v->size; ++i) assert(cp->array[i] == v->array[i]);

    /* modify copy — original unchanged */
    cp->array[0] = 999;
    assert(v->array[0] == 5);

    free_vector(cp);

    Vector* mv = move_vector(v); /* v is freed inside */
    assert(mv->size == 3);
    assert(mv->array[0] == 5);
    free_vector(mv);

    printf("PASS test_copy_move\n");
}

void test_binary_search(void) {
    int64_t vals[] = {1, 2, 3, 4, 5, 5, 5, 8, 10};
    Vector* v = make(vals, 9);

    /* finds leftmost 5 */
    int64_t idx = binary_search(v, 5);
    assert(idx >= 4 && idx <= 6);
    assert(v->array[idx] == 5);

    /* not found */
    assert(binary_search(v, 99) == -1);

    free_vector(v);
    printf("PASS test_binary_search\n");
}

/* ------------------------------------------------------------------ */
int main(void) {
    test_new_free();
    test_push_pop_back();
    test_pop();
    test_sum();
    test_max_min();
    test_avg();
    test_reverse();
    test_fill();
    test_map();
    test_filter();
    test_slice();
    test_concat();
    test_copy_move();
    test_binary_search();

    printf("\nAll tests passed.\n");
    return 0;
}
