#ifndef LDPASSWD_LEET_H
#define LDPASSWD_LEET_H

// Struct to hold the results of un-leeting a password
typedef struct {
    char **strings;
    int count;
    int capacity;
} ResultList;

ResultList generate_unleet(const char *input);

#endif