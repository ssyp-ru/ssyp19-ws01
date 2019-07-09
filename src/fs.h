#ifndef FS_H_
#define FS_H_

// Review: why there is two defines (in c AND h files)?
#define MAX_PATH_LENGTH 1024
#define BUF_SIZE 1024
// Review: why /.gg ??? Are you create gg folder in root folder?
#define GG_DIR_NAME "/.gg"

// Review: dont really like "file_" prefix. Make fs_copy ... 

int file_copy(const char *path_from, const char *path_to);

int file_delete(const char *path);

int file_mkdir(const char *path);

int file_move(const char *path_from, const char *path_to);

int is_file(const char *path);

int is_directory(const char *path);

int get_gg_root_path(char *buf);

int str_del_prelast_slash(char *string);

int file_read_to_string(const char *path_from, char *str);

int file_write_from_string(const char *path_to, const char *str);

#endif
