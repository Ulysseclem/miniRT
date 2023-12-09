/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inverter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:36:16 by ulysseclem        #+#    #+#             */
/*   Updated: 2023/12/09 15:32:20 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix *submatrix(t_matrix *m, int r, int c)
{
	t_matrix	*new_m;
	float		*value;
	int			mul;
	int			i;
	int			j;
	
	new_m = create_matrix(m->r - 1, m->c - 1);
	value = malloc(sizeof(int) * ((m->r - 1) * (m->c - 1)));
	if (!value || !new_m)
		return (free(value), NULL);
	i = 0;
	j = -1;
	mul = 0;
	while (i < (m->r * m->c))
	{
		if (i == c + (m->c * mul)) // avoid la colonne
		{
			i++;
			mul++;
		}
		else if (i >= (r * m->c) && i < (r * m->c + m->c)) // avoid la ligne
			i++;
		else
		{
			value[++j] = m->data[i];
			i++;
		}
	}
	fill_matrix(new_m, value);
	free(value);
	return (new_m);
}

float determinant(t_matrix *m)
{

	float	det = 0;
	int		i = 0;

	if (m->c * m->r == 4)
		return(m->data[0]*m->data[3] - m->data[1]*m->data[2]);
	else
	{
		while (i < m->c)
		{
			det = det + (m->data[0 + i] * cofactor(m, 0, i));
			i++;
		}
	}
	return (det);
}

float minor(t_matrix *m, int r, int c)
{
	t_matrix	*sub;

	sub = submatrix(m, r, c);
	return (determinant(sub));
}

float cofactor(t_matrix *m, int r, int c)
{
	float nbr;
	
	nbr = minor(m, r, c);
	if ((r + c) % 2 == 0)
		return (nbr);
	else 
		return (nbr * -1);
}

t_matrix *inverse(t_matrix *m)
{
	t_matrix	*new_m;
	int			r;
	int			c;
	float		cof;
	
	r = 0;
	if (determinant(m) == 0) // Matrice non inversible
		return(NULL);
	new_m = create_matrix(m->r, m->c);
	while (r < m->r)
	{
		c = 0;
		while (c < m->c)
		{
			cof = cofactor(m, r, c);
			new_m->data[r + (c * m->c)] = cof / determinant(m); // R et C sont inverse pour accomplir la transposition
			c++;
		}
		r++;
	}
	return (new_m);
}