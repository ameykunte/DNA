#include "headers.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

void red_flag_check(char *input)
{

	int std_in_saved = dup(0);
	int std_out_saved = dup(1);
	char input_copy[1024];
	strcpy(input_copy, input);
	char *ret;
	char *input_file;
	char *input_file_name = NULL;
	char *output_file = NULL;
	char *output_append_file = NULL;

	input_file = strstr(input_copy, "<");
	if (input_file != NULL)
	{

		input_file_name = strtok(input_file + 1, " \t\r\n\v\f");
		int fd_input = open(input_file_name, O_RDONLY);

		if (fd_input < 0)
		{
			perror("Failed to open input file.");
			exit(1);
		}

		if (dup2(fd_input, STDIN_FILENO) < 0)
		{
			dup2(std_in_saved, STDIN_FILENO);
		}
		close(fd_input);
	}
	else
	{
		input_file_name = NULL;
		dup2(std_in_saved, STDIN_FILENO);
	}

	strcpy(input_copy, input);
	ret = strstr(input_copy, ">>");
	if (ret == NULL)
	{
		output_append_file = NULL;
		ret = strstr(input_copy, ">");
		if (ret != NULL)
		{
			output_file = strtok(ret + 1, " \t\r\n\v\f");
			int fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

			if (fd_out < 0)
			{
				perror("Failed to create/open output file.");
				exit(1);
			}

			if (dup2(fd_out, STDOUT_FILENO) < 0)
			{
				dup2(std_out_saved, STDOUT_FILENO);
			}
			close(fd_out);
		}
		else
		{
			output_file = NULL;
			dup2(std_out_saved, STDOUT_FILENO);
		}
	}
	else
	{
		output_append_file = strtok(ret + 2, " \t\r\n\v\f");
		int fd_out = open(output_append_file, O_APPEND | O_WRONLY | O_CREAT, 0644);

		output_file = NULL;

		if (fd_out < 0)
		{
			perror("Failed to create/open output file.");
			exit(1);
		}

		if (dup2(fd_out, STDOUT_FILENO) < 0)
		{
			dup2(std_out_saved, STDOUT_FILENO);
		}
		close(fd_out);
	}
}