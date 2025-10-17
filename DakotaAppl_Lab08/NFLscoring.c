/* 
NFL scoring combinations
Author: Dakota Appl
KUID: 3175599
Date Created: 10/17/25
Purpose: Given an integer score, determine all possible combinations of
scoring plays that can result in that score.
Scoring plays allowed: 8 (TD+2), 7 (TD+1), 6 (TD), 3 (FG), 2 (Safety).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char line[128];

    while (1) {
        printf("Enter the NFL score (Enter 1 to stop): ");
        if (fgets(line, sizeof line, stdin) == NULL) {
            // EOF
            break;
        }

        // skip leading whitespace
        char *p = line;
        while (*p == ' ' || *p == '\t') ++p;

        char *endptr;
        long score = strtol(p, &endptr, 10);
        if (p == endptr) {
            printf("Invalid input; please enter an integer (or 1 to stop).\n");
            continue;
        }

        if (score == 1) {
            break;
        }

        if (score < 0) {
            printf("Score must be non-negative (or 1 to stop).\n");
            continue;
        }

        printf("Possible combinations of scoring plays if a team's score is %ld:\n", score);

        int found = 0;
        for (int td2 = 0; td2 <= score / 8; ++td2) {           // 8-point TD
            for (int td1 = 0; td1 <= (score - 8*td2) / 7; ++td1) { // 7-point TD
                for (int td0 = 0; td0 <= (score - 8*td2 - 7*td1) / 6; ++td0) { // 6-point TD 
                    for (int fg = 0; fg <= (score - 8*td2 - 7*td1 - 6*td0) / 3; ++fg) { // 3-point FG
                        int rem = score - 8*td2 - 7*td1 - 6*td0 - 3*fg;
                        if (rem < 0) continue;
                        if (rem % 2 != 0) continue; // safeties are 2 points
                        int saf = rem / 2;
                        printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n",
                               td2, td1, td0, fg, saf);
                        found = 1;
                    }
                }
            }
        }

        if (!found) {
            printf("No combinations found.\n");
        }
    }

    return 0;
}