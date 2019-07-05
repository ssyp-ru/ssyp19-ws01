#ifndef REGISTRY_H_
#define REGISTRY_H_

enum Commands {
    UPDATE_INDEX,
    WRITE_TREE,
    LS_FILES,
    CAT_FILE,
    HASH_OBJ,
    COMMIT_TREE,
    LOG,
    COUNT
};

struct cli_module;

void cli_register_command(struct cli_module *cli_module);
#endif
