#ifndef TEXT_DIFF_H_
#define TEXT_DIFF_H_

enum diff_types{
    ADD,
    DELETE,
    CHANGE
};

typedef struct{
    int s1_from;
    int s1_len;
    int s2_from;
    int s2_len;
    int diff_type;
}diff_t;

diff_t **diff_find(const char **s1, const int len1, const char **s2, const int len2, int *num_of_diffs);

diff_t **file_diff(const char *path1, const char *path2, int *num_of_diffs);

int diff_print(const char **s1, const char **s2, diff_t **diffs, int n);
#endif
