#ifndef LDPASSWD_PERTURB_H
#define LDPASSWD_PERTURB_H

void perturb_word(char *token, double budget);
void perturb_number(char *token, int token_len, double budget);
void perturb_special(char *token, double budget);

#endif