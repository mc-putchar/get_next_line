/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 06:17:41 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/19 06:19:24 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1337
# endif
# define FD_LIMIT 4096

typedef struct s_stream
{
	int				fd;
	ssize_t			len;
	size_t			off;
	unsigned char	buff[BUFFER_SIZE];
}	t_stream;

typedef struct s_buffer
{
	size_t			size;
	unsigned char	*buff;
}	t_buffer;

char			*get_next_line(int fd);
void			*ft_memcpy(void	*dest, const void *src, size_t n);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memgrow(void *ptr, size_t old_size, size_t new_size);

#endif
