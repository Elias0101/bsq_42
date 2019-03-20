/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnigellu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 15:19:01 by bnigellu          #+#    #+#             */
/*   Updated: 2019/03/20 15:34:21 by bnigellu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char		**g_mass;

char		g_obstacle;

char		g_empty;

char		g_fill;

int			g_columns;

int			g_rows;

int 		main(int n, char **str)
{
	int i;

	i = 1;
	while (i < n)
	{
		if (massive(str[i]) == 0)
			write(2, "map error\n", 10);
		i++;
	}
	return (0);
}
