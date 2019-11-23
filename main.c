#include <stdio.h>
#include "scanner.h"
#include "yap.h"

void printTokens() {
    yyin = fopen("C:\\Workspace\\Project\\flex-practice\\test.c", "rb+");
    int tok, count = 1;
    while ((tok = yylex()) != 0) {
        printf("%d [%d:%s]\n", count++, tok, yytext[0] == '\n' ? "\\n" : yytext);
    }
    fclose(yyin);
}

int main() {
//    printTokens();
    yyin = fopen("C:\\Workspace\\Project\\flex-practice\\test.c", "rb+");

    advance();
    program();

    fclose(yyin);
    return 0;
}