//
// Created by Alex on 18/10/2023.
//

#ifndef EQUINOX_STRING_H
#define EQUINOX_STRING_H

#include <stddef.h>

typedef int s_status;

typedef char s_iterator;
typedef struct string_t string;
struct string_t {
    size_t _r_size;
    size_t size;
    char* array;
};


/**
 *
 * @param s
 * @return
 */
s_status s_create(string**);


/**
 *
 * @return
 */
string* s_create_unwrap();


/**
 *
 * @param s
 */
void s_delete(string**);


/**
 *
 * @param s
 * @param str
 */
void s_set(string*, char*);


/**
 *
 * @param s
 * @param value
 * @return
 */
s_status s_push(string*, char);


/**
 *
 * @param s
 * @param destination
 * @return
 */
s_status s_pop(string*, char*);


/**
 *
 * @param s
 * @param index
 * @param destination
 * @return
 */
s_status s_remove(string*, size_t, char*);


/**
 *
 * @param s1
 * @param s2
 * @return
 */
s_status s_insert(string*, const string*);


/**
 *
 * @param s
 */
void s_print(const string*);


/**
 *
 * @param s
 * @return
 */
s_iterator* s_begin(string*);


/**
 *
 * @param s
 * @return
 */
s_iterator* s_end(string*);


/**
 *
 * @param it
 * @return
 */
s_iterator* s_next(s_iterator*);

#endif //EQUINOX_STRING_H
