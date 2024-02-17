/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:41:33 by uclement          #+#    #+#             */
/*   Updated: 2024/02/17 18:26:19 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

void	free_shape(t_shape *s, int nshapes)
{
	int	i;

	i = -1;
	while (++i < nshapes)
	{
		free_matrix(s[i].transform);
		free(s[i].ptr_type);
	}
	free(s);
}

void	search_1(char **file, int *ret, t_world *w)
{
	int		i;
	char	**line;

	i = 0;
	while (file[i])
	{
		line = ft_split(file[i], ' ');
		if (strcmp(line[0], "A") == 0)
			*ret = init_ambiant(line, w);
		else if (strcmp(line[0], "L") == 0)
			*ret = init_light(line, w);
		free_2(line);
		i++;
	}
}

int	search(char **file, t_shape **s, t_world *w)
{
	int		i;
	int		j;
	int		ret;
	char	**line;

	i = 0;
	j = 0;
	ret = 0;
	search_1(file, &ret, w);
	i = 0;
	while (file[i])
	{
		line = ft_split(file[i], ' ');
		if (strcmp(line[0], "sp") == 0)
			ret = init_sp(line, &(*s)[j++], w);
		else if (strcmp(line[0], "pl") == 0)
			ret = init_pl(line, &(*s)[j++], w);
		else if (strcmp(line[0], "cy") == 0)
			ret = init_cy(line, &(*s)[j++], w);
		free_2(line);
		if (!ret)
			return (0); // gerer memoire
		i++;
	}
	return (1);
}