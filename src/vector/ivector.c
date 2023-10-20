//
// Created by Alex on 17/10/2023.
//

#include <stdlib.h>
#include <stdio.h>

#include "vector.h"

v_status iv_create(ivector** v) {
    *v = malloc(sizeof(ivector));
    if(*v == NULL)
        return V_MEMORY_ALLOCATION_ERROR;

    (*v)->_r_size = V_DEF_R_SIZE;
    (*v)->size = 0;
    (*v)->sort = V_NOT_SORTED;

    (*v)->array = malloc(sizeof (int) * (*v)->_r_size);
    if((*v)->array == NULL)
        return V_MEMORY_ALLOCATION_ERROR;

    return V_SUCCESS;
}

ivector* iv_create_unwrap(void) {
    ivector* v;

    v_status status = iv_create(&v);
    if(status != V_SUCCESS) {
        fprintf(stderr, "Error occur during create on ivector(%p)\n", v);
        exit(EXIT_FAILURE);
    }

    return v;
}

v_status iv_copy(const ivector *src, ivector **dest) {
    v_status status = iv_create(dest);
    if(status != V_SUCCESS)
        return status;

    if(src->_r_size > (*dest)->_r_size) {
        int* n_a = realloc((*dest)->array, sizeof *n_a * src->_r_size);
        if(n_a == NULL)
            return V_MEMORY_ALLOCATION_ERROR;
        (*dest)->array = n_a;
        (*dest)->_r_size = src->_r_size;
    }

    (*dest)->sort = src->sort;
    (*dest)->size = src->size;

    for(size_t i = 0; i < src->size; i++) {
        iv_set((*dest), i, iv_get_unwrap(src, i));
    }

    return V_SUCCESS;
}

ivector *iv_copy_unwrap(const ivector *src) {
    ivector* v;
    if(iv_copy(src, &v) != V_SUCCESS) {
        fprintf(stderr, "Error occur during copy on ivector(%p) to ivector(%p)\n", src, v);
        exit(EXIT_FAILURE);
    }

    return v;
}

void iv_delete(ivector** v) {
    if((*v) != NULL) {
        free((*v)->array);
        free(*v);
    }
}

v_status iv_push(ivector* v, int value) {
    if(v->size >= v->_r_size) {
        int* n_a = realloc(v->array, sizeof *n_a * v->_r_size * 2);
        if(n_a == NULL)
            return V_MEMORY_ALLOCATION_ERROR;
        v->array = n_a;
        v->_r_size *= 2;
    }

    v->array[v->size] = value;
    v->size += 1;

    return V_SUCCESS;
}

v_status iv_pop(ivector *v, int *dest) {
    if(v->size <= 0) {
        dest = NULL;
        return V_EMPTY;
    }

    *dest = *iv_end(v);
    v->size -= 1;
    return V_SUCCESS;
}

v_status iv_insert(ivector *v1, const ivector *v2) {
    for(iv_iterator* it = iv_cbegin(v2); it <= iv_cend(v2); it = iv_next(it)) {
        iv_push(v1, *it);
    }
    return V_SUCCESS;
}

v_status iv_get(const ivector* v, size_t index, int* dest) {
    if(index >= v->size)
        return V_INDEX_OUT_OF_BOUND;

    *dest = v->array[index];
    return V_SUCCESS;
}

int iv_get_unwrap(const ivector* v, size_t index) {
    int value;
    int status = iv_get(v, index, &value);
    if(status != V_SUCCESS) {
        fprintf(stderr, "Error occur during get on ivector(%p) at index %zu\n", v, index);
        exit(EXIT_FAILURE);
    }
    return value;
}

v_status iv_set(ivector* v, size_t index, int value) {
    if(index >= v->size)
        return V_INDEX_OUT_OF_BOUND;

    v->array[index] = value;
    return V_SUCCESS;
}

