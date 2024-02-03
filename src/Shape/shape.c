/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 12:49:30 by ulysseclem        #+#    #+#             */
/*   Updated: 2024/02/03 15:21:15 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"


// t_shape	init_shape(char *type)
// {
// 	t_shape shape;
	
// 	shape.transform = identify_matrix(4, 4); //no need if there is a transformation
// 	shape.material = material_default();
// 	shape.type = type;
// 	if (type == SPHERE)
// 		shape.sphere = sphere();
// 	else if (type == PLANE)
// 		shape.plane = plane();
// 	return(shape);
// }

t_material	material_default()
{
	t_material	m;

	m.color = set_color(1, 1, 1);
	m.ambiant = 0.1;
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.shininess = 200;
	return(m);
}