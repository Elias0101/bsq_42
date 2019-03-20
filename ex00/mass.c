/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mass.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnigellu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 08:38:31 by bnigellu          #+#    #+#             */
/*   Updated: 2019/03/20 11:21:25 by bnigellu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


char		**g_mass; //массив

char		g_obstacle; //char барьер

char		g_empty; //char пустота

char		g_fill; //chae которым надо заполнить найденный квадрат

int			g_columns; //количество столбцов в исходном map

int			g_rows; //количество строк в исходно мap

void		check_input()
{
	int		i;
	int		j;

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

t_list		*create_el(char el)
{
	t_list *root;

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
	 int	i;

	 i = 1;
	 last = root;
	 printf("%c\n", last->el);
	 printf("%c\n", last->next->el);
	 while (last->next != NULL)
	 {
		 i++;
		 printf("el: %c\n", last->el);
		 last =  last->next;
		 printf("check_el: %d\n", i);
	 }
	 printf("done");
	 printf("check_el: %d\n", i);
	 if (i >= 4)
		 return (1);
	 else
		 return (0);
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
			printf("element = |%c|\n", root->el);
			free(buf);
			list_fill(fd, root->next);
		}
		printf("done\n");
	}
}

int			struct_atoi(t_list *root)
{
	int		res;
	t_list	*st_now;

	st_now = root;
	while (st_now != NULL)
	{
		if ((st_now->el >= '0') && (st_now->el <= '9'))
		{
			res = res * 10 	+ (st_now->el - 48);
			st_now = st_now->next;
		}
		else
			return (0);
	}
	return (res);
}
			
void		del_struct(t_list *root)
{
	if ((root->next == NULL) || (root == NULL))
		free(root);
	else
		del_struct(root->next);
}

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
		printf("zakon\n");
		if (root->next->next->next->next == NULL)
			printf("NULL\n");
		if (check_el(root) == 1)
		{
			g_fill = record_last_el(root);
			printf("%c\n", g_fill);
			g_obstacle = record_last_el(root);
			g_empty = record_last_el(root);
			printf("el: %c\n", root->el);
			if (root->el == '+')
				g_rows = struct_atoi(root->next);
			else if ((root->el >= '0') && (root->el <= '9'))
				g_rows = struct_atoi(root);
			else
				return(0);
			if (g_rows == 0)
				return (0);
			del_struct(root);
			return(1);
		}
	}
	del_struct(root);
	return (0);	
}



int			main(int n, char **str)
{
	(void)n;
	int		fd;

	if ((fd = open(str[1], O_RDONLY)) == -1)
	   return(0);
	if (first_line(fd) == 0)
		return(0);
	printf("%d  %c  %c  %c\n",g_rows, g_empty, g_obstacle, g_fill);
	close(fd);
	return (0);
}
