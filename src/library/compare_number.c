#include "icse_question_generator.h"
#include <basic_math_operations.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

bool icse_question_generator_number_equals(char *a, char *b) {
    char *subtraction = calloc(strlen(a) + strlen(b) + 3, sizeof(char));
    subtract(a, b, subtraction);
    bool val = (!strcmp(subtraction, "0")) || (!strcmp(subtraction, "-0"));
    free(subtraction);
    return val;
}