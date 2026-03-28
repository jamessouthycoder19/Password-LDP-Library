#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <json-c/json.h>

#include <ldpasswd/ldpasswd.h>

int tokenize(const char *input) {
    // First get the length of the password
    int length = strlen(input);

    // Array to hold starting indices of each token
    int start_of_token_indicies[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    int token_count = 0;
    for (int i = 0; i < length; i++) {
        // Only storing 20 tokens
        if (token_count >= 20) {
            break;
        } else {
            start_of_token_indicies[token_count] = i;
            token_count++;
        }
        // First check if we have a number
        if (input[i] >= '0' && input[i] <= '9') {
            for (int j = i + 1; j < length; j++) {
                // figure out if we have a number after
                // If not, break out of the 'j' loop.
                if (input[j] < '0' || input[j] > '9') {
                    break;
                } else {
                    // If we do, increment i again to skip over the number
                    // because that gets counted with the previous token.
                    i = j;
                }
            }
        }
        // Next check if we have a special character.
        // No need to check for any other special characters after,
        // they should each be treated as their own token
        else if ((input[i] >= '!' && input[i] <= '/') || (input[i] >= ':' && input[i] <= '@') || (input[i] >= '[' && input[i] <= '`') || (input[i] >= '{' && input[i] <= '~')) {
            start_of_token_indicies[token_count] = i;
            token_count++;
        }
        // Next letters.
        // If we have a capital.
        //            Then if there is a lowercase letter after, keep going until capital or non letter is found, thats the end of token. There should be at least 2 lowercase
        //                                                   
        // If 
        else if (input[i] >= 'A' && input[i] <= 'Z') {
            // start_of_token_indicies[token_count] = i;
            // token_count++;
            // for (int j = i + 1; j < length; j++) {
            //     // figure out if we have a lowercase letter after
            //     // If not, break out of the 'j' loop.
            //     if (input[j] < 'a' || input[j] > 'z') {
            //         break;
            //     } else {
            //         // If we do, increment i again to skip over the lowercase letter
            //         // because that gets counted with the previous token.
            //         i = j;
            //     }
            // }
        }
    }
    return 0;
}

void hello(void) {
    printf("Hello, World!\n");
    

    FILE *file = fopen("/home/james/LDPasswd/data/data.txt", "r");
    if (file == NULL) {
        perror("Unable to open file");
        return 1;
    }

    // Array to hold 6 string pointers
    const char *raw_lines;
    char *temp_line = NULL;
    size_t len = 0;

    // getline handles the memory allocation for the temporary read
    while (getline(&temp_line, &len, file) != -1) {
        
        // Remove trailing newline if present
        temp_line[strcspn(temp_line, "\r\n")] = '\0';

        // Use strdup to create a permanent copy for our array
        raw_lines = strdup(temp_line);
    }

    // Free the temporary buffer used by getline
    free(temp_line);
    fclose(file);

    struct json_tokener *tok = json_tokener_new();
    const struct json_object *json_dict;
    // const char *json_str = "{\"name\": \"Alice\", \"age\": 30, \"is_student\": false}";
    json_dict = json_tokener_parse_ex(tok, raw_lines, strlen(raw_lines));

    json_tokener_free(tok);
    free((void *)raw_lines);

    // At this point all of the JSON wordlists have bene parsed correctly. 
    // This wil obviously get organized better into functions and what not
    // but after this is how we would tokenize a password and what not

    const char *example_password = "JamesPassword123!";

    // Split up into tokens of length 2
    char tokens[100][3]; // Assuming max 100 tokens of length 2
    int token_count = 0;
    for (int i = 0; i < strlen(example_password); i += 2) {
        snprintf(tokens[token_count], sizeof(tokens[token_count]), "%c%c", example_password[i], example_password[i + 1]);
        token_count++;
    }

    for (int i = 0; i < token_count; i++) {
        printf("Token %d: %s\n", i + 1, tokens[i]);
    }

    // Below this is cleanup code to free the memory allocated for the lines and the json objects.
    json_object_put((struct json_object *)json_dict);

    return 0;
}