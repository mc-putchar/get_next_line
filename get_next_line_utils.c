/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 03:45:34 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/19 06:13:56 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void	*dest, const void *src, size_t n)
{
	size_t	i;

	if (!src || !dest)
		return (dest);
	i = 0;
	while (i++ < n)
		*(unsigned char *)(dest + i - 1) = *(unsigned char *)src++;
	return (dest);
}

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	while (n--)
	{
		*(unsigned char *)dest = *(unsigned char *)src++;
		if (*(unsigned char *)dest++ == (unsigned char)c)
			return (dest);
	}
	return (NULL);
}

void	*ft_memgrow(void *ptr, size_t old_size, size_t new_size)
{
	void	*new;

	new = malloc(new_size);
	if (!new)
		return (NULL);
	if (ptr && new_size > old_size)
		new = ft_memcpy(new, ptr, old_size);
	return (free(ptr), new);
}
