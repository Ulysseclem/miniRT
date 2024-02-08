/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inverter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:36:16 by ulysseclem        #+#    #+#             */
/*   Updated: 2024/02/08 17:23:46 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

t_matrix	*inverse_next(int i, t_matrix *copy, t_matrix *identity)
{
	int		k;
	int		j;
	float	factor;

	k = 0;
	while (k < 4)
	{
		if (k != i)
		{
			factor = copy->data[k][i];
			j = 0;
			while (j < 4)
			{
				copy->data[k][j] -= factor * copy->data[i][j];
				identity->data[k][j] -= factor * identity->data[i][j];
				j++;
			}
		}
		k++;
	}
	return (copy);
}

t_matrix	*inverse(t_matrix *m)
{
	t_matrix	*copy;
	t_matrix	*identity;
	int			i;
	int			j;
	float		scalar;

	copy = create_matrix(4, 4);
	fill_matrix(copy, m->data);
	identity = identify_matrix(4, 4);
	i = 0;
	while (i < 4)
	{
		scalar = 1.0 / copy->data[i][i];
		j = 0;
		while (j < 4)
		{
			copy->data[i][j] *= scalar;
			identity->data[i][j] *= scalar;
			j++;
		}
		copy = inverse_next(i, copy, identity);
		i++;
	}
	free_matrix(copy);
	return (identity);
}
