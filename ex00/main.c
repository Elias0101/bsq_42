/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 19:01:29 by tkarri            #+#    #+#             */
/*   Updated: 2019/03/18 21:23:24 by tkarri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

	i = 0;
	j = 0;
	while (i < g_rows)
	{
		while (j < g_columns)
		{
			if (g_mass[i][j] == g_obstacle)
				write(1, &g_obstacle, 1);
			else if (i >= g_i && j >= g_j && i < (g_i + g_len) && j < (g_j + g_len))
				write(1, &g_fill, 1);
			else
				write(1, &g_empty, 1);
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

int		main(void)
{
	fill_square();
	return (0);
}
