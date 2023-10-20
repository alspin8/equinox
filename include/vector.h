//
// Created by Alex on 17/10/2023.
//

#ifndef EQUINOX_VECTOR_H
#define EQUINOX_VECTOR_H

#include <stddef.h>

#include "core.h"

#define V_DEF_R_SIZE 8

#define V_EMPTY 2
#define V_ALREADY_SORT 1
#define V_SUCCESS 0
#define V_INDEX_OUT_OF_BOUND (-1)
#define V_MEMORY_ALLOCATION_ERROR (-2)
#define V_VALUE_NOT_FOUND (-3)

#define V_NOT_SORTED 0
#define V_ASC 1
#define V_DSC 2

/**
 * @brief Use to return status of many vector function (0 SUCCESS, > 0 WARNING, < 0 ERROR)
 * @see #V_EMPTY
 * @see #V_ALREADY_SORT
 * @see #V_SUCCESS
 * @see #V_INDEX_OUT_OF_BOUND
 * @see #V_MEMORY_ALLOCATION_ERROR
 * @see #V_VALUE_NOT_FOUND
*/
typedef int v_status;


/**
 * @brief Iterator for ivector
 * @see ivector
*/
typedef int iv_iterator;


/**
 * @brief Typedef for ivector_t
 * @see ivector_t
*/
typedef struct ivector_t ivector;


/**
 * @struct ivector_t
 * @brief Struct that represent a vector of int (dynamic array)
 * @var ivector_t::_r_size Contain pre allocated size of the vector
 * @var ivector_t::size Contain the current size of the vector
 * @var ivector_t::size Use as boolean to know if vector is sorted and the order (use for QuickSort find)
 * @var ivector_t::array Contain data
*/
struct ivector_t {
    size_t _r_size;
    size_t size;
    int sort;
    int *array;
};


/**
 * @brief Iterator for uvector
 * @see uvector
*/
typedef uint uv_iterator;


/**
 * @brief Typedef for uvector_t
 * @see uvector_t
*/
typedef struct uvector_t uvector;


/**
 * @struct uvector_t
 * @brief Struct that represent a vector unsigned int (dynamic array)
 * @var uvector_t::_r_size Contain pre allocated size of the vector
 * @var uvector_t::size Contain the current size of the vector
 * @var uvector_t::size Use as boolean to know if vector is sorted and the order (use for QuickSort find)
 * @var uvector_t::array Contain data
*/
struct uvector_t {
    size_t _r_size;
    size_t size;
    int sort;
    uint *array;
};


/**
 * @brief Iterator for fvector
 * @see fvector
*/
typedef float fv_iterator;


/**
 * @brief Typedef for fvector_t
 * @see fvector_t
*/
typedef struct fvector_t fvector;


/**
 * @struct fvector_t
 * @brief Struct that represent a vector of float (dynamic array)
 * @var fvector_t::_r_size Contain pre allocated size of the vector
 * @var fvector_t::size Contain the current size of the vector
 * @var fvector_t::size Use as boolean to know if vector is sorted and the order (use for QuickSort find)
 * @var fvector_t::array Contain data
*/
struct fvector_t {
    size_t _r_size;
    size_t size;
    int sort;
    float *array;
};


/**
 * @brief Create ivector
 * @param [in] v Pointer to an ivector pointer
 * @return v_status Status of the process (V_SUCCESS or V_MEMORY_ALLOCATION_ERROR)
 * @see iv_create_unwrap(void)
 * @see iv_delete(ivector**)
*/
v_status iv_create(ivector**);


/**
 * @brief Create uvector
 * @param [in] v Pointer to an uvector pointer
 * @return v_status Status of the process (V_SUCCESS or V_MEMORY_ALLOCATION_ERROR)
 * @see uv_create_unwrap(void)
 * @see uv_delete(uvector**)
*/
v_status uv_create(uvector**);


/**
 * @brief Create fvector
 * @param [in] v Pointer to an fvector pointer
 * @return v_status Status of the process (V_SUCCESS or V_MEMORY_ALLOCATION_ERROR)
 * @see fv_create_unwrap(void)
 * @see fv_delete(fvector**)
*/
v_status fv_create(fvector**);


/**
 * @brief Create ivector (Not recommended to use)
 * @return A pointer to and ivector
 * @see iv_create(ivector**)
*/
ivector* iv_create_unwrap(void);


