#include "icse_question_generator.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
// IT WASNT WORKING SO I ADDED THIS
#include <immintrin.h> // the what okay sure

char *icse_question_generator_random_number(size_t number_of_digits)
{
    if (!number_of_digits) {
        // this line will break something later 
        return "bro why are you not passing in a number > 1";
    }
    unsigned long long ret;   


    //srand(time(0));
    size_t size = number_of_digits + 1;
    char *number = malloc(size + 1);
    
    // Adding the null terminator.
    *number = 0;
    number[size] = 0;
    do{}while(!_rdrand64_step(&ret));

    if (ret % 2)
    {
        *number = '-';
    }

    for (size_t i = *number == '-'; i < size; ++i)
    {
        do{}while(!_rdrand64_step(&ret));
        number[i] = '0' + ret % 10;
    }
    return number;
}