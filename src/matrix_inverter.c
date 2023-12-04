/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inverter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:36:16 by ulysseclem        #+#    #+#             */
/*   Updated: 2023/12/04 22:51:16 by ulysseclem       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float determinant(t_matrix *m)
{
	return(m->data[0]*m->data[3] - m->data[1]*m->data[2]);
}

t_matrix *submatrix(t_matrix *m, int r, int c)
{
	t_matrix	*new_m;
	float		*value;
	int			i;
	
	new_m = create_matrix(m->r - 1, m->c - 1);
	
	value = malloc(sizeof(int) * ((m->r - 1) * (m->c - 1)));
	i = 0;
	while (i < m->r * m->c)
	{
		if (i >= r && i < r + m->c) // avoid la ligne -> FAUX 
			i++;
		else if (i == c + i) // avoid la colonne
			i++;
		else
		{
			value[i] = m->data[i];
			printf("%f\n", value[i]);
			i++;
		}
	}
	fill_matrix(new_m, value);
	print_matrix(new_m);
	return (new_m);
}