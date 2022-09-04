#define _GNU_SOURCE
#include "builtin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define DELIM " \t\r\a\n"
#define BUF_SIZE 64

void launch_process(char **args) {
  pid_t pid = fork();
  int wstatus = 0;
  if (pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  } else if (pid == 0) {
    execvp(args[0], args);
  } else if (pid > 0) {
    do {
      wstatus = waitpid(pid, &wstatus, WUNTRACED);
    } while (!WEXITSTATUS(wstatus) && !WIFSIGNALED(wstatus));
  }
}

char *read_line() {
  char *line = NULL;
  size_t buf_size = 0;
  if (getline(&line, &buf_size, stdin) == -1) {
    exit(EXIT_FAILURE);
  }
  return line;
}

char **parse(char *line) {
  char *token = NULL;
  char **args = malloc(BUF_SIZE * sizeof(char *));
  int pos = 0;

  token = strtok(line, DELIM);
  while (token) {
    args[pos] = token;
    pos++;
    token = strtok(NULL, DELIM);
  }
  args[pos] = NULL;
  return args;
}

void exec(char **args) {
  int builtin_size = (int)sizeof(builtin) / sizeof(char *);
  for (int i = 0; i < builtin_size; ++i) {
    if (strcmp(builtin[i], args[0]) == 0) {
      (*builtin_func[i])(args);
      printf("\n");
    }
  }

  // if it is not in the builtins,
  // after invoke the execvp, the shell will be terminated.
  // so we need to fork.
  launch_process(args);
  printf("\n");
}

void loop() {
  while (1) {
    char *line = NULL;
    char **args = NULL;

    printf("> ");
    // read line
    line = read_line();
    // parse
    args = parse(line);

    // exec
    exec(args);
  }
}

void print() {
  system("cat ysh.cat");
  printf("\n");
}

int main() {
  print();
  loop();
  return 0;
}