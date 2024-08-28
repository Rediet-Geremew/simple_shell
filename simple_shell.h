#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int execute_command(char *command);

#endif
