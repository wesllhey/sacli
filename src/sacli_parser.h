#ifndef __SACLI_PARSER__
#define __SACLI_PARSER__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "sacli.h"

typedef struct sacli_parser {
    char **next_args;
    unsigned next_args_size;
    struct sacli_command *command_found;
} sacli_parser;

extern sacli_parser *sacli_parser_extract(
    const sacli *sacli,
    const int argc,
    char **argv);

extern sacli_command *sacli_parser_find_command_by_arg(
    sacli_command **commands,
    const unsigned command_size,
    char *arg);

extern void sacli_parser_free(
    sacli_parser **parser);

#endif