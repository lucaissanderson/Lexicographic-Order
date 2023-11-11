//----------------------------
//          Lex.c
//     Lucais Sanderson
//         lzsander
//           pa1
//----------------------------

//----------------------------
//          Citation
//   Much of this program is
//   based on the FileIO.c
//   provided from the examples
//   at
//   https://people.ucsc.edu/~ptantalo/cse101/Spring23/Examples/C/FileIO/FileIO.c
//---------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LINE_LENGTH 1000
#define MAX_LINES 10000


int main(int argc, char* argv[]) {
    FILE* in;
    FILE* out;
    char** lines;
    char line[MAX_LINE_LENGTH];
    int i, j, n;

    // open files
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    if (in == NULL) {
        fprintf(stderr, "Unable to open file %s\n", argv[1]);
        exit(1);
    }

    if (out == NULL) {
        fprintf(stderr, "Unable to open file %s\n", argv[2]);
        exit(1);
    }

    // fill array with line-strings
    n = 0;
    lines = NULL;
    while (fgets(line, MAX_LINE_LENGTH, in) != NULL) {
        lines = realloc(lines, sizeof(char*) * (n + 1));
        lines[n] = calloc(strlen(line) + 1, sizeof(char));
        strcpy(lines[n], line);
        n++;
    }

    // sort into List
    List L = newList();
    append(L, 0);
    // implement insertion sort alg. indirectly
    for (i = 1; i < n; i++) {
        moveBack(L);
        j = index(L);
        while (j >= 0 && strcmp(lines[i], lines[get(L)]) < 0) {
            movePrev(L);
            j = index(L);
        }
        if (index(L) >= 0) {
            insertAfter(L, i);
        } else {
            prepend(L, i);
        }
    }

    // print array using sorted list
    moveFront(L);
    for (i = 0; i < n; i++) {
        fprintf(out, "%s", lines[get(L)]);
        moveNext(L);
    }

    // free and close everything
    for (i = 0; i < n; i++) {
        free(lines[i]);
    }
    free(lines);
    freeList(&L);

    fclose(in);
    fclose(out);

    return 0;
}

