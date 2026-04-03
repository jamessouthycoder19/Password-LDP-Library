#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ldpasswd/ldpasswd.h"
#include "ldpasswd/tokenize.h"

void hello() {
    const char *test_pws[] = {
        "PassWord123",
        "Unknownword",
        "jamesblahblahblah",
        "P@sSw0Rd",
        "Password7JamesTh1ngFather",
        "passw0rdRed14&TeamSucks",
        "123PassWord123",
        "1Unknown(((wordBlah",
        "P@sSw0RdJ4mes",
        "Change.me123!",
        "starburst",
        "PleaseDont5489CH32",
        "Super123!?",
        "VikingWorksAgain!",
        "RedTeamIsUgly!!",
        "White#Comet192@Map28",
        "WhyAreWeStillHere2015?",
        "foobarbaz5",
        "weloveyouredteam",
        "RickerBalls2",
        "Idkwhatimdoinghelp1",
        "ThankYouWhiteTeam",
        "Apple432Bottom#",
        "Welcome1",
        "RedTeamSucks3",
        "LemonJumpSlide1#",
        "AngleBatman1!"
    };

    for (int i = 0; i < 27; i++) {
    // for (int i = 0; i < 1; i++) {
        // Array to hold starting indices of each token
        int *start_of_token_indicies = malloc(20 * sizeof(int));
        for (int i = 0; i < 20; i++) {
            start_of_token_indicies[i] = -1;
        }
        int token_count = 0;

        // Array to hold type of each token (word, number, special, or other)
        char *token_types = malloc(20 * sizeof(char));
        for (int i = 0; i < 20; i++) {
            token_types[i] = '\0';
        }


        printf("Tokenizing: %s\n", test_pws[i]);
        int tokens = tokenize_password(test_pws[i], start_of_token_indicies, token_types);
        for (int j = 0; j < 20; j++) {
            if (start_of_token_indicies[j] != -1) {
                int next_token_start = (j < 19) ? start_of_token_indicies[j + 1] : strlen(test_pws[i]);
                if (token_types[j] == 'w') {
                    printf("Word");
                } else if (token_types[j] == 'n') {
                    printf("Number");
                } else if (token_types[j] == 's') {
                    printf("Special");
                } else {
                    printf("Other");
                }
                printf(":%.*s\n", next_token_start - start_of_token_indicies[j], test_pws[i] + start_of_token_indicies[j]);
                // printf("%d:%c  ", start_of_token_indicies[j], token_types[j]);
            }
        }
        printf("\n");
    }
}