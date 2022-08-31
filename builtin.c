#define _GNU_SOURCE
#include "builtin.h"
#include <stdio.h>
#include <unistd.h>

int cd(char **arg) {
  int argc = (int) sizeof(arg) / sizeof(char *);

  if (argc > 2) {
    fprintf(stderr, "\n");
  } else if (chdir(arg[1]) != 0) {
    fprintf(stderr, "cd: no such file or directory: %s", arg[1]);
    return 1;
  }
  return 1;
}

int echo(char **args) {
  // TODO handling error.
  printf("%s\n", args[1]);
  return 0;
}

int pwd(char **args) {
  // TODO
  printf("%s\n", get_current_dir_name());
}