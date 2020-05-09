#include "sacli.h"

sacli *sacli_init()
{
    sacli *cli = (sacli *)malloc(sizeof(sacli));
    cli->commands = (sacli_command **)calloc(DEFAULT_SAGLI_COMMANDS_CAPACITY, sizeof(sacli_command));
    cli->commands_capacity = DEFAULT_SAGLI_COMMANDS_CAPACITY;

    cli->commands_size = 0;

    return cli;
}

sacli *sacli_init_raw(
    const unsigned commands_size,
    ...)
{
    sacli *sacli = sacli_init();

    va_list commands;

    va_start(commands, commands_size);

    for (int i = 0; i < commands_size; i++) {
        sacli_add_command(sacli, va_arg(commands, sacli_command *));
    }

    va_end(commands);

    return sacli;
}

void sacli_add_command(
    sacli *sacli,
    sacli_command *command)
{
    if (sacli->commands_size >= sacli->commands_capacity) {
        sacli_command **new_commands = (sacli_command **)realloc(
            sacli->commands, (sacli->commands_capacity <<= 1) * sizeof(sacli_command));

        if (new_commands)
        {
            sacli->commands = new_commands;
            new_commands = NULL;
        }
    }

    sacli->commands[sacli->commands_size++] = command;
}

void sacli_run(sacli *sacli, const int argc, char **argv)
{
    sacli_parser *parser = sacli_parser_extract(sacli, argc, argv);

    if (parser != NULL) {
        sacli_command *command = parser->command_found;

        if (command->action && command->action != NULL) {
            command->action(command, parser->next_args, parser->next_args_size);
        }
    }
    else {
        printf("command not found\n");
    }

    sacli_parser_free(&parser);
    sacli_free(&sacli);
}

void sacli_free(sacli **sacli)
{
    sacli_command_free((*sacli)->commands, (*sacli)->commands_size);
    (*sacli)->commands = NULL;

    free(*sacli);
    sacli = NULL;
}
