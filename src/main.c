#include "library/icse_question_generator.h"
#include <arithmetica.h>
#include <stdlib.h>
#include <basic_math_operations.h>
#include <stdio.h>
#include <time.h>

int main()
{
    srand(time(0));

    struct icse_question_generator_context context;
    context.grade = 10;
    context.subject = MATHEMATICS;
    context.difficulty = 1;
    context.type = QUADRATIC_EXAMINE_ROOTS;

    while (1)
    {
        struct icse_question *question = icse_question_generator_generate(&context);
        printf("Q: %s\nA: %s\n", question->question, question->answer);
        icse_question_free(question);
    }
}