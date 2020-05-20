#include <stdio.h>

void printParenthesis(char *str, size_t n_parenthesis)
{
    if (0 == n_parenthesis)
    {
        printf("%s", str);

        return;
    }

    printf("(");
    printParenthesis(str, n_parenthesis - 1);
    printf(")");
}

int main(int argc, char const *argv[])
{
    printParenthesis("hello", 0);
    return 0;
}
