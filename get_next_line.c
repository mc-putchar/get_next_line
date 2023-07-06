/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 23:36:17 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/20 01:47:23 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4242
#endif

void	ft_memcpy(void *dest, const void *src, size_t n)
{
	if (!src)
		return ;
	while (n--)
		*(unsigned char *)dest++ = *(unsigned char *)src++;
}

void	ft_memmove(void *dest, const void *src, size_t n)
{
	if (!src || dest == src)
		return ;
	if (dest < src)
	{
		ft_memcpy(dest, src, n);
		return ;
	}
	while (n--)
		*(unsigned char *)(dest + n) = *(unsigned char *)(src + n);
}

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	if (!src)
		return (NULL);
	while (n--)
	{
		*(unsigned char *)dest++ = *(unsigned char *)src;
		if (*(unsigned char *)src++ == (unsigned char)c)
			return ((void *)src);
	}
	return (NULL);
}

void	ft_bzero(void *buff, size_t n)
{
	while (n--)
		*(unsigned char *)buff = 0;
}

void	*ft_realloc(void *ptr, size_t old, size_t new)
{
	void	*nptr;

	if (!new)
		return (free(ptr), NULL);
	nptr = malloc(new);
	if (!nptr)
		return (NULL);
	if (old && old <= new)
		ft_memcpy(nptr, ptr, old);
	if (ptr)
		free(ptr);
	return (nptr);
}

char	*find_line(int fd, char *buff, ssize_t *s)
{
	char	*seek;
	char	*line;
	size_t	len;

	len = 0;
	line = NULL;
	while (*s > 0)
	{
		line = ft_realloc(line, len, len + *s + 1);
		seek = ft_memccpy(line + len, buff, '\n', *s);
		if (seek)
		{
			// found it, shuffle the buffs
			line[len + seek - buff] = 0;
			if (seek == buff + *s)
			{
				ft_bzero(buff, *s);
				*s = 0;
				return (line);
			}
			*s -= seek - buff;
			ft_memmove(buff, seek, *s);
			ft_bzero(buff + *s, BUFFER_SIZE - *s);
			return (line);
		}
		len += *s;
		*s = read(fd, buff, BUFFER_SIZE);
	}
	if (*s < 0)
		return (free(line), NULL);
	line[len] = 0;
	return (line);
}

char	*get_next_line(int fd)
{
	static char		buff[BUFFER_SIZE];
	static ssize_t	size = 0;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!size)
		size = read(fd, &buff[0], BUFFER_SIZE);
	if (size < 0)
	{
		size = 0;
		return (NULL);
	}
	if (!size)
		return (NULL);
	return (find_line(fd, &buff[0], &size));
}

/*
#include <stdio.h>
#include <fcntl.h>
int	main(int ac, char **av)
{
	int		fd;
	char	*line;

	if (ac != 2)
		return (0);
	if (*av[1] == '-')
		fd = 0;
	else
		fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	printf("\n### READ DONE ###\n");
	return (0);
}
*/
