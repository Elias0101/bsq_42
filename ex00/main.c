/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnigellu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 15:19:01 by bnigellu          #+#    #+#             */
/*   Updated: 2019/03/20 22:43:49 by bnigellu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char		**g_mass;

char		g_obstacle;

char		g_empty;

char		g_fill;

int			g_columns;

int			g_rows;

int			g_len;

int			g_i;

int			g_j;

int     try_to_fill(int i, int j, int len)
{
    int i_max;
    int j_max;

    i_max = i + len;
    j_max = j + len;
	printf("i_max = %d\nj_max = %d\n", i + len, j + len);
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
    return (len);
}

void        find_biggest_square(int i, int j, int len)
{
    int new_len;

    if (g_mass[i][j] == '\0')
    {
        i++;
        j = 0;
    }
    printf("rec: i:%d j:%d\n", i, j);
    if (i != g_rows)
    {
        printf("\nconditions to go into: g_rows - i > len: %d > %d\ng_columns - j > len: %d > %d\n", (g_rows - i), len, (g_columns - j), len);
        if (g_mass[i][j] != g_obstacle && (g_rows - i) > len
            && (g_columns - j) > len)
        {
            printf("precycle check: i + len <= g_rows: %d <= %d\nj + len <= g_columns: %d <= %d\n", i + len, g_rows, j + len, g_columns);
            while (i + len < g_rows && j + len < g_columns && ((new_len = try_to_fill(i, j, len + 1)) > len))
            {
                len = new_len;
                printf("in-cycle check: i + len <= g_rows: %d <= %d\nj + len <= g_columns: %d <= %d\n", i + len, g_rows, j + len, g_columns);
            }
            if (len > g_len)
            {
                g_i = i;
                g_j = j;
                g_len = len; //bad variaty because of every time we change len (but possible is one at last
                printf("g_i: %d g_j: %d g_len: %d\n", g_i, g_j, g_len);
            }
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

void    print_answer(void)
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

int 		main(int n, char **str)
{
	int i;

	i = 0;
	while (i < n)
	{
		if ((massive(str[i], n) == 0) && (n > 1))
			write(2, "map error\n", 10);
		else
		{
		printf("\nrows: %d columns: %d empty: %c obstacle: %c fill: %c \n", g_rows, g_columns, g_empty, g_obstacle, g_fill);
			find_biggest_square(0, 0, 0);
			printf("\n\nfinished: g_i: %d, g_j: %d, g_len: %d\n", g_i, g_j, g_len);
			printf("\n\n");
			print_answer();
		}
		i++;
	}
	return (0);
}
