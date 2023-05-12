/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:32:36 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/10 09:32:40 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str++)
		++len;
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
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

size_t	ft_strlcat(char *dst, const char *src, size_t size)
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

char	*ft_strjoin(char *s1, const char *s2)
{
	char	*joined;
	size_t	len;

	if (!s1)
	{
		s1 = malloc(sizeof(char));
		*s1 = 0;
	}
	if (!s2 || (!*s1 && !*s2))
		return (free(s1), NULL);
	if (!*s2)
		return (s1);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = malloc(len);
	if (!joined)
		return (NULL);
	ft_strlcpy(joined, s1, len);
	ft_strlcat(joined, s2, len);
	free(s1);
	return (joined);
}

/*
Allocates memory for a new string and copies the contents of the
given string to it from start index to end index (not included).
Returns a pointer to the new string or NULL on error.
Use free() to deallocate the string.
*/
char	*ft_substr(const char *s, size_t start, size_t end)
{
	size_t	memsize;
	char	*sub;

	if (!s)
		return (NULL);
	memsize = end - start + 1;
	sub = malloc(memsize);
	if (!sub)
		return (NULL);
	sub[--memsize] = 0;
	while (memsize--)
		sub[memsize] = s[start + memsize];
	return (sub);
}
