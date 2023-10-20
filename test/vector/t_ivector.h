//
// Created by Alex on 18/10/2023.
//

#include <assert.h>
#include <printf.h>

#include "vector.h"

void t_iv_create() {
    ivector* v;
    v_status status = iv_create(&v);
    assert(status == V_SUCCESS);
    assert(v != NULL);
    assert(v->size == 0);
    assert(v->_r_size == 8);
    assert(v->array != NULL);
    assert(v->sort == V_NOT_SORTED);
    iv_delete(&v);
}

void t_iv_create_unwrap() {
    ivector* v = iv_create_unwrap();
    assert(v != NULL);
    assert(v->size == 0);
    assert(v->_r_size == 8);
    assert(v->array != NULL);
    assert(v->sort == V_NOT_SORTED);
    iv_delete(&v);
}

void t_iv_push() {
    ivector* v = iv_create_unwrap();
    for(int i = 0; i < 100; i++) {
        assert(iv_push(v, i) == V_SUCCESS);
    }
    assert(v->size == 100);
    iv_delete(&v);
}

void t_iv_pop() {
    ivector* v = iv_create_unwrap();
    assert(iv_push(v, 10) == V_SUCCESS);
    assert(iv_push(v, 11) == V_SUCCESS);
    int p;
    assert(iv_pop(v, &p) == V_SUCCESS);
    assert(p == 11);
    assert(iv_pop(v, &p) == V_SUCCESS);
    assert(p == 10);
    assert(iv_pop(v, &p) == V_EMPTY);
    assert(v->size == 0);
    iv_delete(&v);
}

void t_iv_insert() {
    ivector* v1 = iv_create_unwrap();
    ivector* v2 = iv_create_unwrap();
    ivector* v3 = iv_create_unwrap();

    for(int i = 0; i < 20; i++) {
        if(i < 10)
            assert(iv_push(v1, i) == V_SUCCESS);

        if(i >= 10)
            assert(iv_push(v2, i) == V_SUCCESS);

        assert(iv_push(v3, i) == V_SUCCESS);
    }

    assert(iv_insert(v1, v2) == V_SUCCESS);
    assert(iv_eq(v1, v3));

    iv_delete(&v1);
    iv_delete(&v2);
    iv_delete(&v3);
}

void t_iv_get() {
    ivector* v = iv_create_unwrap();
    int _;
    assert(iv_get(v, 0, &_) == V_INDEX_OUT_OF_BOUND);
    assert(iv_push(v, 10) == V_SUCCESS);
    assert(iv_get(v, 0, &_) == V_SUCCESS);
    iv_delete(&v);
}

void t_iv_get_unwrap() {
    ivector* v = iv_create_unwrap();
    int _;
    assert(iv_push(v, 5) == V_SUCCESS);
    assert(iv_get(v, 0, &_) == V_SUCCESS);
    assert(iv_get_unwrap(v, 0) == _);
    iv_delete(&v);
}

void t_iv_set() {
    ivector* v = iv_create_unwrap();
    assert(iv_push(v, 5) == V_SUCCESS);
    assert(iv_get_unwrap(v, 0) == 5);
    assert(iv_set(v, 0, 6) == V_SUCCESS);
    assert(iv_get_unwrap(v, 0) == 6);
    iv_delete(&v);
}

void t_iv_remove() {
    ivector* a = iv_create_unwrap();
    ivector* b = iv_create_unwrap();

    for (int i = 0; i < 10; ++i) {
        assert(iv_push(a, i) == V_SUCCESS);
        if(i != 5)
            assert(iv_push(b, i) == V_SUCCESS);
    }

    int v;
    assert(iv_remove(a, 5, &v) == V_SUCCESS);
    assert(v == 5);
    assert(iv_eq(a, b));

    iv_delete(&a);
    iv_delete(&b);
}

void t_iv_begin() {
    ivector* v = iv_create_unwrap();
    assert(iv_push(v, 5) == V_SUCCESS);
    assert(*iv_begin(v) == iv_get_unwrap(v, 0));
    assert(iv_push(v, 8) == V_SUCCESS);
    assert(*iv_begin(v) == iv_get_unwrap(v, 0));
    iv_delete(&v);
}

