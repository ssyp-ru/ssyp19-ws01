#ifndef FS_H_
#define FS_H_

#define MAX_PATH_LENGTH 1024
#define BUF_SIZE 1024
#define _GG_DIR_NAME "/.gg"
#define GG_DIR_NAME ".gg"


int fs_copy(const char *path_from, const char *path_to);

int fs_delete(const char *path);

int fs_mkdir(const char *path);

int fs_move(const char *path_from, const char *path_to);

int is_file(const char *path);

int is_directory(const char *path);

int get_gg_root_path(char *buf);

int str_del_prelast_slash(char *string);

int fs_read_to_string(const char *path_from, char *str);

int fs_write_from_string(const char *path_to, const char *str);

#endif
