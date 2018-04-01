#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 64

struct Line {
    size_t start;
    size_t end;
    
    char buf[LINE_LENGTH];
};

int ReadLine(const char *str, struct Line *l) {
    int nvariables = 0;
    int nchars = 0;
    for (int i=LINE_LENGTH+1; i--; l->buf[i]=0) ;
    // although the format string specifies 64 characters, 
    // it really expects to read in less than 60 chars.
    nvariables = sscanf(str + l->start, "%64s", l->buf);
    if (! nvariables) {
        return 0;
    }
    if (! (nchars = strlen(l->buf))) {
        return 0;
    }
    assert(nchars <= LINE_LENGTH - 4);
    // count in the newline character
    l->start += nchars + 1;
    return 1;
}

// no space is allowed
// try write out a line that is longer than 60 chars (including \n),
// the assert statement will fail
const char *SUT =\
"A->B\n"
"A->C\n"
"B->D,D->F\n"
"C->E,E->M\n";

int main(int argc, char **argv) {
    int n = 0;
    struct Line l;
    l.start = 0;
    l.end = 0;
    while (ReadLine(SUT, &l)) {
        printf("<line>%s</line>", l.buf);
    }
    return 0;
}
