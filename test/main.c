//
// Created by Alex on 19/10/2023.
//

#include <stdlib.h>
#include "test.h"

#include "vector/t_ivector.h"
#include "vector/t_uvector.h"
#include "vector/t_fvector.h"

#include "list/t_ilist.h"

int main(int argc, char** argv) {
    M_TEST(VECTOR, IVECTOR, t_ivector)
    M_TEST(VECTOR, UVECTOR, t_uvector)
    M_TEST(VECTOR, FVECTOR, t_fvector)

    M_TEST(LIST, ILIST, t_ilist)
    return EXIT_SUCCESS;
}