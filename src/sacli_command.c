#include <stdlib.h>

#include "sacli_command.h"

sacli_command *sacli_command_create(
    char *name,
    char *alias,
    char *usage_text)
{
    sacli_command *command = (sacli_command *)malloc(sizeof(sacli_command));
    command->sub_commands = (sacli_command **)calloc(SACLI_DEFAULT_SUB_COMMANDS_CAPACITY, sizeof(sacli_command));
    command->sub_command_capacity = SACLI_DEFAULT_SUB_COMMANDS_CAPACITY;
    command->has_sub_commands = false;
    command->sub_command_size = 0;
    command->alias = alias;
    command->name = name;

    command->add_sub_command = sacli_command_add_sub_command;
    command->add_sub_command_raw = sacli_command_add_sub_command_raw;

    return command;
}

sacli_command *sacli_command_create_raw(
    char *name,
    char *alias,
    char *usage_text,
    void (*action)(char **next_args, unsigned next_args_size))
{
    sacli_command *command = sacli_command_create(name, alias, usage_text);
    command->action = action;

    return command;
}

void sacli_command_add_sub_command(
    sacli_command *command,
    sacli_command *sub_command)
{
    if (command->sub_command_size >= command->sub_command_capacity) {
        sacli_command **new_sub_commands =
            (sacli_command **)realloc(command->sub_commands, (sub_command->sub_command_capacity <<= 1) * sizeof(sub_command));

        if (new_sub_commands) {
            command->sub_commands = new_sub_commands;
            new_sub_commands = NULL;
        }
    }
    command->has_sub_commands = true;
    command->sub_commands[command->sub_command_size++] = sub_command;
}

void sacli_command_add_sub_command_raw(
    sacli_command *command,
    char *name,
    char *alias,
    char *usage_text,
    void (*action)(char **next_args, unsigned next_args_size))
{
    sacli_command *sub_command = sacli_command_create_raw(name, alias, usage_text, action);
    sacli_command_add_sub_command(command, sub_command);
}

void sacli_command_free(
    sacli_command **commands,
    const unsigned commands_size)
{

    for (int i = 0; i < commands_size; i++) {
        sacli_command *command = commands[i];
        if (command->has_sub_commands) {
            sacli_command_free(command->sub_commands, command->sub_command_size);
        }

        free(command);
        command = NULL;
    }

    free(commands);
    commands = NULL;
}
