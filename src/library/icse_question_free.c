#include "icse_question_generator.h"
#include <stdlib.h>

void icse_question_free(struct icse_question *question)
{
    if (question == 0)
        return;
    if (question->question)
        free(question->question);
    if (question->answer)
        free(question->answer);
    free(question);
}