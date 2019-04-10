#ifndef MACRO_H
#define MACRO_H

#define _WARNING_FEW_ARG_(COMMAND)                          \
{                                                           \
    printf("Too few arguments to command %s.\n", COMMAND);  \
    return;                                                 \
}

#define _WARNING_MANY_ARG_(COMMAND)                         \
{                                                           \
    printf("Too many arguments to command %s.\n", COMMAND); \
    return;                                                 \
}

#define _INPUT_STRING_(str, MaxSize)   \
{                                       \
    fflush(stdin);                      \
    fgets (str, MaxSize + 1, stdin);    \
    str[strlen(str) - 1] = '\0';        \
}


#endif
