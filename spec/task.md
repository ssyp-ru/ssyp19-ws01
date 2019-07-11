# 1 fs helpers
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

# 2 CLI module
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
# 2.1
Сделать вывод --help

# (Done) 3 integration test module
Модуль тестирования. Нужно научится запускать программы, запихивать туда stdin и принwrite-treeимать его stdout. Сравнивать с ожидаемым.
```c
test_bin_t * test_case = create_test_case("programm_name");
test_case->args({"arg1", "arg2", ...});
test_case->stdin("");
test_case->env_var({"", "", ...});
test_case->expect_code(0);
test_case->expect_stdout("")
```

# 4 ini file parser
файл такого формата (см. .gitconfig для примера):
```
[section_name]
var_name = var_value
```
нужен примерно такой интерфейс
```c
ini_storage_t * ini_storage = ini_parse(filepath);
char buf[100];
ini_get_value(section_name, var_name, buf); // section_name may be ""
ini_set_value(section_name, var_name, value);
```


# 5 gitignore
нужно сделать функцию, которая принимает путь и возвращает 1 если он соответствует gitignore

# 6 rev-parse, rev-update
функции, которые возвращают и записывают rev

#6.1 rev-list

#6.2 HEAD~2 syntax

# 7 filelock

# 8 hash-object, sha lib interration, cat-file
флаги для:
hash-object: -w --stdin, [filename]
cat-file: -p -t

# 9 update-index, ls-files, write-tree

# 10 commit-tree

# 11 read env vars
нужно уметь читать переменные окружения (через отдельный модуль?)

# 12 add, commit

# 13 simple log

# 14 text diff

# 15 commit diff

# 16 merge fast-forward

# 17 automerge

# 18 GC

# 19 log flags

# 20 cherry-pick

# 21 commit --amend

# 22 config

# (Done) 23 string_t

основные str функции + 

```c
void read_str_from_file(string_t * s, const char* path);
void write_str_to_file(string_t * s, const char* path);
```

# 24 make patch, apply patch

# 25 sha1 helper function
```c
void calc_sha_str(char hash[SHA_LENGHT], const char* data, int len);
void calc_sha_file(char hash[SHA_LENGHT], const char* path_to_file);
```

# 26 gg init
If not exists, create .gg and .gg/objects folders

# 27 git checkout
Нужно уметь читать tree object во внутреннюю структуру, искать соответствующие блобы и записывать их в файловую систему
