/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 19:01:29 by tkarri            #+#    #+#             */
/*   Updated: 2019/03/19 22:44:49 by bnigellu         ###   ########.fr       */
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

void		find_biggest_square(int i, int j, int len)
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

int		rest_lines(int fd)
{
	int ret;
	char *buf;
	int i;
	int j;

	i = 1;
	buf = (char*)malloc(sizeof(char) * 2);
	buf[1] = '\0';
	while ((ret = read(fd, buf, 1)) > 0)
	{
		printf("Zashel\n");
		buf[1] = '\0';
		if (buf[0] == '\n')
		{
			printf("g_mass[%d] = |%s|\n", i, g_mass[i]);
			i++;
			j = 0;
		}
		else
		{
			if ((i == g_rows) || (j > g_columns))
			{
				free(g_mass);
				return (0);
			}
			g_mass[i][j] = buf[0];
			j++;
		}
	}
	return (1);
}

void second_line(char *str)
{
	int i;

	printf("%s\n", str);
	i = 0;
	while (str[i] != '\0')
		i++;
	g_columns = i;
	printf("col: %d\n", g_columns);
	i = 0;
	while (i != g_rows)
	{
		g_mass[i] = (char*)malloc(sizeof(char) * g_columns + 1);
		if (g_mass[i] == NULL)
		{
			printf("UPS\n");
			break;
		}
		g_mass[i][g_columns] = '\0';
		i++;
	}
	i = 0;
	while ( i != g_rows)
	{
		g_mass[0][i] = str[i];
		i++;
	}
	printf("g_mass[0] = |%s|\n", g_mass[0]);
}

int	my_atoi(char *str)
{
	int i;
	int res;
	int sign;

	res = 0;
	i = 0;
	sign =  1;
	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[0] == '+')
		i++;
	while (str[i] != '\n')
	if ((str[i] >= '0') && (str[i] <= '9'))
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	else
		return (0);
	return (res * sign);
}

int first_line(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	if (i >= 4)
	{
		i--;
		g_fill = str[i];
		i--;
		g_obstacle = str[i];
		i--;
		g_empty = str[i];
		str[i] = '\n';
		g_rows = my_atoi(str);
		if (g_rows <= 0)
		   return (0);
		free(str);
		printf("%d %c %c %c\n", g_rows, g_empty, g_obstacle, g_fill);
		if ((g_mass = (char**)malloc(sizeof(char*) * g_rows)) != NULL)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}
/*
int my_atoi(char *str)
{
	int i;
	int res;
	int sign;

	res = 0;
	i = 0;
	sign =  1;
	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[0] == '+')
		i++;
	while (str[i] != '\n')
		if ((str[i] >= '0') && (str[i] <= '9'))
		{
			res = res * 10 + (str[i] - 48);
			i++;
		}
		else
			return (0);
	return (res * sign);
	}*/

void assign(char *s1, char *s2)
{
	int i;
	
	i = 0;
	while ((s1[i] != '\0') || (s2[i] != '\0'))
    	{
      		s1[i] = s2[i];
      		i++;
    	}
}

char	*line_str(int fd, int *p_ret)
{
	int k;
	char *buf;
	char *s1;
	char *s2;
	int ret;

	buf = (char*)malloc(sizeof(char) * 2);
	buf[1] = '\0';
	k = 0;
	s2 = (char*)malloc(sizeof(char) * 2);
	s2[1] = '\0';
	while (((ret = read(fd, buf, 1)) > 0) && (buf[0] != '\n'))
	{
		printf("line_str (s2d): |%s|, k = %d\n", s2, k);
		s2[k] = buf[0];
		printf("line_str (s2p): |%s|, k = %d\n", s2, k);
		if ((s1 = (char*)malloc(sizeof(char) * k + 2)) == NULL)
			printf("NULL\n");
		s1[k+1] = '\0';
//		printf("do: s1 = |%s|, s2 = |%s|\n", s1, s2);
		assign(s1,s2);
		printf("line_str (s1c): |%s|, k = %d\n", s1, k);
//		printf("posle: s1 = |%s|, s2 = |%s|\n", s1, s2);
		free(s2);	
		k++;
		if ((s2 = (char*)malloc(sizeof(char) * k + 1)) == NULL)
		   printf("NULL\n");	
		s2[k + 1] = '\0';
		if (k == 16)
			printf("line_str: |%s|\ns2 = |%s|\n", s1, s2);
		assign(s2, s1);
		if (k == 16)
			printf("line_str: |%s|\ns2 = |%s|\n", s1, s2);
		free(s1);
	}
	s2[k] = '\0';
	printf("s2: |%s|\n", s2);
	free(buf);
	*p_ret = ret;
	return (s2);
}

/*void assign(char *s1, char *s2)
{
	int i;

	i = 0;
	while ((s1[i] != '\0') || (s2[i] != '\0'))
	{
		s1[i] = s2[i];
		i++;
	}
	}*/


int		main(int ac, char **ar)
{
	int i;
	int fd;
	int ret;

	i = 1;
	while (i < ac)
	{
		if (((fd = open(ar[i], O_RDONLY)) != -1)
				&& (first_line(line_str(fd, &ret)) != 0))
		{
			printf("Vizov second_line\n");
			second_line(line_str(fd, &ret));
			if (rest_lines(fd) == 1)
				check_input();
		}
		i++;
	}
	close(fd);
	return (0);
}
