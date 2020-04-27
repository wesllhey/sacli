#ifndef __SACLI__
#define __SACLI__

#define DEFAULT_SAGLI_COMMANDS_CAPACITY 1 << 4

#include "sacli_command.h"

typedef struct sacli {
    char *name;
    char *usage_text;
    unsigned version;
    struct sacli_command **commands;
    unsigned commands_capacity;
    unsigned commands_size;
    // void (*add_command)(struct sacli *self, struct sacli_command *command);

} sacli;

extern sacli *sacli_init();

extern sacli *sacli_init_raw(
    const unsigned commands_size,
    ...);

extern void sacli_add_command(
    sacli *sacli,
    sacli_command *command);

#include "sacli_parser.h"

extern void sacli_run(
    sacli *sacli, 
    const int argc, 
    char **argv);

extern void sacli_free(
    sacli **sacli);

#endif
