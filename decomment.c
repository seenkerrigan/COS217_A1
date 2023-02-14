#include <stdio.h>
#include <ctype.h>

enum Statetype {NORMAL, INCOMMENT, INCHAR, INSTRING};

enum Statetype
handleNormalState(int c) {
    enum Statetype state;
    if (c=='/' && getchar()=='*') {
        state = handleCommentState(c);
        state = INCOMMENT;
        putchar(' ');
    }
    else {
        if (c=='\'') {
            state = INCHAR;
            putchar(c);
        }
        else {
            if (c=='"') {
                state = INSTRING;
                putchar(c);
            }
            else state = NORMAL;
        }
    }
    return state;
}

enum Statetype
handleCommentState(int c) {
    enum Statetype state;
    if (c=='*' && getchar()=='/') {
        state = NORMAL;
    }
    else state = INCOMMENT;
    return state;
}

enum Statetype
handleCharState(int c) {
    enum Statetype state;
    if (c=='\'') {
        state = NORMAL;
        putchar(c);
    }
    state = INCHAR;
    putchar(c);
    return state;
}

enum Statetype
handleStringState(int c) {
    enum Statetype state;
    if (c=='"') {
        state = NORMAL;
        putchar(c);
    }
    putchar(c);
    state = INSTRING; 
    return state;
}
int main(void) {
    int c;
    enum Statetype state = NORMAL;
    while ((c = getchar())!=EOF) {
        switch (state) {
            case NORMAL:
                state = handNormalState(c);
                break;
            case INCOMMENT:
                state = handleCommentState(c);
                break;
            case INCHAR:
                state = handleCharState(c);
                break;
            case INSTRING:
                state = handleStringState(c);
                break;
        }
    }
    return 0;
}