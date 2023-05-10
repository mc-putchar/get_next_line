/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 01:00:17 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/10 09:22:09 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*find_nline(char *str, ssize_t *i, ssize_t r)
{
	ssize_t	n;
	ssize_t	s;
	char	*line;

	n = -1;
	s = *i;
	while (str[s])
	{
		if (str[s++] == '\n')
		{
			n = s;
			break ;
		}
	}
	if (n == -1)
		return (NULL);
	line = ft_substr(str, *i, n - *i);
	*i = s;
	if (s == r)
		*i = 0;
	return (line);
}

static char	*gtfo(t_data *data, char *line)
{
	char	*ret;

	data->buff[0] = 0;
	data->pos = 0;
	ret = NULL;
	if (!data->rbytes)
		ret = line;
	else if (line)
		free(line);
	data->rbytes = 0;
	return (ret);
}

char	*get_next_line(int fd)
{
	static t_data	d;
	char			*nline;
	char			*tmp;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	nline = NULL;
	while (1)
	{
		if (!d.pos)
		{
			d.rbytes = read(fd, d.buff, BUFFER_SIZE);
			if (d.rbytes < 1)
				return (gtfo(&d, nline));
			d.buff[d.rbytes] = 0;
		}
		tmp = find_nline(d.buff, &(d.pos), d.rbytes);
		if (tmp)
		{
			nline = ft_strjoin(nline, tmp);
			return (free(tmp), nline);
		}
		nline = ft_strjoin(nline, &d.buff[d.pos]);
		d.pos = 0;
	}
}
