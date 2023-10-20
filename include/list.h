//
// Created by Alex on 19/10/2023.
//

#ifndef EQUINOX_LIST_H
#define EQUINOX_LIST_H

#include "stddef.h"

#include "core.h"

#define L_EMPTY 2
#define L_SUCCESS 0
#define L_INDEX_OUT_OF_BOUND (-1)
#define L_MEMORY_ALLOCATION_ERROR (-2)

typedef int l_status;

typedef struct ilist_node_t ilist_node;
struct ilist_node_t {
    int value;
    ilist_node* prev;
    ilist_node* next;
};

typedef struct ilist_t ilist;
struct ilist_t {
    size_t size;
    ilist_node* head;
    ilist_node* tail;
};

typedef struct ulist_node_t ulist_node;
struct ulist_node_t {
    uint value;
    ulist_node* prev;
    ulist_node* next;
};

typedef struct ulist_t ulist;
struct ulist_t {
    size_t size;
    ulist_node* head;
    ulist_node* tail;
};

typedef struct flist_node_t flist_node;
struct flist_node_t {
    float value;
    flist_node* prev;
    flist_node* next;
};

typedef struct flist_t flist;
struct flist_t {
    size_t size;
    flist_node* head;
    flist_node* tail;
};


/**
 *
 * @param l
 * @return
 */
l_status il_create(ilist**);


/**
 *
 * @param l
 * @return
 */
l_status ul_create(ulist**);

/**
 *
 * @param l
 * @return
 */
l_status fl_create(flist**);


/**
 *
 * @return
 */
ilist* il_create_unwrap(void);


/**
 *
 * @return
 */
ulist* ul_create_unwrap(void);


/**
 *
 * @return
 */
flist* fl_create_unwrap(void);


/**
 *
 * @param l
 * @param value
 * @return
 */
l_status il_insert(ilist*, int);


/**
 *
 * @param l
 * @param value
 * @return
 */
l_status ul_insert(ulist*, uint);


/**
 *
 * @param l
 * @param value
 * @return
 */
l_status fl_insert(flist*, float);


/**
 *
 * @param l
 * @param value
 * @return
 */
l_status il_insert_last(ilist*, int);


/**
 *
 * @param l
 * @param value
 * @return
 */
l_status ul_insert_last(ulist*, uint);


/**
 *
 * @param l
 * @param value
 * @return
 */
l_status fl_insert_last(flist*, float);


/**
 *
 * @param l
 * @param dest
 * @return
 */
l_status il_remove(ilist*, int*);


/**
 *
 * @param l
 * @param dest
 * @return
 */
l_status ul_remove(ulist*, uint*);


/**
 *
 * @param l
 * @param dest
 * @return
 */
l_status fl_remove(flist*, float*);


/**
 *
 * @param l
 * @param dest
 * @return
 */
l_status il_remove_last(ilist*, int*);


/**
 *
 * @param l
 * @param dest
 * @return
 */
l_status ul_remove_last(ulist*, uint*);


/**
 *
 * @param l
 * @param dest
 * @return
 */
l_status fl_remove_last(flist*, float*);


/**
 *
 * @param l
 * @param index
 * @param value
 * @return
 */
l_status il_get(const ilist*, size_t, int*);


/**
 *
 * @param l
 * @param index
 * @param value
 * @return
 */
l_status ul_get(const ulist*, size_t, uint*);


/**
 *
 * @param l
 * @param index
 * @param value
 * @return
 */
l_status fl_get(const flist*, size_t, float*);


/**
 *
 * @param l
 * @param index
 * @param value
 * @return
 */
l_status il_set(ilist*, size_t, int);


/**
 *
 * @param l
 * @param index
 * @param value
 * @return
 */
l_status ul_set(ulist*, size_t, uint);


/**
 *
 * @param l
 * @param index
 * @param value
 * @return
 */
l_status fl_set(flist*, size_t, float);


/**
 *
 * @param l
 */
void il_print(const ilist*);


/**
 *
 * @param l
 */
void ul_print(const ulist*);


/**
 *
 * @param l
 */
void fl_print(const flist*);


/**
 *
 * @param l
 */
void il_delete(ilist**);


/**
 *
 * @param l
 */
void ul_delete(ulist**);


/**
 *
 * @param l
 */
void fl_delete(flist**);

#endif //EQUINOX_LIST_H
