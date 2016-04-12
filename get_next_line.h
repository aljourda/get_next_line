/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljourda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 12:59:46 by aljourda          #+#    #+#             */
/*   Updated: 2016/04/09 12:55:33 by aljourda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <libft.h>
# include <stdlib.h>
# include <unistd.h>
# define BUFF_SIZE 32
# define FD_CONTENT_SIZE	lst->content_size - sizeof(t_fd)
# define FD_LST_CHECK		((t_fd*)lst->content)->fd == fd

typedef struct			s_fd
{
	int					fd;
	char				content[];
}						t_fd;

int						get_next_line(int const fd, char **line);

#endif
