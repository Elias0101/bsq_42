/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 19:01:29 by tkarri            #+#    #+#             */
/*   Updated: 2019/03/19 15:42:40 by tkarri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

#include <stdio.h>

char	**g_mass; //массив

char	g_obstacle; //char барьер

char	g_empty; //char пустота

char	g_fill; //chae которым надо заполнить найденный квадрат

int		g_i; //строка левого верхнего элемента квадрата, который мы нашли и будем заполнять

int		g_j; // аналогично только столбуц

int		g_len; //длина этого квадрата

int		g_columns; //количество столбцов в исходном map

int		g_rows; //количество строк в исходно мap

void	print_answer(void)
{
	int i;
	int j;

	char c; //delete

	i = 0;
	j = 0;
	while (i < g_rows)
	{
		while (j < g_columns)
		{/*
			if (g_mass[i][j] == g_obstacle)
				write(1, &g_obstacle, 1);
			else if (i >= g_i && j >= g_j && i < (g_i + g_len) && j < (g_j + g_len))
				write(1, &g_fill, 1);
			else
			write(1, &g_empty, 1);*/
			c = g_mass[i][j];
			write(1, &c, 1);
			j++;
		}
		write(1, "\n", 1);
		j = 0;
		i++;
	}
}

int		try_to_fill(int i, int j, int len)
{
	int i_max;
	int j_max;

	i_max = i + len;
	j_max = j + len;
	while (i < i_max)
	{
		while (j < j_max)
		{
			if (g_mass[i][j] == g_obstacle)
				return (-1);
			j++;
		}
		j = j_max - len;
		i++;
	}
	return (len + 1);
}

void	find_biggest_square(int i, int j, int len)
{
	int new_len;

	if (g_mass[i][j] == '\0')
	{
		i++;
		j = 0;
	}
	if (i != g_rows)
	{
		if (g_mass[i][j] != g_obstacle && (g_rows - i - 1) > len
			&& (g_columns - j - 1) > len)
		{
			while ((new_len = try_to_fill(i, j, len + 1)) > len)
				len = new_len;
			g_i = i;
			g_j = j;
			g_len = len; //bad variaty because of every time we change len (but possible is one at last
			j = j + 1;
			find_biggest_square(i, j, len);
		}
		else
		{
			j = j + 1;
			find_biggest_square(i, j, len);
		}
	}
}

void	fill_square()
{
	find_biggest_square(0, 0, 0);
	if (g_len != 0)
		print_answer();
}

void	readfile(int fd)
{
	char element[BUF_SIZE];
	char reading[1];
	int ret;
	int count;
	int i;
	int j;

	i = 0;
	j = 0;
	count = 0;
	ret = read(fd, element, BUF_SIZE);
	g_rows = element[0];
	g_empty = element[1];
	g_obstacle = element[2];
	g_fill = element[3];
	ret = read(fd, reading, 1);
	while ((ret = read(fd, reading, 1)) != 0)
	{
		if (reading[0] == '\n')
		{
			g_mass[i][j] = '\0';
			j = 0;
			i++;
		}
		else
		{
			g_mass[i][j] = reading[0];
			j++;
		}
	}
	g_mass[i][0] = '\0';
}

void	check_input()
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (g_mass[i][0] != '\0')
	{
		while (g_mass[i][j] != '\0')
		{
			printf("%c", g_mass[i][j]); 
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}
}

int		main(int ac, char **ar)
{
	int i;
	int fd;
	int j;

	j = 0;
	i = 1;
	if (ac > 1)
	{
		while (ar[i] != '\0')
		{
			g_mass = (char**)malloc(sizeof(char*) * (9 + 1));
			while (j < 10)
			{
				g_mass[j] = (char*)malloc(sizeof(char) * 27);
				j++;
			}
			fd = open(ar[i], O_RDONLY);
			printf("opened\n");
			if (fd != -1)
			{
				readfile(fd);
				printf("read\n");
				check_input();
				fill_square();
				//print_answer();
			}
			i++;
		}
	}
	return (0);
}
