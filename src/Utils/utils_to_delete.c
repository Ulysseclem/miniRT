/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_to_delete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:08:54 by ulysseclem        #+#    #+#             */
/*   Updated: 2024/01/14 13:09:55 by ulysseclem       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

void	print_xs(t_inter *xs)
{
	int	i;
	i = 0;
	while (i < xs->count)
	{
		printf("xs : %f\n", xs[i].t);
		i++;
	}
}

void	print_tuple(t_tuple	t)
{
	printf("(%f, %f, %f, %d)\n", t.x, t.y, t.z, t.w);
}

void	print_color(t_color	t)
{
	printf("(%f, %f, %f)\n", t.r, t.g, t.b);
}

void print_matrix(t_matrix *matrix) 
{
	static int i = 0;
	printf("id : %d\n", i);
	i++;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%f\t", matrix->data[i][j]);
        }
        printf("\n");
    }
	printf("\n---------------\n");
}