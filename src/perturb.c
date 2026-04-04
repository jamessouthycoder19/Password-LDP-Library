#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int exponential_mechanism(double *utility_space, int utility_space_length, double budget) {
    double *weights = malloc((utility_space_length) * sizeof(double));
    double total_weight = 0;
    for (int i = 0; i < utility_space_length; i++) {
        weights[i] = exp((utility_space[i] * budget) / 2.0);
        total_weight += weights[i];
    }

    double *probabiltiies = malloc((utility_space_length) * sizeof(double));
    for (int i = 0; i < utility_space_length; i++) {
        probabiltiies[i] = weights[i] / total_weight;
    }

    double rand_val = ((double) rand() / (double) RAND_MAX);
    double cumulative_prob = 0.0;

    for (int i = 0; i < utility_space_length; i++) {
        cumulative_prob += probabiltiies[i];
        if (rand_val < cumulative_prob) {
            free(weights);
            free(probabiltiies);
            return i;
        }
    }

    free(weights);
    free(probabiltiies);
    return utility_space_length - 1;
}

void perturb_word(char *token, double budget) {
    // Placeholder for perturbing a word token using the given budget
    // This could involve synonym replacement, character swapping, etc.
}

void perturb_number(char *token, int token_len, double budget) {
    int len_num = token_len;

    int max_num = 1;
    for(int i = 0; i < len_num; i++) max_num *= 10;
    max_num -= 1;

    int token_num = atoi(token);

    // Create utility space
    double *utility_space = malloc((max_num + 1) * sizeof(double));
    for (int i = 0; i <= max_num; i++) {
        utility_space[i] = -1.0 * abs(token_num - i);
    }

    int selection = exponential_mechanism(utility_space, max_num + 1, budget);

    // Create a temporary buffer to format the number
    // Ensure it's large enough for any integer
    char fmt_buf[32];
    // Use %0*d to preserve leading zeros if the original had them (e.g., "07")
    sprintf(fmt_buf, "%0*d", len_num, selection);

    // Only copy up to the original length to avoid overflowing the password buffer
    memcpy(token, fmt_buf, len_num);
    
    free(utility_space);
}

void perturb_special(char *token, double budget) {
    // Placeholder for perturbing a special character token using the given budget
    // This could involve character replacement, shuffling, etc.
}