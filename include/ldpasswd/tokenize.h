#ifndef LDPASSWD_TOKENIZE_H
#define LDPASSWD_TOKENIZE_H

int tokenize_password(const char *pw, int *start_of_token_indices, char *token_types);

#endif