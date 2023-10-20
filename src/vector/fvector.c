//
// Created by Alex on 17/10/2023.
//

#include <stdlib.h>
#include <stdio.h>

#include "vector.h"

v_status fv_create(fvector** v) {
    *v = malloc(sizeof(fvector));
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

fvector* fv_create_unwrap(void) {
    fvector* v;

    v_status status = fv_create(&v);
    if(status != V_SUCCESS) {
        fprintf(stderr, "Error occur during create on fvector(%p)\n", v);
        exit(EXIT_FAILURE);
    }

    return v;
}

v_status fv_copy(const fvector *src, fvector **dest) {
    v_status status = fv_create(dest);
    if(status != V_SUCCESS)
        return status;

    if(src->_r_size > (*dest)->_r_size) {
        float* n_a = realloc((*dest)->array, sizeof *n_a * src->_r_size);
        if(n_a == NULL)
            return V_MEMORY_ALLOCATION_ERROR;
        (*dest)->array = n_a;
        (*dest)->_r_size = src->_r_size;
    }

    (*dest)->sort = src->sort;
    (*dest)->size = src->size;

    for(size_t i = 0; i < src->size; i++) {
        fv_set((*dest), i, fv_get_unwrap(src, i));
    }

    return V_SUCCESS;
}

fvector* fv_copy_unwrap(const fvector *src) {
    fvector* v;
    if(fv_copy(src, &v) != V_SUCCESS) {
        fprintf(stderr, "Error occur during copy on fvector(%p) to fvector(%p)\n", src, v);
        exit(EXIT_FAILURE);
    }

    return v;
}

void fv_delete(fvector** v) {
    if((*v) != NULL) {
        free((*v)->array);
        free(*v);
    }
}

v_status fv_push(fvector* v, float value) {
    if(v->size >= v->_r_size) {
        float* n_a = realloc(v->array, sizeof *n_a * v->_r_size * 2);
        if(n_a == NULL)
            return V_MEMORY_ALLOCATION_ERROR;
        v->array = n_a;
        v->_r_size *= 2;
    }

    v->array[v->size] = value;
    v->size += 1;

    return V_SUCCESS;
}

v_status fv_pop(fvector *v, float *dest) {
    if(v->size <= 0) {
        dest = NULL;
        return V_EMPTY;
    }

    *dest = *fv_end(v);
    v->size -= 1;
    return V_SUCCESS;
}

v_status fv_insert(fvector *v1, const fvector *v2) {
    for(fv_iterator* it = fv_cbegin(v2); it <= fv_cend(v2); it = fv_next(it)) {
        fv_push(v1, *it);
    }
    return V_SUCCESS;
}

v_status fv_get(const fvector* v, size_t index, float* dest) {
    if(index >= v->size)
        return V_INDEX_OUT_OF_BOUND;

    *dest = v->array[index];
    return V_SUCCESS;
}

float fv_get_unwrap(const fvector* v, size_t index) {
    float value;
    int status = fv_get(v, index, &value);
    if(status != V_SUCCESS) {
        fprintf(stderr, "Error occur during get on fvector(%p) at index %zu\n", v, index);
        exit(EXIT_FAILURE);
    }
    return value;
}

v_status fv_set(fvector* v, size_t index, float value) {
    if(index >= v->size)
        return V_INDEX_OUT_OF_BOUND;

    v->array[index] = value;
    return V_SUCCESS;
}

void fv_print(const fvector *v) {
    printf("fvector([");
    for(int i = 0; i < v->size - 1; i++) {
        printf("%f, ", fv_get_unwrap(v, i));
    }
    printf("%f])\n", fv_get_unwrap(v, v->size - 1));
}

fv_iterator* fv_begin(fvector* v) {
    return &v->array[0];
}

fv_iterator *fv_cbegin(const fvector *v) {
    return &v->array[0];
}

fv_iterator *fv_cend(const fvector *v) {
    return &v->array[v->size - 1];
}

fv_iterator* fv_end(fvector* v) {
    return &v->array[v->size - 1];
}

fv_iterator* fv_next(fv_iterator* it) {
    return ++it;
}

fv_iterator* fv_prev(fv_iterator *it) {
    return --it;
}

void fv_swap(fv_iterator *a, fv_iterator *b) {
    float t = *a;
    *a = *b;
    *b = t;
}

fv_iterator* fv_partition(fv_iterator *begin, fv_iterator *end, int order) {
    fv_iterator* pivot = end;
    fv_iterator* i = fv_prev(begin);

    for(fv_iterator* j = begin; j < end; j = fv_next(j)) {
        if((order == V_ASC && *j <= *pivot) || (order == V_DSC && *j >= *pivot)) {
            i = fv_next(i);
            fv_swap(i, j);
        }
    }

    fv_swap(fv_next(i), end);

    return fv_next(i);
}

v_status fv_sort_recurse(fv_iterator *begin, fv_iterator *end, int order) {
    if(begin < end) {
        fv_iterator* p = fv_partition(begin, end, order);

        v_status status;

        status = fv_sort_recurse(begin, fv_prev(p), order);
        if(status != V_SUCCESS)
            return status;

        status = fv_sort_recurse(fv_next(begin), end, order);
        if(status != V_SUCCESS)
            return status;
    }

    return V_SUCCESS;
}

v_status fv_sort(fvector *v, int order) {
    if(v->sort == order)
        return V_ALREADY_SORT;

    v_status status = fv_sort_recurse(fv_begin(v), fv_end(v), order);
    if(status == V_SUCCESS)
        v->sort = order;

    return status;
}

v_status fv_find(const fvector* v, size_t *dest, float value) {
    int is_asc;
    int fv_set = 0;
    const fvector* cv;
    fvector* fv;
    if(v->sort == V_NOT_SORTED) {
        fv_set = 1;

        v_status status = fv_copy(v, &fv);
        if(status != V_SUCCESS)
            return status;

        status = fv_sort(fv, V_ASC);
        if(status != V_SUCCESS)
            return status;

        is_asc = 1;
        cv = fv;
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

        if(value == fv_get_unwrap(cv, mid)) {
            *dest = mid;

            if(fv_set)
                fv_delete(&fv);

            return V_SUCCESS;
        }

        if(value < fv_get_unwrap(cv, mid))
            end = mid + (is_asc ? -1 : 1);
        else
            start = mid + (is_asc ? 1 : -1);
    }

    if(fv_set)
        fv_delete(&fv);

    dest = NULL;
    return V_VALUE_NOT_FOUND;
}

int fv_eq(const fvector *a, const fvector *b) {
    if(a->size != b->size)
        return 0;

    for(int i = 0; i < a->size; i++) {
        if (fv_get_unwrap(a, i) != fv_get_unwrap(b, i))
            return 0;
    }

    return 1;
}

v_status fv_remove(fvector *v, size_t index, float *dest) {
    if(index >= v->size)
        return V_INDEX_OUT_OF_BOUND;

    *dest = fv_get_unwrap(v, index);

    for (size_t i = index; i < v->size - 1; ++i) {
        v_status status = fv_set(v, i, fv_get_unwrap(v, i + 1));
        if(status != V_SUCCESS)
            return status;
    }

    v->size -= 1;

    return V_SUCCESS;
}