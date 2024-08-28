#include "main.h"

/**
 * main - Entry point of the shell program.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line arguments.
 *
 * Return: 0 on success.
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int status = 0;
	(void)argc;
	(void)argv;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, "$ ", 2);
		}
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			if (feof(stdin))
			{
				break;
			}
			perror("getline");
			exit(EXIT_FAILURE);
		}
		line[read - 1] = '\0';
		if (execute_command(line, &status) == -1)
		{
			perror("execute_command");
			exit(EXIT_FAILURE);
		}
	}
	free(line);
	return (status);
}

/**
 * execute_command - Executes a command from the shell.
 * @command: The command to execute.
 * @status: Pointer to store the exit status.
 *
 * Return: 0 on success, -1 on failure.
 */
int execute_command(char *command, int *status)
{
	pid_t pid;
	int status_code;
	char *argv[2];

	argv[0] = command;
	argv[1] = NULL;

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
		waitpid(pid, &status_code, 0);
		if (WIFEXITED(status_code))
		{
			*status = WEXITSTATUS(status_code);
		}
	}

	return (0);
}
