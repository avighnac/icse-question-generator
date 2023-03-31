#include "icse_question_generator.h"
#include <stdlib.h>
#include <basic_math_operations.h>
#include <time.h>
#include <string.h>
struct icse_question *icse_question_generator_quadratic_examine_roots(struct icse_question_generator_context *context, enum icse_question_generator_quadratic_examine_roots_root_types root_type)
{
    if (context->grade < 1 || context->grade > 10)
        return 0;

    // For now, we'll return if the grade is not 10.
    if (context->grade != 10)
        return 0;

    if (root_type == ANY)
    {
        // This is the 'more complicated' case where we have to decide the root type.
        // Bias towards real roots with a 1/4 chance of complex roots.
        if (rand() % 4 == 0)
            root_type = COMPLEX;
        else
        {
            // Bias towards rational roots with a 1/3 chance of irrational roots.
            if (rand() % 3 == 0)
                root_type = IRRATIONAL_UNEQUAL;
            else
                // There's no bias for equal or unequal rational roots.
                root_type = (rand() % 2) == 0 ? RATIONAL_UNEQUAL : RATIONAL_EQUAL;
        }
    }

    struct icse_question *question = malloc(sizeof(struct icse_question));
    size_t lens[] = {59, 76, 108, 81, 79};
    char *questions[5] = {"Without solving, find the nature of roots of the equation ",
                          "Find the nature of the roots of the following equation without solving it: ",
                          "What is the nature of the roots of the following equation? Obtain your answer wihout solving the equation: ",
                          "Determine the nature of the roots of the following equation without solving it: ",
                          "Without solving, determine the nature of the roots of the following equation: "};
    // Generate the question.
    int random = rand() % 5;
    question->question = malloc(lens[random] * sizeof(char));
    *question->question = 0;
    strcat(question->question, questions[random]);

    switch (root_type)
    {
    case RATIONAL_UNEQUAL:
        // (r^2)x^2 - (p + q)r x + pq = 0
        char *p = icse_question_generator_random_number(rand() % context->difficulty + 1);
        char *q = icse_question_generator_random_number(rand() % context->difficulty + 1);
        char *r = icse_question_generator_random_number(rand() % context->difficulty + 1);
        while (icse_question_generator_number_equals(r, "0"))
        {
            free(r);
            r = icse_question_generator_random_number(rand() % context->difficulty + 1);
        }

        char *a = calloc(2 * strlen(r) + 3, sizeof(char));
        multiply(r, r, a);

        char *t_1 = calloc(strlen(p) + strlen(q) + 3, sizeof(char));
        add(p, q, t_1);
        char *t_2 = calloc(strlen(t_1) + strlen(r) + 3, sizeof(char));
        multiply(t_1, r, t_2);

        // I should probably make a negate() function in BMO.
        char *b = calloc(strlen(t_2) + 5, sizeof(char));
        multiply(t_2, "-1", b);

        char *c = calloc(strlen(p) + strlen(q) + 3, sizeof(char));
        multiply(p, q, c);

        question->question = realloc(question->question, (strlen(question->question) + strlen(a) + strlen(b) + strlen(c) + 15) * sizeof(char));

        strcat(question->question, a);
        strcat(question->question, "x^2 + ");
        strcat(question->question, b);
        strcat(question->question, "x + ");
        strcat(question->question, c);
        strcat(question->question, " = 0");

        question->answer = malloc(22);
        strcpy(question->answer, "Rational and unequal.");

        // Frees
        free(p);
        free(q);
        free(r);
        free(a);
        free(t_1);
        free(t_2);
        free(b);
        free(c);
        break;
    default:
        free(question);
        return 0;
    }

    return question;
}