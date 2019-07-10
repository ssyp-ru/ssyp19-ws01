#ifndef REV_H_
#define REV_H_


int find_ref_file(const char *refname, char *buf);

int rev_parse(const char *refname, char *buf);

int rev_update(const char *refname, const char *newvalue, const char *oldvalue); 

#endif
