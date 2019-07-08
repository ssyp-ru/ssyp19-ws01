# 1 
Написать модуль с хелперами для файловых операций. Необходимый (возможно не достаточный) список:
```c
int copy(const char* from, const char* to);
int move(const char* from, const char* to);
int delete(const char* path);
int mkdir(const char* path);
int is_file(const char* path);
int is_directory(const char* path);
void get_gg_root_dir_path(char buffer[MAX_PATH_LENGHT]);
```

# 2
Написать модуль CLI. Должно это выглядеть примерно так (с клиентской стороны):
```c
enum Commands {
    CHECKOUT_COMMAND,
    ...
};

void cli_register_commands(cli_module_t * cli_module) {
// ...
// comand register
register_command(cli_module, CHECKOUT_COMMAND, "checkout", "help message");
add_named_argument(cli_module, CHECKOUT_COMMAND, "long_name", "l", , "help message");
add_positional_argument(cli_module, CHECKOUT_COMMAND, "name", 1, , "help message");

// ...
}

// command parse
cli_module_t * cli_module = cli_create();
cli_register_commands(cli_module);
cli_parse(cli_module, argc, argv);

switch (cli_module->command_type) {
    case CHECKOUT_COMMAND: ...
}

```

# 3
Модуль тестирования. Нужно научится запускать программы, запихивать туда stdin и принwrite-treeимать его stdout. Сравнивать с ожидаемым.
```c
test_bin_t * test_case = create_test_case("programm_name");
test_case->args({"arg1", "arg2", ...});
test_case->stdin("");
test_case->env_var({"", "", ...});
test_case->expect_code(0);
test_case->expect_stdout("")
```
# 3.1
Сделать вывод --help

# 4
ini file parser

# 5
gitignore

# 6
rev-parse, rev-update, rev-list

# 7
filelock

# 8
hash-object, sha lib interration, cat-file

# 9
update-index, ls-files, write-tree

# 10
commit-tree

# 11
read env vars

# 12
add, commit

# 13
simple log

# 14
text diff

# 15
commit diff

# 16
merge fast-forward

# 17
automerge

# 18
GC

# 19
log flags

# 20
cherry-pick

# 21
commit --amend

# 22
config

# 23
string_t

основные str функции + 

```c
void read_str_from_file(string_t * s, const char* path);
void write_str_to_file(string_t * s, const char* path);
```

# 24
make patch, apply patch

# 25
sha1 helper function
```c
void calc_sha_str(char hash[SHA_LENGHT], const char* data, int len);
void calc_sha_file(char hash[SHA_LENGHT], const char* path_to_file);
```