void iv_print(const ivector *v) {
    printf("ivector([");
    for(int i = 0; i < v->size - 1; i++) {
        printf("%i, ", iv_get_unwrap(v, i));
    }
    printf("%i])\n", iv_get_unwrap(v, v->size - 1));
}

iv_iterator* iv_begin(ivector* v) {
    return &v->array[0];
}

iv_iterator *iv_cbegin(const ivector *v) {
    return &v->array[0];
}

iv_iterator *iv_cend(const ivector *v) {
    return &v->array[v->size - 1];
}

iv_iterator* iv_end(ivector* v) {
    return &v->array[v->size - 1];
}

iv_iterator* iv_next(iv_iterator* it) {
    return ++it;
}

iv_iterator* iv_prev(iv_iterator *it) {
    return --it;
}

void iv_swap(iv_iterator *a, iv_iterator *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

iv_iterator* iv_partition(iv_iterator *begin, iv_iterator *end, int order) {
    iv_iterator* pivot = end;
    iv_iterator* i = iv_prev(begin);

    for(iv_iterator* j = begin; j < end; j = iv_next(j)) {
        if((order == V_ASC && *j <= *pivot) || (order == V_DSC && *j >= *pivot)) {
            i = iv_next(i);
            iv_swap(i, j);
        }
    }

    iv_swap(iv_next(i), end);

    return iv_next(i);
}

v_status iv_sort_recurse(iv_iterator *begin, iv_iterator *end, int order) {
    if(begin < end) {
        iv_iterator* p = iv_partition(begin, end, order);

        v_status status;

        status = iv_sort_recurse(begin, iv_prev(p), order);
        if(status != V_SUCCESS)
            return status;

        status = iv_sort_recurse(iv_next(begin), end, order);
        if(status != V_SUCCESS)
            return status;
    }

    return V_SUCCESS;
}

v_status iv_sort(ivector *v, int order) {
    if(v->sort == order)
        return V_ALREADY_SORT;

    v_status status = iv_sort_recurse(iv_begin(v), iv_end(v), order);
    if(status == V_SUCCESS)
        v->sort = order;

    return status;
}

v_status iv_find(const ivector* v, size_t *dest, int value) {
    int is_asc;
    int iv_set = 0;
    const ivector* cv;
    ivector* iv;
    if(v->sort == V_NOT_SORTED) {
        iv_set = 1;

        v_status status = iv_copy(v, &iv);
        if(status != V_SUCCESS)
            return status;

        status = iv_sort(iv, V_ASC);
        if(status != V_SUCCESS)
            return status;

        is_asc = 1;
        cv = iv;
    }
    else {
        cv = v;
        is_asc = v->sort == V_ASC ? 1 : 0;
    }

    size_t start = 0;
    size_t end = cv->size - 1;
    size_t mid;
    while (start <= end) {
        mid = start + (end - start) / 2;

        if(value == iv_get_unwrap(cv, mid)) {
            *dest = mid;

            if(iv_set)
                iv_delete(&iv);

            return V_SUCCESS;
        }

        if(value < iv_get_unwrap(cv, mid))
            end = mid + (is_asc ? -1 : 1);
        else
            start = mid + (is_asc ? 1 : -1);
    }

    if(iv_set)
        iv_delete(&iv);

    dest = NULL;
    return V_VALUE_NOT_FOUND;
}

int iv_eq(const ivector *a, const ivector *b) {
    if(a->size != b->size)
        return 0;

    for(int i = 0; i < a->size; i++) {
        if (iv_get_unwrap(a, i) != iv_get_unwrap(b, i))
            return 0;
    }

    return 1;
}

v_status iv_remove(ivector *v, size_t index, int *dest) {
    if(index >= v->size)
        return V_INDEX_OUT_OF_BOUND;

    *dest = iv_get_unwrap(v, index);

    for (size_t i = index; i < v->size - 1; ++i) {
        v_status status = iv_set(v, i, iv_get_unwrap(v, i + 1));
        if(status != V_SUCCESS)
            return status;
    }

    v->size -= 1;

    return V_SUCCESS;
}