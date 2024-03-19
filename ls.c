#include "headers.h"
#include <time.h>
#include <pwd.h>
#include <grp.h>

void list_items(char *filename, char *dirname);

int flag_check(char **list, int cnt);

int ls_basic(char **list, int i, char *home_dir)
{
	char ch;
	char dirname[1024] = "";
	if (list[1] == NULL)
	{

		getcwd(dirname, sizeof(dirname));
	}
	else
	{
		char path[1024];
		ch = list[i][0];
		strcpy(path, list[i]);

		if (path[0] == '~')
		{
			if (strlen(path) == 1)
			{
				strcat(dirname, home_dir);
			}
			else
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

				strcat(dirname, home_dir);

				strcat(dirname, buf);
			}
		}
		else
			strcat(dirname, path);
	}

	DIR *pointer = NULL;
	struct dirent *box;
	pointer = opendir(dirname);
	if (pointer == NULL)
	{
		printf("%s: ", dirname);
		printf("Cannot open Dir!\n");
		printf("\n**********************************************************************************\n\n");
		return -1;
		exit(1);
	}
	printf("%s:\n", dirname);

	box = readdir(pointer);
	while (box != NULL)
	{
		char file_name[100] = "";
		strcat(file_name, box->d_name);
		ch = file_name[0];
		char file_path[1024];
		strcpy(file_path, dirname);
		strcat(file_path, "/");
		strcat(file_path, file_name);

		struct stat file;
		stat(file_path, &file);

		int p = file.st_mode;
		if (ch != '.')
		{

			if (S_ISDIR(file.st_mode))
			{
				bold_cyan();
				printf("%s\n", file_name);
				color_reset();
			}
			else if (file.st_mode & S_IXUSR)
			{
				red();
				printf("%s\n", file_name);
				color_reset();
			}
			else
			{
				printf("%s\n", file_name);
			}
		}
		box = readdir(pointer);
	}
	printf("**********************************************************************************\n\n");

	return 0;
}

int ls_a(char **list, int i, char *home_dir)
{

	char ch;
	char dirname[1024] = "";
	if (list[2] == NULL)
	{

		getcwd(dirname, sizeof(dirname));
	}
	else
	{
		char path[1024];
		ch = list[i][0];
		strcpy(path, list[i]);

		if (path[0] == '~')
		{
			if (strlen(path) == 1)
			{
				strcat(dirname, home_dir);
			}
			else
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

				strcat(dirname, home_dir);

				strcat(dirname, buf);
			}
		}
		else
			strcat(dirname, path);
	}

	DIR *pointer = NULL;
	struct dirent *box;
	pointer = opendir(dirname);
	if (pointer == NULL)
	{
		printf("%s: ", dirname);
		printf("Cannot open Dir!\n");
		printf("\n**********************************************************************************\n\n");
		return -1;
		exit(1);
	}
	printf("%s:\n", dirname);

	box = readdir(pointer);
	while (box != NULL)
	{
		char file_name[100] = "";
		strcat(file_name, box->d_name);

		ch = file_name[0];
		char file_path[1024];
		strcpy(file_path, dirname);
		strcat(file_path, "/");
		strcat(file_path, file_name);

		struct stat file;
		stat(file_path, &file);

		int p = file.st_mode;

		if (S_ISDIR(file.st_mode))
		{
			bold_cyan();
			printf("%s\n", file_name);
			color_reset();
		}
		else if (file.st_mode & S_IXUSR)
		{
			red();
			printf("%s\n", file_name);
			color_reset();
		}
		else
		{
			printf("%s\n", file_name);
		}

		box = readdir(pointer);
	}
	printf("**********************************************************************************\n\n");

	return 0;
}

