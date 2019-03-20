/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rest_struct_fun.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnigellu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:56:04 by bnigellu          #+#    #+#             */
/*   Updated: 2019/03/20 22:43:16 by bnigellu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char		**g_mass;

char		g_obstacle;

char		g_empty;

char		g_fill;

int			g_columns;

int			g_rows;

void		del_struct(t_list *root)
{
	if (root)
	{
		if (root->next != NULL)
			del_struct(root->next);
		root->next = NULL;
		free(root);
		root = NULL;
	}
}

int			rest_lines(int fd)
{
	int		ret;
	int		i;
	int		j;
	char	buf[2];

	buf[1] = '\0';
	i = 1;
	j = 0;
	while ((ret = read(fd, buf, 1)) > 0)
	{
		if ((buf[0] == '\n') && (j == g_columns))
		{
			i++;
			j = 0;
		}
		else if (((buf[0] == g_empty) || (buf[0] == g_obstacle))
				&& ((j < g_columns) && (i < g_rows)))
			j = assign(i, j, buf);
		else
			return (0);
	}
	if (((ret = read(fd, buf, 1)) > 0) || (i != g_rows))
		return (0);
	return (1);
}

int		assign(int i, int j, char *buf)
{
	g_mass[i][j] = buf[0];
	return (j + 1);
}

int			second_line(int fd)
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
		g_columns = check_el(root);
		if (make_mass_size() == 0)
			return (0);
		if (fill_first_map_line(root) == 0)
		{
			del_mass();
			return (0);
		}
		del_struct(root);
		return (1);
	}
	del_struct(root);
	return (0);
}
