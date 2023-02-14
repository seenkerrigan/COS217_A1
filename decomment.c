#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

enum Statetype {NORMAL, INCOMMENT, INCHAR, INSTRING};

enum Statetype
handleNormalState(int c) {
    enum Statetype state;
    if (c=='/') {
        int ch = getchar();
        if (ch=='*') {
        state = INCOMMENT;
        putchar(' ');
        return state;
        }
        else {
            putchar(c);
            putchar(ch);
            if (ch=='\'') {
                state = INCHAR;
                return state;
            }
            if (ch=='"') {
                state = INSTRING;
                return state;
            }
            state = NORMAL;
            return state;
        }
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
    if (c=='\n') {
        printf("\n");
        state = NORMAL;
    }
    /*
    if (c=='\\') {
        int ch = getchar();
        state = NORMAL;
        if (ch=='n') {
            int char3 = getchar();
            if (char3==' ') printf("\n");
            else {
                putchar(c);
                putchar(ch);
                handleNormalState(char3);
            }
            return state;
        }
        else {
            handleNormalState(ch);
            /*
            putchar(c);
            if (ch=='\'') {
                state = INCHAR;
                putchar(ch);
                return state;
            }
            if (ch=='"') {
                state = INSTRING;
                putchar(ch);
                return state;
            }
            return state;
        }
        */
    putchar(c);
    state = NORMAL;
    return state;
}

enum Statetype
handleCommentState(int c) {
    enum Statetype state;
    if (c=='*') {
        int ch = getchar();
        if (ch=='/') {
            state = NORMAL;
            return state;
        }
        else handleCommentState(ch);
    }
    if (c=='\n') printf("\n");
    state = INCOMMENT;
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
        if (ch==EOF) {
            putchar(c);
            return NORMAL;
        }
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
        if (ch==EOF) {
            putchar(c);
            return NORMAL;
        }
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
    if (state==INCOMMENT) {
        fprintf(stderr, "Error: line BLANK: unterminated comment");
        return EXIT_FAILURE;
    }
    return 0;
}