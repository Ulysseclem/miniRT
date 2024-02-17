/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_maker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaharel <icaharel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:42:55 by uclement          #+#    #+#             */
/*   Updated: 2024/02/17 17:25:40 by icaharel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

t_matrix	*create_matrix(int r, int c)
{
	t_matrix	*matrix;
	int			i;

	matrix = malloc(sizeof(t_matrix));
	if (!matrix)
		return (NULL);
	matrix->r = r;
	matrix->c = c;
	matrix->data = malloc(sizeof(float *) * r);
	if (!matrix->data)
		return (NULL);
	i = 0;
	while (i < c)
	{
		matrix->data[i] = malloc(sizeof(float) * c);
		if (!matrix->data[i])
			return (NULL);
		i++;
	}
	return (matrix);
}

void	fill_matrix(t_matrix *m, float **value)
{
	int	i;
	int	j;

	i = 0;
	while (i < m->r)
	{
		j = 0;
		while (j < m->c)
		{
			m->data[i][j] = value[i][j];
			j++;
		}
		i++;
	}
}

t_matrix	*identify_matrix(int r, int c)
{
	int			i;
	int			j;
	t_matrix	*matrix;

	matrix = create_matrix(r, c);
	i = 0;
	while (i < r)
	{
		j = 0;
		while (j < c)
		{
			if (i == j)
				matrix->data[i][j] = 1;
			else
				matrix->data[i][j] = 0;
			j++;
		}
		i++;
	}
	return (matrix);
}

t_matrix	*identify_matrix_reverse(int r, int c)
{
	int			i;
	int			j;
	t_matrix	*matrix;

	matrix = create_matrix(r, c);
	i = 0;
	while (i < r)
	{
		j = 0;
		while (j < c)
		{
			if (i == j)
				matrix->data[i][j] = -1;
			else
				matrix->data[i][j] = 0;
			j++;
		}
		i++;
	}
	return (matrix);
}
