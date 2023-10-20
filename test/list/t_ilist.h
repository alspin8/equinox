//
// Created by Alex on 19/10/2023.
//

#ifndef EQUINOX_T_ILIST_H
#define EQUINOX_T_ILIST_H

#include "list.h"

void t_il_create(void) {
    ilist* l;
    assert(il_create(&l) == L_SUCCESS);
    assert(l->head == NULL);
    assert(l->size == 0);
    il_delete(&l);
}

void t_il_create_unwrap(void) {
    ilist* l = il_create_unwrap();
    assert(l->head == NULL);
    assert(l->size == 0);
    il_delete(&l);
}

void t_il_insert(void) {
    ilist* l = il_create_unwrap();
    assert(il_insert(l, 5) == L_SUCCESS);
    assert(l->size == 1);
    assert(l->head != NULL && l->head == l->tail);
    assert(l->head->prev == NULL && l->head->next == NULL);
    assert(l->head->value == 5);

    assert(il_insert(l, 6) == L_SUCCESS);
    assert(l->size == 2);
    assert(l->head->value == 6);
    assert(l->tail->value == 5);
    assert(l->head->next == l->tail);
    assert(l->tail->prev == l->head);
    assert(l->head->prev == NULL);
    assert(l->tail->next == NULL);

    assert(il_insert(l, 7) == L_SUCCESS);
    assert(l->size == 3);
    assert(l->head->value == 7);
    assert(l->tail->value == 5);
    assert(l->head->next->value == 6);
    assert(l->tail->prev->value == 6);
    assert(l->tail->prev->next == l->tail);
    assert(l->head->next->prev == l->head);
    assert(l->head->next != l->head);
    il_delete(&l);
}

void t_il_insert_last(void) {
    ilist* l = il_create_unwrap();
    assert(il_insert_last(l, 5) == L_SUCCESS);
    assert(l->size == 1);
    assert(l->tail != NULL && l->head == l->tail);
    assert(l->tail->prev == NULL && l->tail->next == NULL);
    assert(l->tail->value == 5);

    assert(il_insert_last(l, 6) == L_SUCCESS);
    assert(l->size == 2);
    assert(l->tail->value == 6);
    assert(l->head->value == 5);
    assert(l->head->next == l->tail);
    assert(l->tail->prev == l->head);
    assert(l->head->prev == NULL);
    assert(l->tail->next == NULL);

    assert(il_insert_last(l, 7) == L_SUCCESS);
    assert(l->size == 3);
    assert(l->tail->value == 7);
    assert(l->head->value == 5);
    assert(l->head->next->value == 6);
    assert(l->tail->prev->value == 6);
    assert(l->tail->prev->next == l->tail);
    assert(l->head->next->prev == l->head);
    assert(l->head->next != l->head);
    il_delete(&l);
}

void t_il_remove(void) {
    ilist* l = il_create_unwrap();

    for (int i = 0; i < 10; ++i) {
        assert(il_insert_last(l, i) == L_SUCCESS);
    }
    assert(l->size == 10);

    int value;
    assert(il_remove(l, &value) == L_SUCCESS);
    assert(value == 0);
    assert(l->size == 9);

    il_delete(&l);
}

void t_il_remove_last(void) {
    ilist* l = il_create_unwrap();

    for (int i = 0; i < 10; ++i) {
        assert(il_insert_last(l, i) == L_SUCCESS);
    }
    assert(l->size == 10);

    int value;
    assert(il_remove_last(l, &value) == L_SUCCESS);
    assert(value == 9);
    assert(l->size == 9);

    il_delete(&l);
}

void t_il_get(void) {
    ilist* l = il_create_unwrap();
    int value;

    assert(il_get(l, 0, &value) == L_INDEX_OUT_OF_BOUND);
    assert(il_get(l, 10, &value) == L_INDEX_OUT_OF_BOUND);

    for (int i = 0; i < 10; ++i) {
        assert(il_insert_last(l, i) == L_SUCCESS);
    }
    assert(l->size == 10);

    assert(il_get(l, 9, &value) == L_SUCCESS);
    assert(value == 9);

    assert(il_get(l, 3, &value) == L_SUCCESS);
    assert(value == 3);

    assert(il_get(l, 7, &value) == L_SUCCESS);
    assert(value == 7);

    assert(il_get(l, 10, &value) == L_INDEX_OUT_OF_BOUND);

    il_delete(&l);
}

void t_il_set(void) {
    ilist* l = il_create_unwrap();
    int value;

    assert(il_set(l, 0, 20) == L_INDEX_OUT_OF_BOUND);
    assert(il_set(l, 10, 20) == L_INDEX_OUT_OF_BOUND);

    for (int i = 0; i < 10; ++i) {
        assert(il_insert_last(l, i) == L_SUCCESS);
    }
    assert(l->size == 10);

    assert(il_set(l, 9, 5) == L_SUCCESS);
    assert(il_get(l, 9, &value) == L_SUCCESS);
    assert(value == 5);

    assert(il_set(l, 3, 35) == L_SUCCESS);
    assert(il_get(l, 3, &value) == L_SUCCESS);
    assert(value == 35);

    assert(il_set(l, 7, -30) == L_SUCCESS);
    assert(il_get(l, 7, &value) == L_SUCCESS);
    assert(value == -30);

    assert(il_set(l, 10, 1500) == L_INDEX_OUT_OF_BOUND);

    il_delete(&l);
}

void t_ilist(void) {
    TEST(t_il_create)
    TEST(t_il_create_unwrap)
    TEST(t_il_insert)
    TEST(t_il_insert_last)
    TEST(t_il_remove)
    TEST(t_il_remove_last)
    TEST(t_il_get)
    TEST(t_il_set)
}

#endif //EQUINOX_T_ILIST_H
