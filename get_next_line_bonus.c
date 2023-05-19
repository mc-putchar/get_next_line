/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 06:17:16 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/19 06:17:38 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	init_buffer(t_stream *stream, t_buffer *re)
{
	if (!re->buff)
	{
		stream->len = read(stream->fd, stream->buff, BUFFER_SIZE);
		return (stream->len);
	}
	ft_memcpy(stream->buff, re->buff, re->size);
	free(re->buff);
	re->buff = NULL;
	stream->len = re->size;
	stream->off = 0;
	return (stream->len);
}

static void	save_re(t_stream *stream, t_buffer *re)
{
	if (stream->off >= (size_t)stream->len)
		return ;
	if (stream->off < (size_t)stream->len)
	{
		re->size = stream->len - stream->off;
		re->buff = malloc(re->size);
	}
	if (!re->buff)
		return ;
	ft_memcpy(re->buff, stream->buff + stream->off, re->size);
}

static unsigned char	*getl(t_stream *s, size_t *n)
{
	unsigned char	*line;
	unsigned char	*tmp;

	line = NULL;
	while (s->len > 0)
	{
		line = ft_memgrow(line, *n, *n + s->len + 1);
		if (!line)
			return (NULL);
		tmp = ft_memccpy(line + *n, s->buff, 10, s->len);
		if (tmp)
		{
			s->off = (size_t)(tmp - line - *n);
			*n += s->off;
			return (line);
		}
		*n += s->len;
		s->len = read(s->fd, s->buff, BUFFER_SIZE);
	}
	if (s->len == -1)
		return (free(line), NULL);
	return (line);
}

static unsigned char	*gnl(t_stream *s, t_buffer *re)
{
	size_t			n;
	unsigned char	*line;

	n = 0;
	if (init_buffer(s, re) < 1)
		return (NULL);
	line = getl(s, &n);
	if (!line)
		return (NULL);
	if (s->len > 0)
		save_re(s, re);
	line[n] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static t_buffer	re[FD_LIMIT];
	unsigned char	*nline;
	t_stream		*stream;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= FD_LIMIT)
		return (NULL);
	stream = malloc(sizeof(t_stream));
	if (!stream)
		return (NULL);
	stream->fd = fd;
	nline = gnl(stream, &re[fd]);
	if (!nline)
		return (free(stream), NULL);
	return (free(stream), (char *)nline);
}
