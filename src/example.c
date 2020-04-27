#include <stdlib.h>
#include <stdio.h>

#include "sacli_parser.h"
#include "sacli.h"

void command_1_action(char **next_args, unsigned next_args_size)
{
    printf("command 1\n");
}

void command_1_sub_action(char **next_args, unsigned next_args_size)
{
    printf("command 1 sub\n");
}

void command_2_action(char **next_args, unsigned next_args_size)
{
    printf("command 2\n");
}

void command_2_sub_action(char **next_args, unsigned next_args_size)
{
    printf("command 2 sub\n");
}

int main(int argc, char **argv)
{
    sacli_command *command_1 = sacli_command_create_raw("command1", "c1", "this is the command1 with alias c1", command_1_action);
    command_1->add_sub_command_raw(command_1, "c1-sub", "c1-s", "this is the sub command of command 1 with alias c1-s", command_1_sub_action);
    // OR 
    // sacli_command_add_sub_command_raw(command_1, "c1-sub", "c1-s", "this is the sub command of command 1 with alias c1-s", command_1_sub_action);

    sacli_command *command_2 = sacli_command_create_raw("command2", "c2", "this is the command2 with alias c2", command_2_action);
    command_2->add_sub_command_raw(command_2, "c2-sub", "c2-s", "this is the sub command of command 1 with alias c2-s", command_2_sub_action);
    // OR 
    // sacli_command_add_sub_command_raw(command_2, "c2-sub", "c2-s", "this is the sub command of command 1 with alias c2-s", command_2_sub_action);
    sacli *sacli = sacli_init_raw(2, command_1, command_2);

    sacli_run(sacli, argc, argv);

    return EXIT_SUCCESS;
}