/**
 * @brief Create uvector (Not recommended to use)
 * @return A pointer to and uvector
 * @see uv_create(uvector**)
*/
uvector* uv_create_unwrap(void);


/**
 * @brief Create fvector (Not recommended to use)
 * @return A pointer to and fvector
 * @see fv_create(fvector**)
*/
fvector* fv_create_unwrap(void);

/**
 * @brief Copy vector src to dest
 * @param [in] src Pointer to the vector that you want to copy
 * @param [out] dest Pointer to a pointer of your destination
 * @return Status of the process (V_SUCCESS or V_MEMORY_ALLOCATION_ERROR)
 * @see iv_copy_unwrap(const ivector*)
 */
v_status iv_copy(const ivector*, ivector**);


/**
 * @brief Copy vector src to dest
 * @param [in] src Pointer to the vector that you want to copy
 * @param [out] dest Pointer to a pointer of your destination
 * @return Status of the process (V_SUCCESS or V_MEMORY_ALLOCATION_ERROR)
 * @see uv_copy_unwrap(const uvector*)
 */
v_status uv_copy(const uvector*, uvector**);


/**
 * @brief Copy vector src to dest
 * @param [in] src Pointer to the vector that you want to copy
 * @param [out] dest Pointer to a pointer of your destination
 * @return Status of the process (V_SUCCESS or V_MEMORY_ALLOCATION_ERROR)
 * @see uv_copy_unwrap(const uvector*)
 */
v_status fv_copy(const fvector*, fvector**);


/**
 * @brief Return a copy of src (Not recommended to use)
 * @param [in] src Pointer to the vector that you want to copy
 * @return Pointer to the copy of src
 * @see iv_copy(const ivector*, ivector**)
 */
ivector* iv_copy_unwrap(const ivector*);


/**
 * @brief Return a copy of src (Not recommended to use)
 * @param [in] src Pointer to the vector that you want to copy
 * @return Pointer to the copy of src
 * @see uv_copy(const uvector*, uvector**)
 */
uvector* uv_copy_unwrap(const uvector*);


/**
 * @brief Return a copy of src (Not recommended to use)
 * @param [in] src Pointer to the vector that you want to copy
 * @return Pointer to the copy of src
 * @see fv_copy(const fvector*, fvector**)
 */
fvector* fv_copy_unwrap(const fvector*);


/**
 * @brief Delete ivector
 * @param v Address of ivector pointer
 */
void iv_delete(ivector** v);


/**
 * @brief Delete ivector
 * @param v Address of uvector pointer
 */
void uv_delete(uvector** v);


/**
 * @brief Delete ivector
 * @param v Address of fvector pointer
 */
void fv_delete(fvector** v);


/**
 * @brief Print given vector to stdout as vector([0, 1, ...])
 * @param v Vector that you want to print
 */
void iv_print(const ivector*);


/**
 * @brief Print given vector to stdout as vector([0, 1, ...])
 * @param v Vector that you want to print
 */
void uv_print(const uvector*);


/**
 * @brief Print given vector to stdout as vector([0, 1, ...])
 * @param v Vector that you want to print
 */
void fv_print(const fvector*);


/**
 *
 * @param v
 * @param value
 * @return
 */
v_status iv_push(ivector*, int);


/**
 *
 * @param v
 * @param value
 * @return
 */
v_status uv_push(uvector*, uint);


/**
 *
 * @param v
 * @param value
 * @return
 */
v_status fv_push(fvector*, float);


/**
 *
 * @param v
 * @param dest
 * @return
 */
v_status iv_pop(ivector*, int*);


/**
 *
 * @param v
 * @param dest
 * @return
 */
v_status uv_pop(uvector*, uint*);


/**
 *
 * @param v
 * @param dest
 * @return
 */
v_status fv_pop(fvector*, float*);


/**
 *
 * @param v1
 * @param v2
 * @return
 */
v_status iv_insert(ivector*, const ivector*);


/**
 *
 * @param v1
 * @param v2
 * @return
 */
v_status uv_insert(uvector*, const uvector*);


/**
 *
 * @param v1
 * @param v2
 * @return
 */
v_status fv_insert(fvector*, const fvector*);


/**
 *
 * @param v
 * @param index
 * @param value
 * @return
 */
v_status iv_set(ivector*, size_t, int);


/**
 *
 * @param v
 * @param index
 * @param value
 * @return
 */
