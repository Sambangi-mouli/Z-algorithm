#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getZarr(const char *str, int Z[], int length) {
    int L, R, K;
    L = R = 0;
    Z[0] = 0;

    for (int i = 1; i < length; ++i) {
        if (i > R) {
            L = R = i;
            while (R < length && str[R] == str[R - L]) {
                R++;
            }
            Z[i] = R - L;
            R--;
        } else {
            K = i - L;
            if (Z[K] < R - i + 1) {
                Z[i] = Z[K];
            } else {
                L = i;
                while (R < length && str[R] == str[R - L]) {
                    R++;
                }
                Z[i] = R - L;
                R--;
            }
        }
    }
}

void search(const char *text, const char *pattern, const char *outputFile) {
    int patternLength = strlen(pattern);
    int textLength = strlen(text);
    int concatLength = patternLength + textLength + 1;
    char *concat = (char *)malloc(concatLength + 1);
    int *Z = (int *)malloc(concatLength * sizeof(int));

    sprintf(concat, "%s$%s", pattern, text);
    getZarr(concat, Z, concatLength);

    FILE *out = fopen(outputFile, "w");
    if (out == NULL) {
        printf("Error opening output file.\n");
        free(concat);
        free(Z);
        return;
    }

    int found = 0;
    for (int i = 0; i < concatLength; ++i) {
        if (Z[i] == patternLength) {
            fprintf(out, "Pattern found at index %d\n", i - patternLength - 1);
            found = 1;
        }
    }

    if (!found) {
        fprintf(out, "Pattern not found.\n");
    }

    free(concat);
    free(Z);
    fclose(out);
}

int main() {
    FILE *textFile = fopen("filename.txt", "r");
    FILE *patternFile = fopen("patternfile.txt", "r");

    if (!textFile || !patternFile) {
        fprintf(stderr, "Error opening files!\n");
        if (textFile) fclose(textFile);
        if (patternFile) fclose(patternFile);
        return 1;
    }

    char text[1000];
    char pattern[100];
    if (!fgets(pattern, sizeof(pattern), patternFile)) {
        fprintf(stderr, "Error reading pattern file.\n");
        fclose(textFile);
        fclose(patternFile);
        return 1;
    }

    if (!fgets(text, sizeof(text), textFile)) {
        fprintf(stderr, "Error reading text file.\n");
        fclose(textFile);
        fclose(patternFile);
        return 1;
    }

    // Remove newline characters if present
    pattern[strcspn(pattern, "\n")] = 0;
    text[strcspn(text, "\n")] = 0;

    search(text, pattern, "output.txt");

    fclose(textFile);
    fclose(patternFile);
    return 0;
}

