#include "headers.h"

char *cd_list[1000];
int cd_change = 1;

int cd_call(char **list, char *input, char *home_dir)
{

	cd_list[0] = (char *)malloc(200 * sizeof(char));
	strcpy(cd_list[0], home_dir);
	cd_list[0][strlen(home_dir)] = '\0';

	if ((list[1] == NULL) || (strcmp(list[1], "~") == 0))
	{

		if (chdir(home_dir) != 0)
			return -1;

		cd_change++;
		char cwd[1024];
		getcwd(cwd, 1024);
		cd_list[cd_change] = (char *)malloc(200 * sizeof(char));
		strcpy(cd_list[cd_change], cwd);
		cd_list[cd_change][strlen(cwd)] = '\0';

		return 0;
	}

	if ((strcmp(list[1], "-") == 0))
	{

		if (cd_change == 1)
		{

			char cwd[1024];
			getcwd(cwd, 1024);
			printf("%s\n", cwd);
		}
		else
		{

			char *copy1_of_last_dir;
			copy1_of_last_dir = (char *)malloc(200 * sizeof(char));
			strcpy(copy1_of_last_dir, cd_list[cd_change - 1]);

			char *temp_dir_name;
			temp_dir_name = (char *)malloc(200 * sizeof(char));

			if (strstr(copy1_of_last_dir, home_dir) != NULL)
			{

				temp_dir_name[0] = '~';
				int k = 1;
				for (int j = strlen(home_dir); j < strlen(cd_list[cd_change - 1]); j++)
				{
					temp_dir_name[k] = cd_list[cd_change - 1][j];
					k++;
				}
				temp_dir_name[k] = '\0';
				printf("%s\n", temp_dir_name);
				chdir(cd_list[cd_change - 1]);
			}
			else
			{
				strcpy(temp_dir_name, cd_list[cd_change - 1]);
				temp_dir_name[strlen(cd_list[cd_change - 1])] = '\0';
				printf("%s\n", temp_dir_name);
				chdir(cd_list[cd_change - 1]);
			}

			cd_change++;
			char cwd[1024];
			getcwd(cwd, 1024);
			cd_list[cd_change] = (char *)malloc(200 * sizeof(char));
			strcpy(cd_list[cd_change], cwd);
			cd_list[cd_change][strlen(cwd)] = '\0';

			/*
			if (cd_list[cd_change - 1][0] == '~')
			{

				int i = 1, j = 0;
				char buf[1024];
				while (cd_list[cd_change - 1][i] != '\0')
				{
					buf[j] = cd_list[cd_change - 1][i];
					j++;
					i++;
				}
				buf[j] = '\0';


				char dirname[1024] = "";

				strcat(dirname, home_dir);

				strcat(dirname, buf);
				printf("%s\n", dirname);
				if (chdir(dirname) != 0)
					return -1;
				cd_change++;
				cd_list[cd_change] = (char*)malloc(200 * sizeof(char));
				strcpy(cd_list[cd_change], cd_list[cd_change - 2]);
				cd_list[cd_change][strlen(cd_list[cd_change - 2])] = '\0';
			}
			else
			{

				if (chdir(cd_list[cd_change - 1]) != 0)
					return -1;
				cd_change++;
				cd_list[cd_change] = (char*)malloc(200 * sizeof(char));
				strcpy(cd_list[cd_change], cd_list[cd_change - 2]);
				cd_list[cd_change][strlen(cd_list[cd_change - 2])] = '\0';

			}
			*/
		}

		return 0;
	}

	char path[1024];
	char ch = list[1][0];
	strcpy(path, list[1]);

	if (path[0] == '~')
	{

		int i = 1, j = 0;
		char buf[1024];
		while (path[i] != '\0')
		{
			buf[j] = path[i];
			j++;
			i++;
		}
		buf[j] = '\0';

		char dirname[1024] = "";

		strcat(dirname, home_dir);

		strcat(dirname, buf);

		if (chdir(dirname) != 0)
			return -1;

		cd_change++;
		char cwd[1024];
		getcwd(cwd, 1024);
		cd_list[cd_change] = (char *)malloc(200 * sizeof(char));
		strcpy(cd_list[cd_change], cwd);
		cd_list[cd_change][strlen(cwd)] = '\0';
	}

	else if (strcmp(list[1], "/") == 0)
	{

		if (chdir("/") != 0)
			return -1;
		cd_change++;
		char cwd[1024];
		getcwd(cwd, 1024);
		cd_list[cd_change] = (char *)malloc(200 * sizeof(char));
		strcpy(cd_list[cd_change], cwd);
		cd_list[cd_change][strlen(cwd)] = '\0';
	}

	else
	{

		if (chdir(list[1]) != 0)
			return -1;

		cd_change++;
		char cwd[1024];
		getcwd(cwd, 1024);
		cd_list[cd_change] = (char *)malloc(200 * sizeof(char));
		strcpy(cd_list[cd_change], cwd);
		cd_list[cd_change][strlen(cwd)] = '\0';
	}

	return 0;
}