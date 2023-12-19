/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:09:14 by ulysseclem        #+#    #+#             */
/*   Updated: 2023/12/19 11:16:58 by ulysseclem       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_world set_world()
{
	t_world w;

	w.l.intensity = set_color(1, 1, 1); // test
	w.l.position = point( -10, 10, -10); // test
	w.count = 0;
	w.s = NULL;
	return(w);
}

void	sort_inter(t_inter *xs)
{
	t_inter tmp;
	int i;

	i = 0;
	while (i < xs[0].count -1)
	{
		if (xs[i].t > xs[i + 1].t)
		{
			tmp = xs[i];
			xs[i] = xs[i +1];
			xs[i + 1] = tmp;
		}
		i++;
	}
}

/* ************************************************************************** */
/*	Definis et sort toutes les intersection de rays et d'objets dans le world */
/* ************************************************************************** */

t_inter	*intersect_world(t_world w, t_ray r2)
{

	t_inter *xs;
	t_ray r;
	t_tuple s_t_r;
	xs = NULL;
	int i;
	int	test = 0;

	i = 0;
	while (i < w.count)
	{		
		r = trnsform_ray(r2, inverse(w.s[i].transform));
		s_t_r = sub_tuple(r.origin, point(0 ,0 , 0));
		w.s[i].a = dot_product(r.direction, r.direction);
		w.s[i].b = dot_product(r.direction, s_t_r) * 2;
		w.s[i].c = dot_product(s_t_r, s_t_r) - 1;
		w.s[i].d = pow(w.s[i].b, 2) - (4 * w.s[i].a * w.s[i].c);
		if (w.s[i].d >= 0)
			test += 2;
		i++;
	}
	if (test == 0)
		return (NULL);
	xs = malloc(sizeof(t_inter) * test);
	if (!xs)
		return (NULL);
	i = 0;
	int j = 0;
	xs[0].count = test;
	while (i < w.count)
	{
		if (w.s[i].d >= 0)
		{
			xs[j] = create_inter(((w.s[i].b * -1) - sqrt(w.s[i].d)) / (2 * w.s[i].a), w.s[i]); // premiere inter
			j++;
			xs[j] = create_inter(((w.s[i].b * -1) + sqrt(w.s[i].d)) / (2 * w.s[i].a), w.s[i]); // deuxieme inter
			j++;
		}
		i++;
	}
	xs->count = test;
	sort_inter(xs);
	return(xs);
}

/* ************************************************************************** */
/*	precompute pour trouver le Hit											  */
/* ************************************************************************** */
t_comps prepare_computation(t_inter xs, t_ray r)
{
	t_comps comps;

	comps.t = xs.t;
			printf("id %d\n", xs.object.id);
	comps.object = xs.object;
	comps.p = position_f(r, comps.t);
	comps.eyev = neg_tuple(r.direction);
	comps.normalv = normale_at(comps.object, comps.p);
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
	return (lightning(c.object.material, w.l, c.p, c.eyev, c.normalv));
}

t_color shade_hit_no_specular(t_world w, t_comps c)
{
	return (lightning_no_specular(c.object.material, w.l, c.p, c.normalv));
}

t_color	color_at(t_world w, t_ray r)
{	
	t_inter hit_xs;
	t_inter *xs;
	t_comps	c;
	
	xs = intersect_world(w, r);
	if (!xs) // aucune intersection trouve, color = noir.
		return (set_color(0, 0, 0));
	hit_xs = hit(xs);
	if (hit_xs.hit == false)
		return (set_color(0, 0, 0));
	c = prepare_computation(hit_xs, r);
	return (shade_hit(w, c));
}