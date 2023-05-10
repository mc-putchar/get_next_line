/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 03:45:34 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/10 07:14:37 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (*str++)
		++len;
	return (len);
}

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	srclen;
	size_t	i;

	srclen = ft_strlen(src);
	if (size && src && dst)
	{
		if (size > srclen)
			size = srclen + 1;
		i = 0;
		while (i < size - 1)
		{
			dst[i] = src[i];
			++i;
		}
		dst[i] = 0;
	}
	return (srclen);
}

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	i;

	srclen = ft_strlen(src);
	dstlen = 0;
	while (dst[dstlen] && dstlen < size)
		++dstlen;
	i = 0;
	if (srclen && size)
	{
		while (*src && i + dstlen < size - 1)
		{
			dst[dstlen + i] = *src++;
			++i;
		}
	}
	if (dstlen + i < size)
		dst[dstlen + i] = 0;
	return (dstlen + srclen);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*joined;
	size_t	len;

	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = 0;
	}
	if (!*s2)
		return (s1);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = malloc(len);
	if (!joined)
		return (free(s1), NULL);
	ft_strlcpy(joined, s1, len);
	ft_strlcat(joined, s2, len);
	free(s1);
	s1 = NULL;
	return (joined);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	memsize;
	size_t	i;
	char	*sub;

	memsize = 1;
	i = 0;
	if (s)
	{
		while (s[i] && i < start)
			++i;
		while (s[i++] && len--)
			++memsize;
	}
	sub = malloc(memsize);
	if (!sub)
		return (NULL);
	sub[--memsize] = 0;
	while (memsize--)
		sub[memsize] = s[start + memsize];
	return (sub);
}
