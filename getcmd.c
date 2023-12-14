#include "main.h"

/**
 * getcmd - gets a cmd object from a command string
 * @command: command string
 * @temp: temp to free
 * Return: a cmd structure
 */
cmd *getcmd(const char *command, char **temp)
{
	cmd *res = NULL;
	char *pathname = NULL;

	if (command == NULL)
		return (NULL);
	res = find_builtin(command);
	if (res != NULL)
		return (res);
	if (is_path(command))
		pathname = copy(command);
	else
	{
		pathname = find_in_PATH(command, temp);
		if (pathname == NULL || pathname[0] == '\0')
		{
			if (pathname == NULL)
				print_error(command, "Permission denied");
			else if (pathname[0] == '\0')
			{
				print_error(command, "not found");
				free(pathname);
			}
			exit_status(SET_VARIABLE, 127);
			return (NULL);
		}
	}

	if (!can_access(command, pathname))
	{
		free(pathname);
		return (NULL);
	}
	res = make_execmd(pathname);
	free(pathname);
	return (res);
}
