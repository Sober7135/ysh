#ifndef BUILTIN_H
#define BUILTIN_H

#include <stdio.h>
#include <unistd.h>

static char *builtin[] = {"cd", "echo", "pwd", "exit"};

int ysh_cd(char **args);

int ysh_echo(char **args);

int ysh_pwd(char **args);

int ysh_exit(char **args);

static int (*builtin_func[])(char **args) = {&ysh_cd, &ysh_echo, &ysh_pwd, &ysh_exit};
#endif