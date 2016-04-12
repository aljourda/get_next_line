/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljourda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 13:02:42 by aljourda          #+#    #+#             */
/*   Updated: 2016/01/06 13:09:41 by aljourda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <dlfcn.h>
#include "get_next_line.h"

static void* (*r_malloc)(size_t) = NULL;
static void (*r_free)(void*) = NULL;

static int current_memory = 0;
static int allow_malloc = 1;
static int debug_malloc = 0;

void initialize() {
    r_malloc = dlsym(RTLD_NEXT, "malloc");
    r_free = dlsym(RTLD_NEXT, "free");
}

void* malloc(size_t size) {
	void	*mem;

	if (debug_malloc)
		printf("\tMalloc");
//	allow_malloc++;
	if (allow_malloc%2){
		current_memory++;
		mem = r_malloc(size);
		if (mem != 0)
		{
			if (debug_malloc)
				printf(" ok : %p...\n",mem);
			return (mem);
		}
	}
	if (debug_malloc)
		printf(" error...\n");
	return (0);
}

void free(void *ptr) {
	if (ptr != 0)
		current_memory--;
	if (debug_malloc)
		printf("\tFree : %p...\n", ptr);
	r_free(ptr);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*next;
	int		ret;

	fd = 0;
	initialize();
	if (argc > 1)
		fd = open(argv[1], O_RDONLY);

	if (fd >= 0)
	{
		while ((ret = get_next_line(fd, &next)) >= 0)
		{
			printf("fd %d ; status %d ; line $%s$\n", fd, ret, next);
			free(next);
			if (ret == 0)
				break ;
		}
	}
	if (argc > 1)
		close(fd);
	printf("Memory : %d\n", current_memory);

	return (0);
}