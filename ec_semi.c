#include "headers.h"
char *cmd[1000];

char **extract_semicolon(char *input, int *cnt_semi)
{

	cmd[0] = strtok(input, ";");

	long long int i = 0, j = 0;
	while (cmd[i] != NULL)
	{

		i++;
		cmd[i] = strtok(NULL, ";");
	}

	return cmd;
}