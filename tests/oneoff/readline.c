#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 64

struct Line;

typedef void (*ResetFunc)(struct Line *l);
typedef int (*ReadFunc)(const char *str, struct Line *l);
typedef int (*CheckFunc)(struct Line *l);

struct Line {
    size_t start;
    size_t end;
    
    void *data;

    ResetFunc reset;
    ReadFunc read;
    CheckFunc check;
};

///////////////////////////////////////////////////////////

void ResetString(struct Line *l) {
    for (int i=LINE_LENGTH+1; i--; ((char *)(l->data))[i]=0) ;
}

int ReadString(const char *str, struct Line *l) {
    // although the format string specifies 64 characters, 
    // it really expects to read in less than 60 chars.
    return sscanf(str + l->start, "%64s", (char *)(l->data)); 
}

int CheckString(struct Line *l) {
    int nchars = 0;
    if (! (nchars = strlen((char *)(l->data)))) {
        return 0;
    }
    if (nchars > LINE_LENGTH - 4) {
        return 0;
    }
    // count in the newline character
    l->start += nchars + 1;
    return 1;
}

struct Line CreateString() {
    struct Line l;
    l.data = malloc(LINE_LENGTH);
    l.reset = ResetString;
    l.read = ReadString;
    l.check = CheckString;
    l.start = 0;
    l.end = 0;
    return l;
}

void DeleteString(struct Line *l) {
    free(l->data);
    l->data = NULL;
}

///////////////////////////////////////////////////////////

int ReadLine(const char *str, struct Line *l) {
    l->reset(l);
    if (! (l->read(str, l) && l->check(l))) {
        return 0;
    }
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
    struct Line l = CreateString();
    while (ReadLine(SUT, &l)) {
        printf("<line>%s</line>", (char *)(l.data));
    }
    DeleteString(&l);
    return 0;
}
