/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 12:49:30 by ulysseclem        #+#    #+#             */
/*   Updated: 2024/01/25 12:14:42 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"


t_shape	init_shape(char *type)
{
	t_shape shape;
	
	shape.transform = identify_matrix(4, 4); //no need if there is a transformation
	shape.material = material_default();
	shape.type = type;
	if (strcmp(type, "sphere") == 0)
		shape.sphere = sphere();
	return(shape);
}

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