#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

void execute_command(char *command);
char *read_line(void);
void prompt(void);

#endif
