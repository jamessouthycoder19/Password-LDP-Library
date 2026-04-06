#include <stdio.h>
#include <string.h>

#include <ldpasswd/ldpasswd.h>

int main(void) {
    char test_pws[][64] = {
        "musketeer333marshmallow",
        "!blah#Thing^",
        "Password7JamesTh1ngFather",
        "PassWord123",
        "Unknownword",
        "jamesblahblahblah",
        "P@sSw0Rd",
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

    double epsilon_values[] = {40, 30, 20, 15, 10, 5, 2.5, 1};
    for (int j = 0; j < 8; j++) {
        printf("Epsilon: %f\n", epsilon_values[j]);
        int num_same = 0;
        for (int i = 0; i < 29; i++) {
            for (int k = 0; k < 1000; k++) {
                char temp[64];
                strncpy(temp, test_pws[i], 64);
                perturb_password(temp, epsilon_values[j]);
                if (strcmp(temp, test_pws[i]) == 0) {
                    num_same++;
                }   
            }
        }
        printf("Percent Changed: %f\n\n", 100.0 * (29000 - num_same) / 29000);
    }
}