int ls_l(char **list, int i, char *home_dir)
{

	char ch;
	char dirname[1024] = "";

	if (list[2] == NULL)
	{

		getcwd(dirname, sizeof(dirname));
	}
	else
	{

		char path[1024];
		ch = list[i][0];
		strcpy(path, list[i]);

		if (path[0] == '~')
		{
			if (strlen(path) == 1)
			{
				strcat(dirname, home_dir);
			}
			else
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

				strcat(dirname, home_dir);

				strcat(dirname, buf);
			}
		}
		else
		{

			strcat(dirname, path);
		}
	}

	/*
	ls -l displays the following information for each file in the given directory

	file mode
	number of links
	owner name
	group name
	number of bytes in the file
	abbreviated month
	day-of-month file was last modified
	hour file last modified
	minute file last modified
	and the pathname
	*/

	DIR *pointer = NULL;
	struct dirent *box;
	pointer = opendir(dirname);
	if (pointer == NULL)
	{
		printf("%s: ", dirname);
		printf("Cannot open Dir!\n");
		printf("\n**********************************************************************************\n\n");
		return -1;
		exit(1);
	}
	printf("%s:\n", dirname);

	box = readdir(pointer);
	while (box != NULL)
	{

		char file_name[100] = "";
		strcat(file_name, box->d_name);

		ch = file_name[0];

		if (ch != '.')
		{

			list_items(file_name, dirname);
		}

		box = readdir(pointer);
	}

	printf("**********************************************************************************\n\n");

	return 0;
}

int ls_al(char **list, int i, char *home_dir)
{

	char ch;
	char dirname[1024] = "";
	if (list[2] == NULL)
	{

		getcwd(dirname, sizeof(dirname));
	}
	else if (list[1][0] == list[2][0])
	{
		getcwd(dirname, sizeof(dirname));
	}
	else
	{
		char path[1024];
		ch = list[i][0];
		strcpy(path, list[i]);

		if (path[0] == '~')
		{
			if (strlen(path) == 1)
			{
				strcat(dirname, home_dir);
			}
			else
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

				strcat(dirname, home_dir);

				strcat(dirname, buf);
			}
		}
		else
			strcat(dirname, path);
	}

	/*
	ls -l displays the following information for each file in the given directory

	file mode
	number of links
	owner name
	group name
	number of bytes in the file
	abbreviated month
	day-of-month file was last modified
	hour file last modified
	minute file last modified
	and the pathname
	*/

	DIR *pointer = NULL;
	struct dirent *box;
	pointer = opendir(dirname);
	if (pointer == NULL)
	{
		printf("%s: ", dirname);
		printf("Cannot open Dir!\n");
		printf("\n**********************************************************************************\n\n");
		return -1;
		exit(1);
	}
	printf("%s:\n", dirname);

	box = readdir(pointer);
	while (box != NULL)
	{
		char file_name[100] = "";
		strcat(file_name, box->d_name);
		ch = file_name[0];

		list_items(file_name, dirname);

		box = readdir(pointer);
	}
	printf("**********************************************************************************\n\n");

	return 0;
}

