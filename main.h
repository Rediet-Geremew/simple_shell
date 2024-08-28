#ifndef MAIN_H
#define MAIN_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int execute_command(char *command, int *status);

#endif /* MAIN_H */
