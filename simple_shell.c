#include "simple_shell.h"

extern char **environ;

/**
 * main - entry point of the simple shell program
 *
 * Return: 0 on success
 */
int main(void)
{
	char *command;

	while (1)
	{
		prompt();
		command = read_line();
		if (command == NULL)
		{
			if (feof(stdin))
			{
				free(command);
				exit(EXIT_SUCCESS);
			}
			else
			{
				perror("read_line");
				continue;
			}
		}
		if (strlen(command) > 0)
		{
			execute_command(command);
		}
		free(command);
	}

	return (0);
}

/**
 * prompt - display the shell prompt
 */
void prompt(void)
{
	write(STDOUT_FILENO, "#cisfun$ ", 9);
}

/**
 * read_line - read input from user
 *
 * Return: line of input, or NULL
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

/**
 * execute_command - Executes a command from the shell
 * @command: the command to execute
 */
void execute_command(char *command)
{
	pid_t pid;
	int status;
	char *argv[2];

	argv[0] = command;
	argv[1] = NULL;

	pid = fork();
	if (pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			perror(argv[0]);
			_exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}
