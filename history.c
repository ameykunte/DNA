#include "headers.h"
#include <stdio.h>
#include<stdio.h>
#include<string.h>

int p = 0, size[22], fill = 0;
char his[20][105];

void update_hist(char * str, int n)
{
	if (n < 1)
		return;
	if (str[0] == '\n')
		return;
	if (n == 1 && str[0] == ' ')
		return;
	for (int i = 0; i < n; i++)
	{
		his[p][i] = str[i];
	}
	size[p] = n;
	p++;
	p %= 20;
	if (fill < 20)
		fill++;
	return;
}

void print_hist(int n)
{
	if (n > fill)
		n = fill - 1;
	int v;
	if (p < n)
		v = 20 - n + p;
	else
		v = p - n;
	for (int i = 0; i < n; i++)
	{
		int a = (v + i) % 20;
		printf("%d ", i + 1);
		for (int j = 0; j < size[a]; j++)
		{
			printf("%c", his[a][j]);
		}
		 
	}
	return;
}
