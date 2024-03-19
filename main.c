#include "headers.h"
#include "prompt.h"
#include "ec.h"
#include "cd.h"
int cnt = 0;
int cnt_semi = 0;

void CTRL_C(int SIG);
int main()
{

	CHILDPID = -1;
	SHELLID = 0;

	int std_in_saved = dup(0);
	int std_out_saved = dup(1);
	dup2(std_in_saved, STDIN_FILENO);
	dup2(std_out_saved, STDOUT_FILENO);

	char *home_dir = get_homedir();

	signal(SIGINT, CTRL_C);
	SHELLID = getpid();

	while (1)
	{
		cnt_semi = 0;
		char *input;
		size_t size = 0;
		prompt();

		getline(&input, &size, stdin);

		update_hist(input, strlen(input));

		if (strlen(input) < 1)
			continue;
		if (input[0] == '\n')
			continue;
		if (strlen(input) == 1 && input[0] == ' ')
			continue;

		for (int i = 0; i < strlen(input); i++)
		{
			if (input[i] == ';')
				cnt_semi++;
		}

		if (cnt_semi != 0)
		{
			char **cmd = extract_semicolon(input, &cnt_semi);

			for (int j = 0; cmd[j] != NULL; j++)
			{

				cnt = 0;

				int ret = piping(cmd[j], home_dir);
				if (ret == 1)
					continue;

				red_flag_check(cmd[j]);
				char **list;

				list = extract_command(cmd[j], &cnt);
				if (cnt == 0)
				{

					continue;
				}
				execute_command(list, home_dir, cnt, cmd[j]);

				dup2(std_in_saved, STDIN_FILENO);
				dup2(std_out_saved, STDOUT_FILENO);
			}
		}
		else
		{

			char input_copy[1024];
			strcpy(input_copy, input);
			char **list;
			cnt = 0;
			list = extract_command(input_copy, &cnt);

			if (cnt == 1)
				continue;

			int ret = piping(input, home_dir);
			if (ret == 1)
				continue;

			red_flag_check(input);

			if (cnt == 1)
				continue;

			execute_command(list, home_dir, cnt, input);

			dup2(std_in_saved, STDIN_FILENO);
			dup2(std_out_saved, STDOUT_FILENO);
		}
	}
}

void CTRL_C(int SIG)
{
	int pid = getpid();
	if (pid != SHELLID)
	{
		return;
	}
	if (CHILDPID != -1)
	{
		kill(CHILDPID, SIGINT);
		signal(SIGINT, CTRL_C);
	}
}
