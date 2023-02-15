#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* names of DFA states */
enum Statetype {NORMAL, INCOMMENT, INCHAR, INSTRING};
/* int to keep track of what line a comment starts on */
int count = 1;
/* int to keep track of lines in a comment*/
int countComment = 0;

/* Normal DFA state. Takes a char as an int c and checks if a String,
char, or comment begins. Prints char c and returns state DFA is in 
after char c is read. */
enum Statetype
handleNormalState(int c) {
    enum Statetype state;
    if (c=='/') {
        int ch = getchar();
        if (ch==EOF) {
            putchar(c);
            return NORMAL;
        }
        if (ch=='*') {
        state = INCOMMENT;
        putchar(' ');
        return state;
        }
        else {
            putchar(c);
            return handleNormalState(ch);
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
    if (c=='\n') count++;
    putchar(c);
    state = NORMAL;
    return state;
}

/* represents DFA state of being inside a comment. Takes char input c
as an int and checks to see if char c causes comment to end. Returns
next state of DFA. */
enum Statetype
handleCommentState(int c) {
    enum Statetype state;
    if (c=='*') {
        int ch = getchar();
        if (ch==EOF) {
            return INCOMMENT;
        }
        if (ch=='/') {
            count += countComment;
            countComment = 0;
            state = NORMAL;
            return state;
        }
        else {
            return handleCommentState(ch);
        }
    }
    if (c=='\n') {
        countComment++;
        printf("\n");
    }
    state = INCOMMENT;
    return state;
}

/* Represents DFA state of being in a char. Takes char input c as an int
and checks to see if c ends the char. Prints out c and returns next
state of DFA. */
enum Statetype
handleCharState(int c) {
    enum Statetype state;
    if (c=='\'') {
        state = NORMAL;
        putchar(c);
        return state;
    }
    if (c=='\n') {
        count++;
        printf("\n");
        state = INCHAR;
        return state;
    }
    /* Checking for backslash removing affect of ' or \ characters */
    if (c=='\\') {
        int ch = getchar();
        if (ch==EOF) {
            putchar(c);
            return NORMAL;
        }
        if (ch=='\'') {
            putchar(c);
            putchar(ch);
            state = INCHAR;
            return state;
        }
        if (ch=='\\') {
            putchar(c);
            putchar(ch);
            state = INCHAR;
            return state;
        }
        putchar(c);
        return handleCharState(ch);
    }
    state = INCHAR;
    putchar(c);
    return state;
}

/* Represents DFA state of being in a String. Takes char input c as an
int and checks if c ends the String. Prints c and returns next DFA
state. */
enum Statetype
handleStringState(int c) {
    enum Statetype state;
    if (c=='"') {
        state = NORMAL;
        putchar(c);
        return state;
    }
    if (c=='\n') {
        count++;
        printf("\n");
        state = INSTRING;
        return state;
    }
    /* Checking for backslash removing affect of " or \ characters */
    if (c=='\\') {
        int ch = getchar();
        if (ch==EOF) {
            putchar(c);
            return NORMAL;
        }
        if (ch=='"') {
            putchar(c);
            putchar(ch);
            state = INSTRING;
            return state;
        }
        if (ch=='\\') {
            putchar(c);
            putchar(ch);
            state = INSTRING;
            return state;
        }
        putchar(c);
        return handleStringState(ch);
    }
    putchar(c);
    state = INSTRING; 
    return state;
}

/* Starts DFA at Normal state and reads in chars as an int c until
end of file is reached. Calls methods representing DFA states as
necessary. When end of file is reached, checks if file has an
unterminated comment and prints to stderr if this is the case with
the line number of the unterminated comment. */
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

        fprintf(stderr, "Error: line %d: unterminated comment\n", count);
        return EXIT_FAILURE;
    }
    return 0;
}