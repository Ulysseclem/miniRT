/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 12:49:30 by ulysseclem        #+#    #+#             */
/*   Updated: 2023/12/30 12:51:20 by ulysseclem       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	test_shape()
{
	t_shape shape;
	
	shape.transform = identify_matrix(4, 4);
	shape.material = material_default();
	
}