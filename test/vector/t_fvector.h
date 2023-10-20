//
// Created by Alex on 18/10/2023.
//

#include <assert.h>
#include <printf.h>

#include "vector.h"

void t_fv_create() {
    fvector* v;
    v_status status = fv_create(&v);
    assert(status == V_SUCCESS);
    assert(v != NULL);
    assert(v->size == 0);
    assert(v->_r_size == 8);
    assert(v->array != NULL);
    assert(v->sort == V_NOT_SORTED);
    fv_delete(&v);
}

void t_fv_create_unwrap() {
    fvector* v = fv_create_unwrap();
    assert(v != NULL);
    assert(v->size == 0);
    assert(v->_r_size == 8);
    assert(v->array != NULL);
    assert(v->sort == V_NOT_SORTED);
    fv_delete(&v);
}

void t_fv_push() {
    fvector* v = fv_create_unwrap();
    for(int i = 0; i < 100; i++) {
        assert(fv_push(v, i) == V_SUCCESS);
    }
    assert(v->size == 100);
    fv_delete(&v);
}

void t_fv_pop() {
    fvector* v = fv_create_unwrap();
    assert(fv_push(v, 10) == V_SUCCESS);
    assert(fv_push(v, 11) == V_SUCCESS);
    float p;
    assert(fv_pop(v, &p) == V_SUCCESS);
    assert(p == 11);
    assert(fv_pop(v, &p) == V_SUCCESS);
    assert(p == 10);
    assert(fv_pop(v, &p) == V_EMPTY);
    assert(v->size == 0);
    fv_delete(&v);
}

void t_fv_insert() {
    fvector* v1 = fv_create_unwrap();
    fvector* v2 = fv_create_unwrap();
    fvector* v3 = fv_create_unwrap();

    for(int i = 0; i < 20; i++) {
        if(i < 10)
            assert(fv_push(v1, i) == V_SUCCESS);

        if(i >= 10)
            assert(fv_push(v2, i) == V_SUCCESS);

        assert(fv_push(v3, i) == V_SUCCESS);
    }

    assert(fv_insert(v1, v2) == V_SUCCESS);
    assert(fv_eq(v1, v3));

    fv_delete(&v1);
    fv_delete(&v2);
    fv_delete(&v3);
}

void t_fv_get() {
    fvector* v = fv_create_unwrap();
    float _;
    assert(fv_get(v, 0, &_) == V_INDEX_OUT_OF_BOUND);
    assert(fv_push(v, 10) == V_SUCCESS);
    assert(fv_get(v, 0, &_) == V_SUCCESS);
    fv_delete(&v);
}

void t_fv_get_unwrap() {
    fvector* v = fv_create_unwrap();
    float _;
    assert(fv_push(v, 5) == V_SUCCESS);
    assert(fv_get(v, 0, &_) == V_SUCCESS);
    assert(fv_get_unwrap(v, 0) == _);
    fv_delete(&v);
}

void t_fv_set() {
    fvector* v = fv_create_unwrap();
    assert(fv_push(v, 5) == V_SUCCESS);
    assert(fv_get_unwrap(v, 0) == 5);
    assert(fv_set(v, 0, 6) == V_SUCCESS);
    assert(fv_get_unwrap(v, 0) == 6);
    fv_delete(&v);
}

void t_fv_remove() {
    fvector* a = fv_create_unwrap();
    fvector* b = fv_create_unwrap();

    for (int i = 0; i < 10; ++i) {
        assert(fv_push(a, i) == V_SUCCESS);
        if(i != 5)
            assert(fv_push(b, i) == V_SUCCESS);
    }

    float v;
    assert(fv_remove(a, 5, &v) == V_SUCCESS);
    assert(v == 5);
    assert(fv_eq(a, b));

    fv_delete(&a);
    fv_delete(&b);
}

void t_fv_begin() {
    fvector* v = fv_create_unwrap();
    assert(fv_push(v, 5) == V_SUCCESS);
    assert(*fv_begin(v) == fv_get_unwrap(v, 0));
    assert(fv_push(v, 8) == V_SUCCESS);
    assert(*fv_begin(v) == fv_get_unwrap(v, 0));
    fv_delete(&v);
}

