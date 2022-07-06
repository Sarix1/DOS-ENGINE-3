#include "status.h"

#define DECL_ERR_STR(unused,str) str,
const char far* error_strings[NUM_ERRORS] =
{
    "OK",
    "Error",
    FOR_EACH_ERROR(DECL_ERR_STR)
};
#undef DECL_ERR_STR