/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnigellu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:47:02 by bnigellu          #+#    #+#             */
/*   Updated: 2019/03/20 13:54:34 by bnigellu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char		**g_mass;

char		g_obstacle;

char		g_empty;

char		g_fill;

int			g_columns;

int			g_rows;

t_list		*create_el(char el)
{
	t_list	*root;

	root = malloc(sizeof(t_list));
	if (root != 0)
	{
		root->next = NULL;
		root->el = el;
	}
	return (root);
}

int			check_el(t_list *root)
{
	t_list	*last;
	int		i;

	i = 1;
	last = root;
	while (last->next != NULL)
	{
		i++;
		last = last->next;
	}
	return (i);
}

char		record_last_el(t_list *root)
{
	t_list	*last;
	char	sym;

	last = root;
	while (last->next->next != NULL)
		last = last->next;
	sym = last->next->el;
	free(last->next);
	last->next = NULL;
	return (sym);
}

void		list_fill(int fd, t_list *root)
{
	char	*buf;
	int		ret;

	if ((buf = (char*)malloc(sizeof(char) * 2)) != 0)
	{
		buf[1] = '\0';
		if (((ret = read(fd, buf, 1)) > 0) && (buf[0] != '\n'))
		{
			root->next = create_el(buf[0]);
			free(buf);
			list_fill(fd, root->next);
		}
	}
}

int			struct_atoi(t_list *root)
{
	int		res;
	t_list	*st_now;

	res = 0;
	st_now = root;
	while (st_now != NULL)
	{
		if ((st_now->el >= '0') && (st_now->el <= '9'))
		{
			res = res * 10 + (st_now->el - 48);
			st_now = st_now->next;
		}
		else
			return (0);
	}
	return (res);
}
