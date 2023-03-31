#ifndef _icse_question_generator_h_
#define _icse_question_generator_h_
#include <stddef.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif

enum icse_question_generator_subject {
    MATHEMATICS
};

enum icse_question_type {
    QUADRATIC_EXAMINE_ROOTS,
    QUADRATIC_FIND_COEFFICIENTS,
    QUADRATIC_SIMPLE_FACTORABLE,
    QUADRATIC_TEDIOUS_FACTORABLE,
};

enum icse_question_generator_quadratic_examine_roots_root_types {
    ANY,
    COMPLEX,
    RATIONAL_EQUAL,
    RATIONAL_UNEQUAL,
    IRRATIONAL_UNEQUAL
};

/// @brief The context/settings for the question generator.
struct icse_question_generator_context {
  /// @brief The grade level of the question, 1-10.
  int grade;
  enum icse_question_generator_subject subject;
  /// @brief This is proportional to the number of significant digits in the
  /// question, 1 or 2 is recommended.
  int difficulty;
  enum icse_question_type type;
};

struct icse_question {
    char *question;
    char *answer;
};

void icse_question_free(struct icse_question *question);

/// @brief The general question generator function. Generates a question based on the context provided with the default settings.
struct icse_question *icse_question_generator_generate(struct icse_question_generator_context *context);

struct icse_question *icse_question_generator_quadratic_examine_roots(struct icse_question_generator_context *context, enum icse_question_generator_quadratic_examine_roots_root_types root_type);

// Not meant for public use, but there's really nothing stopping you from using it.
char *icse_question_generator_random_number(size_t number_of_digits);
// I should really be doing this in bmo
bool icse_question_generator_number_equals(char *a, char *b);

#ifdef __cplusplus
}
#endif

#endif