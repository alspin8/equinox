//
// Created by Alex on 19/10/2023.
//

#include <stdlib.h>
#include <stdio.h>

#include "list.h"

l_status il_create(ilist **l) {
    (*l) = malloc(sizeof (**l));
    if(*l == NULL)
        return L_MEMORY_ALLOCATION_ERROR;
    (*l)->size = 0;
    (*l)->head = NULL;
    (*l)->tail = NULL;

    return L_SUCCESS;
}

ilist *il_create_unwrap(void) {
    ilist* l;
    l_status status = il_create(&l);
    if(status != L_SUCCESS) {
        fprintf(stderr, "Error occur during create on ilist(%p)\n", l);
        exit(EXIT_FAILURE);
    }

    return l;
}

void il_delete(ilist** l) {
    if((*l) == NULL)
        return;

    if((*l)->size > 0) {
        ilist_node** node = &(*l)->head;
        ilist_node** next;
        do {
            next = &((*node)->next);
            free(*node);
            node = next;
        } while ((*next) != NULL);
    }

    free(*l);
}

l_status il_insert(ilist *l, int value) {
    ilist_node* node = malloc(sizeof (*node));
    if(node == NULL)
        return L_MEMORY_ALLOCATION_ERROR;

    node->value = value;

    if(l->size == 0) {
        l->tail = node;
    } else {
        l->head->prev = node;
    }

    node->next = l->head;
    l->head = node;

    l->size += 1;

    return L_SUCCESS;
}

l_status il_insert_last(ilist *l, int value) {
    ilist_node* node = malloc(sizeof (*node));
    if(node == NULL)
        return L_MEMORY_ALLOCATION_ERROR;

    node->value = value;

    if(l->size == 0) {
        l->head = node;
    } else {
        l->tail->next = node;
    }

    node->prev = l->tail;
    l->tail = node;

    l->size += 1;

    return L_SUCCESS;
}

void il_print(const ilist *l) {
    printf("ilist([");
    for(ilist_node* node = l->head; node != l->tail; node = node->next) {
        printf("%i, ", node->value);
    }
    printf("%i])\n", l->tail->value);
}

l_status il_remove(ilist *l, int* dest) {
    if(l->size == 0)
        return L_EMPTY;

    ilist_node* node = l->head;
    *dest = node->value;

    l->head = l->head->next;
    l->head->prev = NULL;

    l->size -= 1;

    free(node);

    return L_SUCCESS;
}

l_status il_remove_last(ilist* l, int* dest) {
    if(l->size == 0)
        return L_EMPTY;

    ilist_node* node = l->tail;
    *dest = node->value;

    l->tail = l->tail->prev;
    l->tail->next = NULL;

    l->size -= 1;

    free(node);

    return L_SUCCESS;
}

l_status il_get(const ilist *l, size_t index, int *dest) {
    if(index >= l->size)
        return L_INDEX_OUT_OF_BOUND;

    ilist_node* node;
    if(index < l->size / 2) {
        node = l->head;
        for (size_t i = 0; i < index; i++) {
            node = node->next;
        }
    } else {
        node = l->tail;
        for (size_t i = 0; i < (l->size - 1) - index; i++) {
            node = node->prev;
        }
    }

    *dest = node->value;

    return L_SUCCESS;
}

l_status il_set(ilist *l, size_t index, int value) {
    if(index >= l->size)
        return L_INDEX_OUT_OF_BOUND;

    ilist_node* node;
    if(index < l->size / 2) {
        node = l->head;
        for (size_t i = 0; i < index; i++) {
            node = node->next;
        }
    } else {
        node = l->tail;
        for (size_t i = 0; i < (l->size - 1) - index; i++) {
            node = node->prev;
        }
    }

    node->value = value;

    return L_SUCCESS;
}