v_status uv_set(uvector*, size_t, uint);


/**
 *
 * @param v
 * @param index
 * @param value
 * @return
 */
v_status fv_set(fvector*, size_t, float);


/**
 *
 * @param v
 * @param index
 * @param dest
 * @return
 */
v_status iv_remove(ivector*, size_t, int*);


/**
 *
 * @param v
 * @param index
 * @param dest
 * @return
 */
v_status uv_remove(uvector*, size_t, uint*);


/**
 *
 * @param v
 * @param index
 * @param dest
 * @return
 */
v_status fv_remove(fvector*, size_t, float*);


/**
 *
 * @param v
 * @param index
 * @param dest
 * @return
 */
v_status iv_get(const ivector*, size_t, int*);


/**
 *
 * @param v
 * @param index
 * @param dest
 * @return
 */
v_status uv_get(const uvector*, size_t, uint*);


/**
 *
 * @param v
 * @param index
 * @param dest
 * @return
 */
v_status fv_get(const fvector*, size_t, float*);


/**
 *
 * @param v
 * @param index
 * @return
 */
int iv_get_unwrap(const ivector*, size_t);


/**
 *
 * @param v
 * @param index
 * @return
 */
uint uv_get_unwrap(const uvector*, size_t);


/**
 *
 * @param v
 * @param index
 * @return
 */
float fv_get_unwrap(const fvector*, size_t);


/**
 *
 * @param v
 * @param order
 * @return
 */
v_status iv_sort(ivector*, int);


/**
 *
 * @param v
 * @param order
 * @return
 */
v_status uv_sort(uvector*, int);


/**
 *
 * @param v
 * @param order
 * @return
 */
v_status fv_sort(fvector*, int);


/**
 *
 * @param v
 * @param dest
 * @param value
 * @return
 */
v_status iv_find(const ivector*, size_t*, int);


/**
 *
 * @param v
 * @param dest
 * @param value
 * @return
 */
v_status uv_find(const uvector*, size_t*, uint);


/**
 *
 * @param v
 * @param dest
 * @param value
 * @return
 */
v_status fv_find(const fvector*, size_t*, float);


/**
 *
 * @param a
 * @param b
 * @return
 */
int iv_eq(const ivector*, const ivector*);


/**
 *
 * @param a
 * @param b
 * @return
 */
int uv_eq(const uvector*, const uvector*);


/**
 *
 * @param a
 * @param b
 * @return
 */
int fv_eq(const fvector*, const fvector*);


/**
 *
 * @param v
 * @return
 */
iv_iterator* iv_begin(ivector*);


/**
 *
 * @param v
 * @return
 */
uv_iterator* uv_begin(uvector*);


/**
 *
 * @param v
 * @return
 */
fv_iterator* fv_begin(fvector*);


/**
 *
 * @param v
 * @return
 */
iv_iterator* iv_end(ivector*);


/**
 *
 * @param v
 * @return
 */
uv_iterator* uv_end(uvector*);


/**
 *
 * @param v
 * @return
 */
fv_iterator* fv_end(fvector*);


/**
 *
 * @param v
 * @return
 */
iv_iterator* iv_cbegin(const ivector*);


/**
 *
 * @param v
 * @return
 */
uv_iterator* uv_cbegin(const uvector*);


/**
 *
 * @param v
 * @return
 */
fv_iterator* fv_cbegin(const fvector*);


/**
 *
 * @param v
 * @return
 */
iv_iterator* iv_cend(const ivector*);


/**
 *
 * @param v
 * @return
 */
uv_iterator* uv_cend(const uvector*);


/**
 *
 * @param v
 * @return
 */
fv_iterator* fv_cend(const fvector*);


/**
 *
 * @param it
 * @return
 */
iv_iterator* iv_next(iv_iterator*);

/**
 *
 * @param it
 * @return
 */
uv_iterator* uv_next(uv_iterator*);


/**
 *
 * @param it
 * @return
 */
fv_iterator* fv_next(fv_iterator*);


/**
 *
 * @param it
 * @return
 */
iv_iterator* iv_prev(iv_iterator*);


/**
 *
 * @param it
 * @return
 */
uv_iterator* uv_prev(uv_iterator*);


/**
 *
 * @param it
 * @return
 */
fv_iterator* fv_prev(fv_iterator*);

#endif //EQUINOX_VECTOR_H