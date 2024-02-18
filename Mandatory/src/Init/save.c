/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaharel <icaharel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:41:33 by uclement          #+#    #+#             */
/*   Updated: 2024/02/18 14:44:35 by icaharel         ###   ########.fr       */
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

int	search_1(char **file, t_world *w)
{
	int		i;
	int		ret;
	char	**line;

	i = 0;
	ret = 1;
	while (file[i])
	{
		line = ft_split(file[i], ' ');
		if (ft_strcmp(line[0], "A") == 0)
			ret = init_ambiant(line, w);
		else if (strcmp(line[0], "L") == 0)
			ret = init_light(line, w);
		free_2(line);
		if (ret == 0)
			return (ret);
		i++;
	}
	return (ret);
}

int	search(char **file, t_shape **s, t_world *w)
{
	int		i;
	int		j;
	int		ret;
	char	**line;

	i = 0;
	j = 0;
	ret = search_1(file, w);
	while (file[i] && ret)
	{
		line = ft_split(file[i], ' ');
		if (ft_strcmp(line[0], "sp") == 0)
			ret = init_sp(line, &(*s)[j++], w);
		else if (ft_strcmp(line[0], "pl") == 0)
			ret = init_pl(line, &(*s)[j++], w);
		else if (ft_strcmp(line[0], "cy") == 0)
			ret = init_cy(line, &(*s)[j++], w);
		free_2(line);
		if (!ret)
			return (free_shape(*s, j), 0);
		i++;
	}
	return (ret);
}

int	init_world(char **file, t_world *w)
{
	int		i;
	int		nshape;
	char	**line;
	t_shape	*shape_list;

	i = 0;
	nshape = 0;
	while (file[i])
	{
		line = ft_split(file[i], ' ');
		if (ft_strcmp(line[0], "sp") == 0 || ft_strcmp(line[0], "pl") == 0
			|| ft_strcmp(line[0], "cy") == 0)
			nshape++;
		free_2(line);
		i++;
	}
	shape_list = malloc(sizeof(t_shape) * nshape);
	if (!shape_list)
		return (0);
	if (!search(file, &shape_list, w))
		return (0);
	w->shape = shape_list;
	w->count = nshape;
	return (nshape);
}