void t_fv_end() {
    fvector* v = fv_create_unwrap();
    assert(fv_push(v, 5) == V_SUCCESS);
    assert(*fv_end(v) == *fv_begin(v));
    assert(fv_push(v, 8) == V_SUCCESS);
    assert(*fv_end(v) == fv_get_unwrap(v, 1));
    fv_delete(&v);
}

void t_fv_next() {
    fvector* v = fv_create_unwrap();
    for(int i = 0; i < 10; i++) {
        assert(fv_push(v, i) == V_SUCCESS);
    }

    fv_iterator* it = fv_begin(v);
    for(int i = 0; i < 10; i++) {
        assert(fv_get_unwrap(v, i) == *it);
        it = fv_next(it);
    }

    it = fv_begin(v);
    for(int i = 0; i < 10; i++) {
        *it *= (float )i;
        assert(fv_get_unwrap(v, i) == *it);
        it = fv_next(it);
    }
    fv_delete(&v);
}

void t_fv_prev() {
    fvector* v = fv_create_unwrap();
    for(int i = 0; i < 10; i++) {
        assert(fv_push(v, i) == V_SUCCESS);
    }

    fv_iterator* it = fv_end(v);
    for(int i = 9; i >= 0; i--) {
        assert(fv_get_unwrap(v, i) == *it);
        it = fv_prev(it);
    }

    it = fv_end(v);
    for(int i = 9; i >= 0; i--) {
        *it *= (float )i;
        assert(fv_get_unwrap(v, i) == *it);
        it = fv_prev(it);
    }
    fv_delete(&v);
}

void t_fv_sort() {
    fvector* a_asc = fv_create_unwrap();
    fvector* a_dsc = fv_create_unwrap();
    fvector* b_asc = fv_create_unwrap();
    fvector* b_dsc = fv_create_unwrap();
    for(int i = 0; i < 10; i++) {
        assert(fv_push(a_asc, i) == V_SUCCESS);
        assert(fv_push(b_asc, i) == V_SUCCESS);
        assert(fv_push(a_dsc, 9 - i) == V_SUCCESS);
        assert(fv_push(b_dsc, 9 - i) == V_SUCCESS);
    }

    assert(fv_sort(b_dsc, V_ASC) == V_SUCCESS);
    assert(fv_eq(a_asc, b_dsc));

    assert(fv_sort(b_asc, V_DSC) == V_SUCCESS);
    assert(fv_eq(a_dsc, b_asc));

    assert(fv_sort(b_asc, V_DSC) == V_ALREADY_SORT);

    fv_delete(&a_asc);
    fv_delete(&a_dsc);
    fv_delete(&b_asc);
    fv_delete(&b_dsc);
}

void t_fv_copy() {
    fvector* base = fv_create_unwrap();
    fvector* copy;

    for(int i = 0; i < 10; i++) {
        assert(fv_push(base, i) == V_SUCCESS);
    }

    fv_copy(base, &copy);

    assert(fv_eq(base, copy));

    fv_delete(&base);
    fv_delete(&copy);
}

void t_fv_copy_unwrap() {
    fvector* base = fv_create_unwrap();

    for(int i = 0; i < 10; i++) {
        assert(fv_push(base, i) == V_SUCCESS);
    }

    fvector* copy = fv_copy_unwrap(base);

    assert(fv_eq(base, copy));

    fv_delete(&base);
    fv_delete(&copy);
}

void t_fv_find() {
    fvector* v = fv_create_unwrap();

    for(int i = 0; i < 10; i++) {
        assert(fv_push(v, i) == V_SUCCESS);
    }

    size_t index;
    assert(fv_find(v, &index, 5) == V_SUCCESS);
    assert(index == 5);

    assert(fv_find(v, &index, 10) == V_VALUE_NOT_FOUND);

    fv_delete(&v);
}

void t_fvector() {
    TEST(t_fv_create)
    TEST(t_fv_create_unwrap)
    TEST(t_fv_push)
    TEST(t_fv_pop)
    TEST(t_fv_insert)
    TEST(t_fv_get)
    TEST(t_fv_get_unwrap)
    TEST(t_fv_set)
    TEST(t_fv_remove)
    TEST(t_fv_begin)
    TEST(t_fv_end)
    TEST(t_fv_next)
    TEST(t_fv_prev)
    TEST(t_fv_sort)
    TEST(t_fv_copy)
    TEST(t_fv_copy_unwrap)
    TEST(t_fv_find)
}