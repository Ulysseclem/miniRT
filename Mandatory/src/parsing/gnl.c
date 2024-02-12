/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:19:59 by uclement          #+#    #+#             */
/*   Updated: 2024/02/12 13:11:53 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

int	is_nextline(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*set_final(void *temp, int eof)
{
	int		size;
	char	*sub;
	char	*next_line;

	if (eof == TRUE)
		size = ft_strlen(temp);
	else
		size = is_nextline(temp) + 1;
	next_line = ft_calloc(sizeof(char), size + 2);
	if (!next_line)
		return (NULL);
	ft_strncat(next_line, temp, size);
	sub = ft_substr(temp, size, BUFFER_SIZE);
	ft_strncpy(temp, sub, BUFFER_SIZE);
	free(sub);
	return (next_line);
}

char	*get_next_line(int fd)
{
	int			eof;
	int			b_read;
	char		*buf;
	static char	temp[10000000];

	eof = 0;
	if (temp[0] && is_nextline(temp) >= 0)
		return (set_final(&temp, eof));
	while (is_nextline(temp) < 0 && eof == FALSE)
	{
		buf = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
		if (!buf)
			return (NULL);
		b_read = read(fd, buf, BUFFER_SIZE);
		if (b_read == -1 || (b_read == 0 && ft_strlen(temp) == 0))
			free(buf);
		if (b_read == -1 || (b_read == 0 && ft_strlen(temp) == 0))
			return (NULL);
		if (ft_strncat(temp, buf, b_read) == FALSE)
			eof = TRUE;
		free(buf);
		if (!temp[0])
			return (NULL);
	}
	return (set_final(&temp, eof));
}
