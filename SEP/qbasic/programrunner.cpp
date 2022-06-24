#include "programrunner.h"

programRunner::programRunner()
{
    this->savedCode = new code;
    savedCode->head = NULL;
    savedCode->num_of_cmd = 0;
}
