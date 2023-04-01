#include "icse_question_generator.h"
#include <stdlib.h>
#include <basic_math_operations.h>
#include <time.h>
#include <string.h>

// If a new root type is added in the future, please update this!
#define N_ROOT_TYPES 4

struct icse_question *icse_question_generator_quadratic_examine_roots(struct icse_question_generator_context *context, enum icse_question_generator_quadratic_examine_roots_root_types root_type)
{
    if (context->grade < 1 || context->grade > 10)
        return 0;

    // For now, we'll return if the grade is not 10.
    if (context->grade != 10)
        return 0;

    if (root_type == ANY)
    {
        root_type = rand() % N_ROOT_TYPES + 1;
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

    char *a;
    char *b;
    char *c;
    char *p;
    char *q;
    char *r;
    char *p_sq;

    switch (root_type)
    {
    case COMPLEX:
        p = icse_question_generator_random_number(rand() % context->difficulty + 1);
        q = icse_question_generator_random_number(rand() % context->difficulty + 1);

        a = malloc(2);
        a[0] = '1';
        a[1] = 0;

        b = calloc(strlen(p) + 5, 1);
        multiply("-2", p, b);

        p_sq = calloc(2 * strlen(p) + 3, 1);
        char *q_sq = calloc(2 * strlen(q) + 3, 1);
        multiply(p, p, p_sq);
        multiply(q, q, q_sq);

        c = calloc(strlen(p_sq) + strlen(q_sq) + 3, 1);
        add(p_sq, q_sq, c);

        question->answer = malloc(9);
        strcpy(question->answer, "Complex.");

        free(p);
        free(q);
        free(p_sq);
        free(q_sq);
        break;
    case RATIONAL_UNEQUAL:
        // (r^2)x^2 - (p + q)r x + pq = 0
        p = icse_question_generator_random_number(rand() % context->difficulty + 1);
        q = icse_question_generator_random_number(rand() % context->difficulty + 1);
        r = icse_question_generator_random_number(rand() % context->difficulty + 1);
        while (icse_question_generator_number_equals(r, "0"))
        {
            free(r);
            r = icse_question_generator_random_number(rand() % context->difficulty + 1);
        }

        a = calloc(2 * strlen(r) + 3, sizeof(char));
        multiply(r, r, a);

        char *t_1 = calloc(strlen(p) + strlen(q) + 3, sizeof(char));
        add(p, q, t_1);
        char *t_2 = calloc(strlen(t_1) + strlen(r) + 3, sizeof(char));
        multiply(t_1, r, t_2);

        b = calloc(strlen(t_2) + 5, sizeof(char));
        multiply(t_2, "-1", b);

        c = calloc(strlen(p) + strlen(q) + 3, sizeof(char));
        multiply(p, q, c);

        question->answer = malloc(22);
        strcpy(question->answer, "Rational and unequal.");

        // Frees
        free(p);
        free(q);
        free(r);
        free(t_1);
        free(t_2);
        break;
    case RATIONAL_EQUAL:
        p = icse_question_generator_random_number(rand() % context->difficulty + 1);
        q = icse_question_generator_random_number(rand() % context->difficulty + 1);
        while (icse_question_generator_number_equals(p, "0")) {
            free(p);
            p = icse_question_generator_random_number(rand() % context->difficulty + 1);
        }
        while (icse_question_generator_number_equals(q, "0")) {
            free(q);
            q = icse_question_generator_random_number(rand() % context->difficulty + 1);
        }

        a = calloc(2 * strlen(p) + 3, 1);
        multiply(p, p, a);

        char *p_times_q = calloc(strlen(p) + strlen(q) + 3, sizeof(char));
        multiply(p, q, p_times_q);
        b = calloc(strlen(p_times_q) + 5, 1);
        multiply(p_times_q, "-2", b);

        c = calloc (2 * strlen(q) + 3, 1);
        multiply(q, q, c);

        question->answer = malloc(20);
        strcpy(question->answer, "Rational and equal.");

        free(p);
        free(q);
        free(p_times_q);
        break;
    case IRRATIONAL_UNEQUAL:
        p = icse_question_generator_random_number(rand() % context->difficulty + 1);
        q = icse_question_generator_random_number(rand() % context->difficulty + 1);
        r = icse_question_generator_random_number(rand() % context->difficulty + 1);

        while (icse_question_generator_number_equals(q, "0")) {
            free(q);
            q = icse_question_generator_random_number(rand() % context->difficulty + 1);
        }
        while (icse_question_generator_number_equals(r, "0")) {
            free(r);
            r = icse_question_generator_random_number(rand() % context->difficulty + 1);
        }

        a = calloc(strlen(r) * 2 + 3, sizeof(char));
        multiply(r, r, a);

        char *p_times_r = calloc(strlen(p) + strlen(r) + 3, sizeof(char));
        multiply(p, r, p_times_r);
        b = calloc(strlen(p_times_r) + 5, sizeof(char));
        multiply("-2", p_times_r, b);

        p_sq = calloc(2 * strlen(p) + 3, sizeof(char));
        multiply(p, p, p_sq);
        c = calloc(strlen(p_sq) + strlen(q) + 3, sizeof(char));
        subtract(p_sq, q, c);

        question->answer = malloc(24);
        strcpy(question->answer, "Irrational and unequal.");

        free(p);
        free(q);
        free(r);
        free(p_times_r);
        free(p_sq);
        break;
    default:
        free(question);
        return 0;
    }

    question->question = realloc(question->question, (strlen(question->question) + strlen(a) + strlen(b) + strlen(c) + 15) * sizeof(char));
    strcat(question->question, a);
    strcat(question->question, "x^2 + ");
    strcat(question->question, b);
    strcat(question->question, "x + ");
    strcat(question->question, c);
    strcat(question->question, " = 0");

    free(a);
    free(b);
    free(c);

    return question;
}