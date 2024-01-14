/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inverter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:36:16 by ulysseclem        #+#    #+#             */
/*   Updated: 2024/01/14 13:08:59 by ulysseclem       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"


t_matrix* inverse(t_matrix *m)
{
	t_matrix* copy;
	t_matrix* identity;
	int			i;
	int			j;
	int 		k;
	float 		scalar;
	float		factor;

	copy = create_matrix(4, 4);
	fill_matrix(copy, m->data);
	identity = identify_matrix(4, 4);

	// Gaussian elimination to transform 
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
		k = 0;
		while (k < 4)
		{
			if (k != i) {
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
		i++;
	}
	free_matrix(copy);
	return identity;
}