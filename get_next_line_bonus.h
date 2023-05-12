/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:32:29 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/10 09:32:33 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# define MAX_MALLOC_ATTEMPTS 7

typedef struct s_save
{
	int				fd;
	char			buff[BUFFER_SIZE + 1];
	struct s_save	*next;
}	t_save;

typedef struct s_data
{
	ssize_t	pos;
	ssize_t	rbytes;
	char	buff[BUFFER_SIZE + 1];
	int		fd;
	t_save	*save;
}	t_data;

char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strjoin(char *s1, const char *s2);
char	*ft_substr(const char *s, size_t start, size_t end);

#endif
