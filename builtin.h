#ifndef BUILTIN_H
#define BUILTIN_H

#include <stdio.h>
#include <unistd.h>

static char *builtin[] = {"cd", "echo", "pwd"};


int cd(char **args);

int echo(char **args);

int pwd(char **args);

static int (*builtin_func[])() = {
  &cd, &echo, &pwd
};
#endif