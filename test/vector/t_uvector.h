//
// Created by Alex on 18/10/2023.
//

#include <assert.h>
#include <printf.h>

#include "vector.h"

void t_uv_create() {
    uvector* v;
    v_status status = uv_create(&v);
    assert(status == V_SUCCESS);
    assert(v != NULL);
    assert(v->size == 0);
    assert(v->_r_size == 8);
    assert(v->array != NULL);
    assert(v->sort == V_NOT_SORTED);
    uv_delete(&v);
}

void t_uv_create_unwrap() {
    uvector* v = uv_create_unwrap();
    assert(v != NULL);
    assert(v->size == 0);
    assert(v->_r_size == 8);
    assert(v->array != NULL);
    assert(v->sort == V_NOT_SORTED);
    uv_delete(&v);
}

void t_uv_push() {
    uvector* v = uv_create_unwrap();
    for(int i = 0; i < 100; i++) {
        assert(uv_push(v, i) == V_SUCCESS);
    }
    assert(v->size == 100);
    uv_delete(&v);
}

void t_uv_pop() {
    uvector* v = uv_create_unwrap();
    assert(uv_push(v, 10) == V_SUCCESS);
    assert(uv_push(v, 11) == V_SUCCESS);
    uint p;
    assert(uv_pop(v, &p) == V_SUCCESS);
    assert(p == 11);
    assert(uv_pop(v, &p) == V_SUCCESS);
    assert(p == 10);
    assert(uv_pop(v, &p) == V_EMPTY);
    assert(v->size == 0);
    uv_delete(&v);
}

void t_uv_insert() {
    uvector* v1 = uv_create_unwrap();
    uvector* v2 = uv_create_unwrap();
    uvector* v3 = uv_create_unwrap();

    for(int i = 0; i < 20; i++) {
        if(i < 10)
            assert(uv_push(v1, i) == V_SUCCESS);

        if(i >= 10)
            assert(uv_push(v2, i) == V_SUCCESS);

        assert(uv_push(v3, i) == V_SUCCESS);
    }

    assert(uv_insert(v1, v2) == V_SUCCESS);
    assert(uv_eq(v1, v3));

    uv_delete(&v1);
    uv_delete(&v2);
    uv_delete(&v3);
}

void t_uv_get() {
    uvector* v = uv_create_unwrap();
    uint _;
    assert(uv_get(v, 0, &_) == V_INDEX_OUT_OF_BOUND);
    assert(uv_push(v, 10) == V_SUCCESS);
    assert(uv_get(v, 0, &_) == V_SUCCESS);
    uv_delete(&v);
}

void t_uv_get_unwrap() {
    uvector* v = uv_create_unwrap();
    uint _;
    assert(uv_push(v, 5) == V_SUCCESS);
    assert(uv_get(v, 0, &_) == V_SUCCESS);
    assert(uv_get_unwrap(v, 0) == _);
    uv_delete(&v);
}

void t_uv_set() {
    uvector* v = uv_create_unwrap();
    assert(uv_push(v, 5) == V_SUCCESS);
    assert(uv_get_unwrap(v, 0) == 5);
    assert(uv_set(v, 0, 6) == V_SUCCESS);
    assert(uv_get_unwrap(v, 0) == 6);
    uv_delete(&v);
}

void t_uv_remove() {
    uvector* a = uv_create_unwrap();
    uvector* b = uv_create_unwrap();

    for (int i = 0; i < 10; ++i) {
        assert(uv_push(a, i) == V_SUCCESS);
        if(i != 5)
            assert(uv_push(b, i) == V_SUCCESS);
    }

    uint v;
    assert(uv_remove(a, 5, &v) == V_SUCCESS);
    assert(v == 5);
    assert(uv_eq(a, b));

    uv_delete(&a);
    uv_delete(&b);
}

void t_uv_begin() {
    uvector* v = uv_create_unwrap();
    assert(uv_push(v, 5) == V_SUCCESS);
    assert(*uv_begin(v) == uv_get_unwrap(v, 0));
    assert(uv_push(v, 8) == V_SUCCESS);
    assert(*uv_begin(v) == uv_get_unwrap(v, 0));
    uv_delete(&v);
}

