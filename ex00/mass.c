/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mass.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnigellu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 08:38:31 by bnigellu          #+#    #+#             */
/*   Updated: 2019/03/20 13:13:21 by bnigellu         ###   ########.fr       */
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

void	print_all_list(t_list *root)
{
	int i;

	i = 1;
	while (root->next != NULL)
	{
//		printf(" |%d: %c | ", i, root->el);
		i++;
		root = root->next;
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
//	 printf("%c\n", last->el);
//	 printf("%c\n", last->next->el);
	 while (last->next != NULL)
	 {
		 i++;
//		 printf("el: %c\n", last->el);
		 last =  last->next;
//		 printf("check_el: %d\n", i);
	 }
//	 printf("done");
//	 printf("check_el: %d\n", i);
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
//			printf("element = |%c|\n", root->el);
			free(buf);
			list_fill(fd, root->next);
		}
//		printf("done\n");
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
	if (root)
	{
		if (root->next != NULL)
			del_struct(root->next);
		root->next = NULL;
		free(root);
		root = NULL;
	}
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
		print_all_list(root);
//		printf("zakon\n");
//		if (root->next->next->next->next == NULL)
//			printf("NULL\n");
		if (check_el(root) >= 4)
		{
			g_fill = record_last_el(root);
//			printf("%c\n", g_fill);
			g_obstacle = record_last_el(root);
			g_empty = record_last_el(root);
//			printf("el: %c\n", root->el);
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

int			 make_mass_size()
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

void		 fill_first_map_line(t_list *root)
{
	int i;
	t_list *last;

	i = 0;
	last = root;
	while (last->next != NULL)
	{
		g_mass[0][i] = last->el;
		i++;
		last =  last->next;
	}
	g_mass[0][i] = last->el;
}

int			rest_lines(int fd)
{
	int     ret;
	int		i;
	int		j;
	char    buf[2];

	buf[1] = '\0';
	i = 1;
	j = 0;
	while ((ret = read(fd, buf, 1)) > 0)
	{
		if (buf[0] == '\n')
		{
			i++;
			if (j != g_columns)
				return (0);
			j = 0;
		}
		else if (((buf[0] == g_empty) || (buf[0] == g_obstacle))
				&& ((j < g_columns) && (i < g_rows)))
		{
			g_mass[i][j] = buf[0];
			j++;
		}
		else
			return (0);
	}
	if ((ret = read(fd, buf, 1)) > 0)
		return (0);
	return (1);
}

int			second_line(int fd)
{
	t_list  *root;
	char    buf[2];
	int     ret;

	buf[1] = '\0';
	root = NULL;
	if (((ret = read(fd, buf, 1)) > 0) && (buf[0] != '\n'))
	{
		root = create_el(buf[0]);
		list_fill(fd, root);
		print_all_list(root);
		g_columns = check_el(root);
//		printf("g_columns = %d\n", g_columns);
		if (make_mass_size() == 0)
			return (0);
		fill_first_map_line(root);
//		printf("first_map_line: |%s|\n", g_mass[0]);
		del_struct(root);
		return (1);
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
	if (second_line(fd) == 0)
		return (0);
	if (rest_lines(fd) == 0)
		return (0);
	check_input();
	close(fd);
	return (0);
}
