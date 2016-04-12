/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljourda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 13:01:18 by aljourda          #+#    #+#             */
/*   Updated: 2016/01/08 15:40:27 by aljourda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_lst_strmove(t_list *lst, char **dst, size_t size, int const fd)
{
	size_t	cpy;
	void	*next;

	if (lst && dst && lst->next)
		size = (ft_lst_strmove(lst->next, dst, size, fd));
	if (lst && dst && lst->content_size > sizeof(t_fd) && FD_LST_CHECK)
	{
		cpy = (size < FD_CONTENT_SIZE) ? size : FD_CONTENT_SIZE;
		ft_memcpy((void*)*dst, ((t_fd*)lst->content)->content, cpy);
		lst->content_size -= cpy;
		if (lst->content_size <= sizeof(t_fd))
			ft_memdel(&(lst->content));
		else
			ft_memcpy(((t_fd*)lst->content)->content,
				((t_fd*)lst->content)->content + cpy, FD_CONTENT_SIZE);
		*dst += cpy;
		size -= cpy;
	}
	if (lst && lst->next && lst->next->content_size <= sizeof(t_fd))
	{
		next = lst->next;
		lst->next = lst->next->next;
		ft_memdel(&next);
	}
	return (size);
}

size_t	ft_lst_next_char(t_list *lst, char next, size_t total, int const fd)
{
	size_t	i;
	char	*buf;

	if (lst && lst->content_size > sizeof(t_fd) && FD_LST_CHECK)
	{
		if ((total > 0 || next == '\0'))
			total += FD_CONTENT_SIZE;
		else if (total == 0)
		{
			i = 0;
			buf = (char*)((t_fd*)lst->content)->content;
			while (i < FD_CONTENT_SIZE)
			{
				if (*(buf + i) == next)
				{
					total = i + 1;
					break ;
				}
				i++;
			}
		}
	}
	if (lst && lst->next)
		total = (ft_lst_next_char(lst->next, next, total, fd));
	return (total);
}

int		ft_lst_fill(int const fd, t_list **list, size_t *line_size)
{
	void	*buffer;
	t_fd	*data;
	int		size;
	void	*ptr;

	size = 1;
	if ((buffer = ft_memalloc(BUFF_SIZE)) != 0)
		while (*line_size == 0 && size > 0)
			if ((*line_size = ft_lst_next_char(*list, '\n', 0, fd)) == 0)
				if ((size = read(fd, buffer, BUFF_SIZE)) > 0)
				{
					data = ft_memalloc(size + sizeof(t_fd));
					if (data)
					{
						data->fd = fd;
						ft_memcpy((void*)data->content, buffer, size);
						if ((ptr = ft_lstnew(data, size + sizeof(t_fd))) != 0)
							ft_lstadd(list, ptr);
						else
							size = -1;
						ft_memdel((void**)&data);
					}
				}
	ft_memdel(&buffer);
	return (size);
}

int		get_next_line(int const fd, char **line)
{
	static t_list		*list;
	size_t				line_size;
	int					size;
	void				*ptr;

	line_size = 0;
	size = ft_lst_fill(fd, &list, &line_size);
	if (size >= 0)
	{
		if (line_size == 0)
		{
			line_size = ft_lst_next_char(list, '\0', 0, fd);
			line_size = (line_size > 0) ? line_size + 1 : line_size;
		}
		size = (line_size > 0) ? 1 : 0;
		if (line_size > 0 && (*line = ft_memalloc(line_size)) != 0)
		{
			ptr = (void*)*line;
			ft_lst_strmove(list, (char**)&ptr, line_size, fd);
			(*line)[line_size - 1] = 0;
		}
	}
	return (size);
}
