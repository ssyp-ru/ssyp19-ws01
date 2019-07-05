#ifndef REGISTRY_H_
#define REGISTRY_H_

enum Commands {
    PUSH,
    CHECKOUT,
    COUNT
};

struct cli_module;

void cli_register_command(struct cli_module *cli_module);
#endif
