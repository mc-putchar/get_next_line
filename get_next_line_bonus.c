/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:32:18 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/10 09:32:50 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//TODO: rewrite all dependencies from ft_strlcpy to ft_memccpy
#include "get_next_line_bonus.h"

//Create allocated save struct w/ buffer remainder and file descriptor
static t_save	*attempt_save(t_data *d, int fd)
{
	int		retries;
	t_save	*save;

	retries = MAX_MALLOC_ATTEMPTS;
	save = NULL;
	if (d->rbytes > 0)
	{
		if (0[d->buff])
		{
			while (!save && retries--)
				save = malloc(sizeof(t_save));
			if (save)
			{
				save->fd = d->fd;
				ft_strlcpy(save->buff, &(d->buff[d->pos]), BUFFER_SIZE + 1);
				save->next = NULL;
			}
		}
	}
	d->buff[0] = 0;
	d->fd = fd;
	d->pos = 0;
	return (save);
}

//If buffer not empty swap states, else overwrite w/ saved data or 0
static void	load_saved_state(t_data *d, int fd)
{
	t_save	*save;
	t_save	*load;
	t_save	*prev;

	save = attempt_save(d, fd);
	load = d->save;
	while (load && load->fd != fd)
	{
		prev = load;
		load = load->next;
	}
	if (load && ft_strlcpy(d->buff, load->buff, BUFFER_SIZE + 1))
	{
		if (load->next && prev)
			prev->next = load->next;
		else
			d->save = load->next;
		free(load);
	}
	d->rbytes = ft_strlen(d->buff);
	if (save)
	{
		save->next = d->save;
		d->save = save;
	}
}

static char	*find_nline(t_data *d)
{
	char	*tmp;
	char	*nl;
	ssize_t	n;

	n = d->pos;
	nl = NULL;
	while (d->buff[n] && d->buff[n] != '\n')
		++n;
	if (d->buff[n] == '\n')
	{
		tmp = ft_substr(d->buff, d->pos, ++n);
		nl = ft_strjoin(nl, tmp);
		free(tmp);
		d->pos = n;
	}
	return (nl);
}

//Search for next line break or end of file and return allocated string or NULL
static char	*retrieve_nline(t_data *d)
{
	char	*tmp;
	char	*nl;

	nl = NULL;
	tmp = NULL;
	while (!tmp && d->pos <= d->rbytes)
	{
		tmp = find_nline(d);
		if (!tmp)
		{
			nl = ft_strjoin(nl, &(d->buff[d->pos]));
			d->rbytes = read(d->fd, d->buff, BUFFER_SIZE);
			d->pos = 0;
			if (d->rbytes == -1)
				return (free(nl), d->rbytes++, NULL);
			d->buff[d->rbytes] = 0;
			if (!(d->rbytes))
				return (nl);
		}
	}
	nl = ft_strjoin(nl, tmp);
	return (free(tmp), nl);
}

/*
Returns the next line (line break included) from the provided file descriptor.
Returns NULL if no more lines are available or an error occurs.
Use free() to deallocate the returned string.
*/
char	*get_next_line(int fd)
{
	static t_data	d;

	if (fd != d.fd)
		load_saved_state(&d, fd);
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!d.rbytes)
	{
		d.rbytes = read(fd, d.buff, BUFFER_SIZE);
		if (d.rbytes != -1)
			d.buff[d.rbytes] = 0;
	}
	if (d.rbytes < 1)
	{
		d.buff[0] = 0;
		d.pos = 0;
		return (NULL);
	}
	return (retrieve_nline(&d));
}
/*
#include <fcntl.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	char	*line;
	int		fd;
	char	*filename;

    if (argc > 1)
	{
		while (--argc)
		{
			filename = argv[argc];
			fd = open(filename, O_RDONLY);
			line = get_next_line(fd);
			while (line)
			{
				printf("%s", line);
				free(line);
				line = get_next_line(fd);
			}
			close(fd);
		}
	}
}
*/