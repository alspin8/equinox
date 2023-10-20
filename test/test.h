//
// Created by Alex on 18/10/2023.
//

#ifndef EQUINOX_TEST_H
#define EQUINOX_TEST_H

#define TEST(p, ...)                        \
    printf("> %s...", #p);                  \
    (p)(__VA_ARGS__);                       \
    if(sizeof(#p) + 4 >= 16)                \
        printf("\t\tcomplete\n");           \
    else                                    \
        printf("\t\t\tcomplete\n");

#define M_TEST(suite, test, p, ...)                                                                             \
    printf("\n\n---------------------------- TEST %s FROM %s ----------------------------\n\n", #test, #suite);     \
    (p)(__VA_ARGS__);                                                                                           \
    printf("\n");

#endif //EQUINOX_TEST_H
