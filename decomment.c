#include <stdio.h>
#include <ctype.h>

enum Statetype {NORMAL, INCOMMENT, INCHAR, INSTRING};

enum Statetype
handleNormalState(int c) {
    enum Statetype state;
    if (c=='/' && getchar()=='*') {
        state = INCOMMENT;
        putchar(' ');
        return state;
    }
    if (c=='\'') {
        state = INCHAR;
        putchar(c);
        return state;
    }
    if (c=='"') {
        state = INSTRING;
        putchar(c);
        return state;
    }
    if (c=='\\') {
        int ch = getchar();
        state = NORMAL;
        if (ch=='n') {
            printf("\n");
            return state;
        }
        else {
            putchar(c);
            putchar(ch);
            return state;
        }
    }
    putchar(c);
    state = NORMAL;
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
        return state;
    }
    if (c=='\\') {
        int ch = getchar();
        if (ch=='n') {
            printf("\n");
        }
        else {
            putchar(c);
            putchar(ch);
        }
        state = INCHAR;
        return state;
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
        return state;
    }
    if (c=='\\') {
        int ch = getchar();
        if (ch=='n') {
            printf("\n");
        }
        else {
            putchar(c);
            putchar(ch);
        }
        state = INSTRING;
        return state;
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
                state = handleNormalState(c);
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