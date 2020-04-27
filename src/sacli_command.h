#ifndef __SACLI_COMMAND__
#define __SACLI_COMMAND__

#include <stdbool.h>

#define SACLI_DEFAULT_SUB_COMMANDS_CAPACITY 1 << 4

typedef struct sacli_command {
    char *name;
    char *alias;
    char *usage_text;
    unsigned sub_command_size;
    unsigned sub_command_capacity;
    struct sacli_command **sub_commands;
    bool has_sub_commands;
    void (*action)(char **next_args, unsigned next_args_size);
    void (*add_sub_command)(struct sacli_command *self, struct sacli_command *sub_command_arg);
    void (*add_sub_command_raw)
        (struct sacli_command *self, char *name, char *alias, char *usage_text, void (*action)(char **next_args, unsigned next_args_size));
} sacli_command;

extern sacli_command *sacli_command_create(
    char *name,
    char *alias,
    char *usage_text);

extern sacli_command *sacli_command_create_raw(
    char *name,
    char *alias,
    char *usage_text,
    void (*action)(char **next_args, unsigned next_args_size));

extern void sacli_command_add_sub_command(
    sacli_command *command,
    sacli_command *sub_command);

extern void sacli_command_add_sub_command_raw(
    sacli_command *command,
    char *name,
    char *alias,
    char *usage_text,
    void (*action)(char **next_args, unsigned next_args_size));

extern void sacli_command_free(
    sacli_command **commands,
    const unsigned commands_size);

#endif