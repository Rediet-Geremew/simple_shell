#include "simple_shell.h"

/**
 * main - entry point of the simple shell program
 *
 * Return: 0 on success
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, "#cisfun$ ", 9);
		}
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			if (feof(stdin))
			{
				write(STDOUT_FILENO, "\n", 1);
				free(line);
				exit(EXIT_SUCCESS);
			}
			perror("getline");
			exit(EXIT_FAILURE);
		}
		if (line[read - 1] == '\n')
		{
			line[read - 1] = '\0';
		}
		if (execute_command(line) == -1)
		{
			perror("execute_command");
		}
	}
	free(line);
	return (status);
}

/**
 * execute_command - Executes a command from the shell
 * @command: the command to execute
 *
 * Return: 0 on success, -1 on failure
 */
int execute_command(char *command)
{
	pid_t pid;
	int status;
	char *argv[2];

	argv[0] = command;
	argv[1] = NULL;

	if (command[0] == '\0')
	{
		return (0);
	}
	pid = fork();
	if (pid == -1)
	{
		return (-1);
	}
	if (pid == 0)
	{
		if (execve(command, argv, NULL) == -1)
		{
			perror(command);
			_exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}

	return (0);
}
