#include "icse_question_generator.h"

struct icse_question *icse_question_generator_generate(struct icse_question_generator_context *context)
{
    switch (context->type)
    {
    case QUADRATIC_EXAMINE_ROOTS:
        return icse_question_generator_quadratic_examine_roots(context, ANY);
    // case QUADRATIC_FIND_COEFFICIENTS:
    //     return icse_question_generator_quadratic_find_coefficients(context);
    // case QUADRATIC_SIMPLE_FACTORABLE:
    //     return icse_question_generator_quadratic_simple_factorable(context);
    // case QUADRATIC_TEDIOUS_FACTORABLE:
    //     return icse_question_generator_quadratic_tedious_factorable(context);
    default:
        return 0;
    }
}