void list_items(char *file_name, char *dirname)
{
	char file_path[1024];
	strcpy(file_path, dirname);
	strcat(file_path, "/");
	strcat(file_path, file_name);

	struct stat file;
	stat(file_path, &file);

	int p = file.st_mode;

	int others = p % 8;
	p = p / 8;
	int group = p % 8;
	p = p / 8;
	int user = p % 8;

	int user_read = (user & 4) >> 2;
	int user_write = (user & 2) >> 1;
	int user_ex = user & 1;
	int group_read = (group & 4) >> 2;
	int group_write = (group & 2) >> 1;
	int group_ex = group & 1;
	int others_read = (others & 4) >> 2;
	int others_write = (others & 2) >> 1;
	int others_ex = others & 1;
	struct stat dir_check;
	int d_check = stat(file_path, &dir_check) == 0 && S_ISDIR(dir_check.st_mode);

	char permisions[11];
	permisions[0] = (d_check == 1) ? 'd' : '-';
	permisions[1] = (user_read == 1) ? 'r' : '-';
	permisions[2] = (user_write == 1) ? 'w' : '-';
	permisions[3] = (user_ex == 1) ? 'x' : '-';
	permisions[4] = (group_read == 1) ? 'r' : '-';
	permisions[5] = (group_write == 1) ? 'w' : '-';
	permisions[6] = (group_ex == 1) ? 'x' : '-';
	permisions[7] = (others_read == 1) ? 'r' : '-';
	permisions[8] = (others_write == 1) ? 'w' : '-';
	permisions[9] = (others_ex == 1) ? 'x' : '-';
	permisions[10] = '\0';

	char time[10], date[10], month[10];
	strftime(time, 10, "%H:%M", localtime(&file.st_mtime));
	strftime(date, 10, "%d", localtime(&file.st_mtime));
	strftime(month, 10, "%b ", localtime(&file.st_mtime));

	struct passwd *pw = getpwuid(file.st_uid);
	struct group *gr = getgrgid(file.st_gid);

	printf("%s\t%hu\t%s\t%s\t%lld\t\t%s\t%s\t%s\t", permisions, file.st_nlink, pw->pw_name, gr->gr_name, file.st_size, month, date, time);
	if (permisions[0] == 'd')
	{
		bold_cyan();
		printf("%s\n", file_name);
		color_reset();
	}
	else if (permisions[3] == 'x')
	{
		red();
		printf("%s\n", file_name);
		color_reset();
	}
	else
	{
		printf("%s\n", file_name);
	}
}

void ls_call(char **list, int cnt, char *home_dir)
{
	char **dirs;
	dirs = list;

	if (cnt == 1)
		ls_basic(dirs, 0, home_dir);

	int flag = flag_check(list, cnt);
	if (flag == 1)
	{
		if (cnt == 2)
			ls_a(dirs, 0, home_dir);
		else
		{

			for (int i = 1; i < cnt; i++)
			{
				if (dirs[i][0] != '-')
					ls_a(dirs, i, home_dir);
			}
		}
	}
	else if (flag == 2)
		for (int i = 1; i < cnt; i++)
		{
			if (cnt == 2)
				ls_l(dirs, 0, home_dir);

			else
			{
				if (dirs[i][0] != '-')
					ls_l(dirs, i, home_dir);
			}
		}
	else if (flag == 3)
	{
		if (cnt == 3 && (dirs[1][0] == dirs[2][0]))
			ls_al(dirs, 0, home_dir);
		else
		{
			for (int i = 1; i < cnt; i++)
			{
				if (cnt == 2)
					ls_al(dirs, 0, home_dir);

				else
				{
					if (dirs[i][0] != '-')
						ls_al(dirs, i, home_dir);
				}
			}
		}
	}
	else if (flag == 4)
		for (int i = 1; i < cnt; i++)
		{
			ls_basic(dirs, i, home_dir);
		}
}

int flag_check(char **list, int cnt)
{
	char flag[5];
	int j = 0;
	for (int i = 1; i < cnt; i++)
	{
		if (list[i][0] == '-')
		{
			if ((strcmp(list[i], "-la") == 0) || (strcmp(list[i], "-al") == 0))
			{

				flag[j] = 'a';
				j++;
				flag[j] = 'l';
				j++;
			}
			else if (list[i][1] == 'l')
			{
				flag[j] = 'l';
				j++;
			}
			else if (list[i][1] == 'a')
			{
				flag[j] = 'a';
				j++;
			}
		}
	}
	flag[j] = '\0';

	if (strcmp(flag, "a") == 0)
		return 1;
	else if (strcmp(flag, "l") == 0)
		return 2;
	else if ((strcmp(flag, "la") == 0) || (strcmp(flag, "al") == 0))
		return 3;
	else if (strcmp(flag, "") == 0)
		return 4;
	else
	{
		printf("Wrong flag: Check again!\n");

		return -1;
	}
}
