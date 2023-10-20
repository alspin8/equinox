//
// Created by Alex on 17/10/2023.
//

#include <stdlib.h>
#include <stdio.h>

#include "vector.h"

v_status uv_create(uvector** v) {
    *v = malloc(sizeof(uvector));
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

uvector* uv_create_unwrap(void) {
    uvector* v;

    v_status status = uv_create(&v);
    if(status != V_SUCCESS) {
        fprintf(stderr, "Error occur during create on uvector(%p)\n", v);
        exit(EXIT_FAILURE);
    }

    return v;
}

v_status uv_copy(const uvector *src, uvector **dest) {
    v_status status = uv_create(dest);
    if(status != V_SUCCESS)
        return status;

    if(src->_r_size > (*dest)->_r_size) {
        uint* n_a = realloc((*dest)->array, sizeof *n_a * src->_r_size);
        if(n_a == NULL)
            return V_MEMORY_ALLOCATION_ERROR;
        (*dest)->array = n_a;
        (*dest)->_r_size = src->_r_size;
    }

    (*dest)->sort = src->sort;
    (*dest)->size = src->size;

    for(size_t i = 0; i < src->size; i++) {
        uv_set((*dest), i, uv_get_unwrap(src, i));
    }

    return V_SUCCESS;
}

uvector* uv_copy_unwrap(const uvector *src) {
    uvector* v;
    if(uv_copy(src, &v) != V_SUCCESS) {
        fprintf(stderr, "Error occur during copy on uvector(%p) to uvector(%p)\n", src, v);
        exit(EXIT_FAILURE);
    }

    return v;
}

void uv_delete(uvector** v) {
    if((*v) != NULL) {
        free((*v)->array);
        free(*v);
    }
}

v_status uv_push(uvector* v, uint value) {
    if(v->size >= v->_r_size) {
        uint* n_a = realloc(v->array, sizeof *n_a * v->_r_size * 2);
        if(n_a == NULL)
            return V_MEMORY_ALLOCATION_ERROR;
        v->array = n_a;
        v->_r_size *= 2;
    }

    v->array[v->size] = value;
    v->size += 1;

    return V_SUCCESS;
}

v_status uv_pop(uvector *v, uint *dest) {
    if(v->size <= 0) {
        dest = NULL;
        return V_EMPTY;
    }

    *dest = *uv_end(v);
    v->size -= 1;
    return V_SUCCESS;
}

v_status uv_insert(uvector *v1, const uvector *v2) {
    for(uv_iterator* it = uv_cbegin(v2); it <= uv_cend(v2); it = uv_next(it)) {
        uv_push(v1, *it);
    }
    return V_SUCCESS;
}

v_status uv_get(const uvector* v, size_t index, uint* dest) {
    if(index >= v->size)
        return V_INDEX_OUT_OF_BOUND;

    *dest = v->array[index];
    return V_SUCCESS;
}

uint uv_get_unwrap(const uvector* v, size_t index) {
    uint value;
    int status = uv_get(v, index, &value);
    if(status != V_SUCCESS) {
        fprintf(stderr, "Error occur during get on uvector(%p) at index %zu\n", v, index);
        exit(EXIT_FAILURE);
    }
    return value;
}

v_status uv_set(uvector* v, size_t index, uint value) {
    if(index >= v->size)
        return V_INDEX_OUT_OF_BOUND;

    v->array[index] = value;
    return V_SUCCESS;
}

void uv_print(const uvector *v) {
    printf("uvector([");
    for(int i = 0; i < v->size - 1; i++) {
        printf("%i, ", uv_get_unwrap(v, i));
    }
    printf("%i])\n", uv_get_unwrap(v, v->size - 1));
}

uv_iterator* uv_begin(uvector* v) {
    return &v->array[0];
}

uv_iterator *uv_cbegin(const uvector *v) {
    return &v->array[0];
}

uv_iterator *uv_cend(const uvector *v) {
    return &v->array[v->size - 1];
}

uv_iterator* uv_end(uvector* v) {
    return &v->array[v->size - 1];
}

uv_iterator* uv_next(uv_iterator* it) {
    return ++it;
}

uv_iterator* uv_prev(uv_iterator *it) {
    return --it;
}

void uv_swap(uv_iterator *a, uv_iterator *b) {
    uint t = *a;
    *a = *b;
    *b = t;
}

uv_iterator* uv_partition(uv_iterator *begin, uv_iterator *end, int order) {
    uv_iterator* pivot = end;
    uv_iterator* i = uv_prev(begin);

    for(uv_iterator* j = begin; j < end; j = uv_next(j)) {
        if((order == V_ASC && *j <= *pivot) || (order == V_DSC && *j >= *pivot)) {
            i = uv_next(i);
            uv_swap(i, j);
        }
    }

    uv_swap(uv_next(i), end);

    return uv_next(i);
}

v_status uv_sort_recurse(uv_iterator *begin, uv_iterator *end, int order) {
    if(begin < end) {
        uv_iterator* p = uv_partition(begin, end, order);

        v_status status;

        status = uv_sort_recurse(begin, uv_prev(p), order);
        if(status != V_SUCCESS)
            return status;

        status = uv_sort_recurse(uv_next(begin), end, order);
        if(status != V_SUCCESS)
            return status;
    }

    return V_SUCCESS;
}

v_status uv_sort(uvector *v, int order) {
    if(v->sort == order)
        return V_ALREADY_SORT;

    v_status status = uv_sort_recurse(uv_begin(v), uv_end(v), order);
    if(status == V_SUCCESS)
        v->sort = order;

    return status;
}

v_status uv_find(const uvector* v, size_t *dest, uint value) {
    int is_asc;
    int uv_set = 0;
    const uvector* cv;
    uvector* uv;
    if(v->sort == V_NOT_SORTED) {
        uv_set = 1;

        v_status status = uv_copy(v, &uv);
        if(status != V_SUCCESS)
            return status;

        status = uv_sort(uv, V_ASC);
        if(status != V_SUCCESS)
            return status;

        is_asc = 1;
        cv = uv;
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

        if(value == uv_get_unwrap(cv, mid)) {
            *dest = mid;

            if(uv_set)
                uv_delete(&uv);

            return V_SUCCESS;
        }

        if(value < uv_get_unwrap(cv, mid))
            end = mid + (is_asc ? -1 : 1);
        else
            start = mid + (is_asc ? 1 : -1);
    }

    if(uv_set)
        uv_delete(&uv);

    dest = NULL;
    return V_VALUE_NOT_FOUND;
}

int uv_eq(const uvector *a, const uvector *b) {
    if(a->size != b->size)
        return 0;

    for(int i = 0; i < a->size; i++) {
        if (uv_get_unwrap(a, i) != uv_get_unwrap(b, i))
            return 0;
    }

    return 1;
}

v_status uv_remove(uvector *v, size_t index, uint *dest) {
    if(index >= v->size)
        return V_INDEX_OUT_OF_BOUND;

    *dest = uv_get_unwrap(v, index);

    for (size_t i = index; i < v->size - 1; ++i) {
        v_status status = uv_set(v, i, uv_get_unwrap(v, i + 1));
        if(status != V_SUCCESS)
            return status;
    }

    v->size -= 1;

    return V_SUCCESS;
}