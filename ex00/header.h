/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 21:18:26 by tkarri            #+#    #+#             */
/*   Updated: 2019/03/20 15:28:33 by bnigellu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>

# include <stdlib.h>

# include <sys/types.h>

# include <sys/stat.h>

# include <fcntl.h>

# include <stdio.h>

typedef struct		s_list
{
	struct s_list	*next;
	char			el;
}					t_list;

t_list				*create_el(char el);

int					massive(char *str);

int					check_el(t_list *root);

char				record_last_el(t_list *root);

void				list_fill(int fd, t_list *root);

int					struct_atoi(t_list *root);

void				del_struct(t_list *root);

int					global_el(t_list *root);

int					assign(int i, int j, char *buf);

int					first_line(int fd);

int					make_mass_size();

int					fill_first_map_line(t_list *root);

int					rest_lines(int fd);

void				del_mass();

int					second_line(int fd);


#endif
