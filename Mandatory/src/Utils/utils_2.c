/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:34:25 by uclement          #+#    #+#             */
/*   Updated: 2024/02/12 13:35:11 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

float	d_to_r(float deg)
{
	return ((deg / 180) * 3.141592);
}

void	swap(t_inter *xp, t_inter *yp)
{
	t_inter	temp;

	temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void	bubble_sort(t_inter *xs, int n)
{
	int		i;
	int		j;
	bool	swapped;

	swapped = false;
	i = 0;
	while (i < n - 1)
	{
		swapped = false;
		j = 0;
		while (j < n - i - 1)
		{
			if (xs[j].t > xs[j + 1].t)
			{
				swap(&xs[j], &xs[j + 1]);
				xs[j].count = n;
				swapped = true;
			}
			j++;
		}
		if (swapped == false)
			break ;
		i++;
	}
}