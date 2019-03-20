/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mass.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnigellu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 08:38:31 by bnigellu          #+#    #+#             */
/*   Updated: 2019/03/20 22:41:55 by bnigellu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char		**g_mass;

char		g_obstacle;

char		g_empty;

char		g_fill;

int			g_columns;

int			g_rows;

void		check_input(void)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < g_rows)
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

int			massive(char *str, int n)
{
	int		fd;

	if (n == 1)
		fd = 0;
	else if ((fd = open(str, O_RDONLY)) == -1)
		return (0);
	if (first_line(fd) == 0)
		return (0);
	if (second_line(fd) == 0)
		return (0);
	if (rest_lines(fd) == 0)
	{
		del_mass();
		return (0);
	}
	printf("%d  %c  %c  %c\n", g_rows, g_empty, g_obstacle, g_fill);
	check_input();
	close(fd);
	return (1);
}
