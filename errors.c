#include "main.h"

/**
 * _errnumber - get current error num and increment it by 1
 * @update: 1 to update errnumber, 0 to not update
 * Return: current error number
 */
int _errnumber(int update)
{
	static int errnumber = 1;
	int temp = errnumber;

	errnumber += update;

	return (temp);
}

/**
 * print_error - print an error to stderr
 * @command: The command where the error happend
 * @error: content of error message
 * Return: length of printed error
 */
int print_error(const char *command, const char *error)
{
	char *err = NULL, *temp = NULL, *temp_num = NULL;
	size_t length;
	int res = 0;

	temp = concat(prog_args(NULL)[0], ": ");
	temp_num = ultos(_errnumber(0));
	err = concat(temp, temp_num);
	free(temp);
	free(temp_num);

	temp = err;
	err = concat(temp, ": ");
	free(temp);

	temp = err;
	err = concat(temp, command);
	free(temp);

	temp = err;
	err = concat(temp, ": ");
	free(temp);

	temp = err;
	err = concat(temp, error);
	free(temp);

	temp = err;
	err = concat(temp, "\n");
	free(temp);

	length = len(err);
	res = write(STDERR_FILENO, err, length);
	free(err);
	return (res);
}
