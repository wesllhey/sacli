#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "sacli_parser.h"

sacli_parser *sacli_parser_extract(
    const sacli *sacli,
    const int argc,
    char **argv)
{
    unsigned last_index_found = 0;

    sacli_command *command = NULL;
    for (unsigned i = 1; i < sacli->commands_size; i++) {
        for (; last_index_found < argc; last_index_found++) {
            if (command != NULL) {
                if (command->has_sub_commands) {
                    command = sacli_parser_find_command_by_arg(command->sub_commands, command->sub_command_size, argv[last_index_found]);
                }
                break;
            }
            
            command = sacli_parser_find_command_by_arg(sacli->commands, sacli->commands_size, argv[last_index_found]);
        }

        if (command != NULL)
            break;
    }

    if (command == NULL)
        return NULL;

    sacli_parser *parser = (sacli_parser *)malloc(sizeof(sacli_parser));
    parser->next_args_size = argc == last_index_found ? 0 : argc - 1 - last_index_found;

    if (parser->next_args_size > 0) {
        char **next_args = (char **)calloc(parser->next_args_size, sizeof(char));

        for (int i = 0; i < parser->next_args_size; i++) {
            next_args[i] = argv[last_index_found + 1 + i];
        }

        parser->next_args = next_args;
    } else {
        parser->next_args = NULL;
    }

    parser->command_found = command;

    return parser;
}

sacli_command *sacli_parser_find_command_by_arg(
    sacli_command **commands,
    const unsigned command_size,
    char *arg)
{
    for (int i = 0; i < command_size; i++) {
        sacli_command *command = commands[i];

        if (strcmp(command->name, arg) == 0 || (command->alias != NULL && (strcmp(command->alias, arg)) == 0)) {
            return command;
        }
    }

    return NULL;
}

void sacli_parser_free(
    sacli_parser **parser)
{
    free(*parser);
    *parser = NULL;
}