void t_iv_end() {
    ivector* v = iv_create_unwrap();
    assert(iv_push(v, 5) == V_SUCCESS);
    assert(*iv_end(v) == *iv_begin(v));
    assert(iv_push(v, 8) == V_SUCCESS);
    assert(*iv_end(v) == iv_get_unwrap(v, 1));
    iv_delete(&v);
}

void t_iv_next() {
    ivector* v = iv_create_unwrap();
    for(int i = 0; i < 10; i++) {
        assert(iv_push(v, i) == V_SUCCESS);
    }

    iv_iterator* it = iv_begin(v);
    for(int i = 0; i < 10; i++) {
        assert(iv_get_unwrap(v, i) == *it);
        it = iv_next(it);
    }

    it = iv_begin(v);
    for(int i = 0; i < 10; i++) {
        *it *= i;
        assert(iv_get_unwrap(v, i) == *it);
        it = iv_next(it);
    }
    iv_delete(&v);
}

void t_iv_prev() {
    ivector* v = iv_create_unwrap();
    for(int i = 0; i < 10; i++) {
        assert(iv_push(v, i) == V_SUCCESS);
    }

    iv_iterator* it = iv_end(v);
    for(int i = 9; i >= 0; i--) {
        assert(iv_get_unwrap(v, i) == *it);
        it = iv_prev(it);
    }

    it = iv_end(v);
    for(int i = 9; i >= 0; i--) {
        *it *= i;
        assert(iv_get_unwrap(v, i) == *it);
        it = iv_prev(it);
    }
    iv_delete(&v);
}

void t_iv_sort() {
    ivector* a_asc = iv_create_unwrap();
    ivector* a_dsc = iv_create_unwrap();
    ivector* b_asc = iv_create_unwrap();
    ivector* b_dsc = iv_create_unwrap();
    for(int i = 0; i < 10; i++) {
        assert(iv_push(a_asc, i) == V_SUCCESS);
        assert(iv_push(b_asc, i) == V_SUCCESS);
        assert(iv_push(a_dsc, 9 - i) == V_SUCCESS);
        assert(iv_push(b_dsc, 9 - i) == V_SUCCESS);
    }

    assert(iv_sort(b_dsc, V_ASC) == V_SUCCESS);
    assert(iv_eq(a_asc, b_dsc));

    assert(iv_sort(b_asc, V_DSC) == V_SUCCESS);
    assert(iv_eq(a_dsc, b_asc));

    assert(iv_sort(b_asc, V_DSC) == V_ALREADY_SORT);

    iv_delete(&a_asc);
    iv_delete(&a_dsc);
    iv_delete(&b_asc);
    iv_delete(&b_dsc);
}

void t_iv_copy() {
    ivector* base = iv_create_unwrap();
    ivector* copy;

    for(int i = 0; i < 10; i++) {
        assert(iv_push(base, i) == V_SUCCESS);
    }

    iv_copy(base, &copy);

    assert(iv_eq(base, copy));

    iv_delete(&base);
    iv_delete(&copy);
}

void t_iv_copy_unwrap() {
    ivector* base = iv_create_unwrap();

    for(int i = 0; i < 10; i++) {
        assert(iv_push(base, i) == V_SUCCESS);
    }

    ivector* copy = iv_copy_unwrap(base);

    assert(iv_eq(base, copy));

    iv_delete(&base);
    iv_delete(&copy);
}

void t_iv_find() {
    ivector* v = iv_create_unwrap();

    for(int i = 0; i < 10; i++) {
        assert(iv_push(v, i) == V_SUCCESS);
    }

    size_t index;
    assert(iv_find(v, &index, 5) == V_SUCCESS);
    assert(index == 5);

    assert(iv_find(v, &index, 10) == V_VALUE_NOT_FOUND);

    iv_delete(&v);
}

void t_ivector() {
    TEST(t_iv_create)
    TEST(t_iv_create_unwrap)
    TEST(t_iv_push)
    TEST(t_iv_pop)
    TEST(t_iv_insert)
    TEST(t_iv_get)
    TEST(t_iv_get_unwrap)
    TEST(t_iv_set)
    TEST(t_iv_remove)
    TEST(t_iv_begin)
    TEST(t_iv_end)
    TEST(t_iv_next)
    TEST(t_iv_prev)
    TEST(t_iv_sort)
    TEST(t_iv_copy)
    TEST(t_iv_copy_unwrap)
    TEST(t_iv_find)
}