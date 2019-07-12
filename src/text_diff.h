#ifndef TEXT_DIFF_H_
#define TEXT_DIFF_H_

enum diff_types{
    ADD,
    DELETE,
    CHANGE,
    NOT_CHANGE
};

typedef struct{
    int s1_from;
    int s1_len;
    int s2_from;
    int s2_len;
    int diff_type;
}diff_t;

diff_t **diff_find(char **s1, int len1, char **s2, int len2, int *num_of_diffs);

diff_t **file_diff(const char *path1, const char *path2, int *num_of_diffs);

int diff_print(char **s1, char **s2, diff_t **diffs, int n);
#endif
