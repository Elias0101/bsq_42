/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_lines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnigellu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:55:03 by bnigellu          #+#    #+#             */
/*   Updated: 2019/03/20 14:52:47 by bnigellu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char		**g_mass;

char		g_obstacle;

char		g_empty;

char		g_fill;

int			g_columns;

int			g_rows;

int			first_line(int fd)
{
	t_list	*root;
	char	buf[2];
	int		ret;

	buf[1] = '\0';
	root = NULL;
	if (((ret = read(fd, buf, 1)) > 0) && (buf[0] != '\n'))
	{
		root = create_el(buf[0]);
		list_fill(fd, root);
		if (check_el(root) >= 4)
			return (global_el(root));
	}
	del_struct(root);
	return (0);
}

int			global_el(t_list *root)
{
	g_fill = record_last_el(root);
	g_obstacle = record_last_el(root);
	g_empty = record_last_el(root);
	if (root->el == '+')
		g_rows = struct_atoi(root->next);
	else if ((root->el >= '0') && (root->el <= '9'))
		g_rows = struct_atoi(root);
	else
		return (0);
	if (g_rows <= 0)
		return (0);
	del_struct(root);
	return (1);
}

int			make_mass_size(void)
{
	int		i;

	i = 0;
	if ((g_mass = (char**)malloc(sizeof(char*) * g_rows)) != 0)
	{
		while (i < g_rows)
		{
			if ((g_mass[i] = (char*)malloc(sizeof(char) * g_columns + 1)) != 0)
			{
				g_mass[i][g_columns] = '\0';
				i++;
			}
			else
				return (0);
		}
		return (1);
	}
	else
		return (0);
}

int			fill_first_map_line(t_list *root)
{
	int		i;
	t_list	*last;

	i = 0;
	last = root;
	while (last != NULL)
	{
		if ((last->el == g_empty) || (last->el == g_obstacle))
		{
			g_mass[0][i] = last->el;
			i++;
			last = last->next;
		}
		else
			return (0);
	}
	return (1);
}

void		del_mass(void)
{
	int		i;

	i = g_rows - 1;
	while (i >= 0)
	{
		free(g_mass[i]);
		i--;
	}
	free(g_mass);
}
