/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:09:14 by ulysseclem        #+#    #+#             */
/*   Updated: 2024/01/14 14:26:14 by ulysseclem       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

t_world set_world()
{
	t_world w;

	w.l.intensity = set_color(1, 1, 1); // test
	w.l.position = point( -10, 10, -10); // test
	w.count = 0;
	w.shape = NULL;
	return(w);
}

t_tuple	normale_at(t_shape s, t_tuple world_point)
{
	t_tuple object_point;
	t_tuple object_normal;
	t_tuple world_normal;
	t_matrix	*inverted;
	t_matrix	*transposed;
	
	inverted = inverse(s.transform);
	world_normal = vector(0, 0, 0);
	object_point = mul_matrix_tuple(inverted, world_point); // obtenir le point and object space
	object_normal = sub_tuple(object_point, world_normal);
	transposed = transp_matrix(inverted);
	world_normal = mul_matrix_tuple(transposed, object_normal);
	world_normal.w = 0;  // remettre le w a 0 (pour vecteur) car il risque d'avoir ete change.
	free_matrix(inverted);
	free_matrix(transposed);
	return(norm(world_normal));
}

t_comps prepare_computation(t_inter xs, t_ray r)
{
	t_comps comps;

	comps.t = xs.t;
	comps.shape = xs.shape;
	comps.p = position_f(r, comps.t);
	comps.eyev = neg_tuple(r.direction);
	comps.normalv = normale_at(comps.shape, comps.p);
	comps.over_p = add_tuple(comps.p, mul_sca_tuple(comps.normalv, 0.00001)); // pour regler l'acne
	if (dot_product(comps.normalv, comps.eyev) < 0) // Verifie si le ray n'origine pas de l'interieur de l'objet
	{
		comps.inside = true;
		comps.normalv = neg_tuple(comps.normalv);
	}
	else
		comps.inside = false;
	return (comps);
}

t_color shade_hit(t_world w, t_comps c)
{
	bool	shadowed;

	shadowed = is_shadowed(w, c.over_p);
	return (lightning(c.shape.material, w.l, c.p, c.eyev, c.normalv, shadowed));
}

t_color shade_hit_no_specular(t_world w, t_comps c) // enleve le specular
{
	bool	shadowed;

	shadowed = is_shadowed(w, c.over_p);
	return (lightning_no_specular(c.shape.material, w.l, c.p, c.normalv, shadowed));
}

t_color	color_at(t_world w, t_ray r)
{	
	t_inter hit_xs;
	t_inter *xs;
	t_comps	c;
	
	xs = inter_world(w, r);
	if (!xs) // aucune intersection trouve, color = noir.
		return (set_color(0, 0, 0));
	hit_xs = hit(xs);
	free(xs);
	if (hit_xs.hit == false)
		return (set_color(0, 0, 0));
	c = prepare_computation(hit_xs, r);
	return (shade_hit(w, c));
}