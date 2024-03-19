
#include "headers.h"
#include "prompt.h"
char home_dir[1024];

char *get_homedir()
{

	getcwd(home_dir, 1024);
	return home_dir;
}

void prompt()
{

	char HOSTNAME[1024], USERNAME[1024];
	gethostname(HOSTNAME, sizeof(HOSTNAME));
	getlogin_r(USERNAME, sizeof(USERNAME));
	color_reset();

	bold_green();
	printf("<%s@", USERNAME);
	printf("%s:", HOSTNAME);
	color_reset();

	char curr_dir[1024];
	getcwd(curr_dir, 1024);
	bold_cyan();
	int cmp = strcmp(home_dir, curr_dir);

	if (cmp == 0)
	{
		printf("~>");
	}

	else if (cmp > 0)
	{
		printf(" %s>", curr_dir);
	}

	else if (cmp < 0)
	{
		printf("~");
		int i = strlen(home_dir);
		while (curr_dir[i] != '\0')
		{
			printf("%c", curr_dir[i]);
			i++;
		}
		printf(">");
	}
	color_reset();
}

void bold_green()
{
	printf("\033[1;32m");
}

void bold_cyan()
{
	printf("\033[1;36m");
}

void color_reset()
{
	printf("\033[0m");
}
void red()
{
	printf("\033[0;31m");
}