void t_uv_end() {
    uvector* v = uv_create_unwrap();
    assert(uv_push(v, 5) == V_SUCCESS);
    assert(*uv_end(v) == *uv_begin(v));
    assert(uv_push(v, 8) == V_SUCCESS);
    assert(*uv_end(v) == uv_get_unwrap(v, 1));
    uv_delete(&v);
}

void t_uv_next() {
    uvector* v = uv_create_unwrap();
    for(int i = 0; i < 10; i++) {
        assert(uv_push(v, i) == V_SUCCESS);
    }

    uv_iterator* it = uv_begin(v);
    for(int i = 0; i < 10; i++) {
        assert(uv_get_unwrap(v, i) == *it);
        it = uv_next(it);
    }

    it = uv_begin(v);
    for(int i = 0; i < 10; i++) {
        *it *= i;
        assert(uv_get_unwrap(v, i) == *it);
        it = uv_next(it);
    }
    uv_delete(&v);
}

void t_uv_prev() {
    uvector* v = uv_create_unwrap();
    for(int i = 0; i < 10; i++) {
        assert(uv_push(v, i) == V_SUCCESS);
    }

    uv_iterator* it = uv_end(v);
    for(int i = 9; i >= 0; i--) {
        assert(uv_get_unwrap(v, i) == *it);
        it = uv_prev(it);
    }

    it = uv_end(v);
    for(int i = 9; i >= 0; i--) {
        *it *= i;
        assert(uv_get_unwrap(v, i) == *it);
        it = uv_prev(it);
    }
    uv_delete(&v);
}

void t_uv_sort() {
    uvector* a_asc = uv_create_unwrap();
    uvector* a_dsc = uv_create_unwrap();
    uvector* b_asc = uv_create_unwrap();
    uvector* b_dsc = uv_create_unwrap();
    for(int i = 0; i < 10; i++) {
        assert(uv_push(a_asc, i) == V_SUCCESS);
        assert(uv_push(b_asc, i) == V_SUCCESS);
        assert(uv_push(a_dsc, 9 - i) == V_SUCCESS);
        assert(uv_push(b_dsc, 9 - i) == V_SUCCESS);
    }

    assert(uv_sort(b_dsc, V_ASC) == V_SUCCESS);
    assert(uv_eq(a_asc, b_dsc));

    assert(uv_sort(b_asc, V_DSC) == V_SUCCESS);
    assert(uv_eq(a_dsc, b_asc));

    assert(uv_sort(b_asc, V_DSC) == V_ALREADY_SORT);

    uv_delete(&a_asc);
    uv_delete(&a_dsc);
    uv_delete(&b_asc);
    uv_delete(&b_dsc);
}

void t_uv_copy() {
    uvector* base = uv_create_unwrap();
    uvector* copy;

    for(int i = 0; i < 10; i++) {
        assert(uv_push(base, i) == V_SUCCESS);
    }

    uv_copy(base, &copy);

    assert(uv_eq(base, copy));

    uv_delete(&base);
    uv_delete(&copy);
}

void t_uv_copy_unwrap() {
    uvector* base = uv_create_unwrap();

    for(int i = 0; i < 10; i++) {
        assert(uv_push(base, i) == V_SUCCESS);
    }

    uvector* copy = uv_copy_unwrap(base);

    assert(uv_eq(base, copy));

    uv_delete(&base);
    uv_delete(&copy);
}

void t_uv_find() {
    uvector* v = uv_create_unwrap();

    for(int i = 0; i < 10; i++) {
        assert(uv_push(v, i) == V_SUCCESS);
    }

    size_t index;
    assert(uv_find(v, &index, 5) == V_SUCCESS);
    assert(index == 5);

    assert(uv_find(v, &index, 10) == V_VALUE_NOT_FOUND);

    uv_delete(&v);
}

void t_uvector() {
    TEST(t_uv_create)
    TEST(t_uv_create_unwrap)
    TEST(t_uv_push)
    TEST(t_uv_pop)
    TEST(t_uv_insert)
    TEST(t_uv_get)
    TEST(t_uv_get_unwrap)
    TEST(t_uv_set)
    TEST(t_uv_remove)
    TEST(t_uv_begin)
    TEST(t_uv_end)
    TEST(t_uv_next)
    TEST(t_uv_prev)
    TEST(t_uv_sort)
    TEST(t_uv_copy)
    TEST(t_uv_copy_unwrap)
    TEST(t_uv_find)
}