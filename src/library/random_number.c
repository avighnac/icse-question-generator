#include "icse_question_generator.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

// i can see the term now
// i had to open from live share menu
// uhhh

char *icse_question_generator_random_number(size_t number_of_digits)
{
    if (!number_of_digits) {
        char *c = malloc(2);
        c[0] = '0';
        c[1] = 0;
        return c;
    }

    // 1 extra for the null terminator.
    int random = rand() % 2;
    char *number = malloc(number_of_digits + random + 1);
    
    // Adding the null terminator and first null byte.
    *number = 0;
    number[number_of_digits + random] = 0;
    
    size_t ptr = 0;
    if (random)
    {
        number[ptr++] = '-';
    }

    for (size_t i = 0; i < number_of_digits; ++i)
    {
        number[ptr++] = '0' + rand() % 10;
    }
    return number;
}