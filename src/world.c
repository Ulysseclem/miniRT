/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:09:14 by ulysseclem        #+#    #+#             */
/*   Updated: 2023/12/15 13:56:00 by ulysseclem       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_world set_world()
{
	t_world w;

	w.l = NULL;
	w.obj = NULL;
	return(w);
}



void	discriminant(t_ray r, t_discri *nbr)
{
	t_tuple s_t_r;

	s_t_r = sub_tuple(r.origin, point(0 ,0 , 0));
	nbr->a = dot_product(r.direction, r.direction);
	nbr->b = dot_product(r.direction, s_t_r) * 2;
	nbr->c = dot_product(s_t_r, s_t_r) - 1;
	nbr->d = pow(nbr->b, 2) - (4 * nbr->a * nbr->c);   // si positif = touche l'objet
}

void count_discri(t_discri *nbr, t_ray r, t_world *w)
{
	t_ray 	r_tmp;
	int		i;
	
	i = 0;
	print_matrix(w->obj[0].s.transform);
	printf("\n");
	print_matrix(w->obj[1].s.transform);
	while (i < w->obj->count)
	{
		r_tmp = trnsform_ray(r, inverse(w->obj[i].s.transform));
		discriminant(r_tmp, &w->obj[i].s.nbr);
		if (w->obj[i].s.nbr.d >= 0)
			nbr->count++;
		i++;
	}
	nbr->count *= 2;
}

t_inter	*intersect_world(t_world w, t_ray r)
{
	t_discri nbr;
	int		i;
	t_inter *xs;
	xs = NULL;

	nbr.count = 0;
	count_discri(&nbr, r, &w);
	if (nbr.count == 0)
		return (0);
	xs = malloc(sizeof(t_inter) * nbr.count);
	if (!xs)
		return (NULL);
	i = 0;
	int j = 0;
	while (i < nbr.count)
	{
		xs[i] = create_inter(((w.obj[j].s.nbr.b * -1) - sqrt(w.obj[j].d)) / (2 * w.obj[j].s.nbr.a), w.obj[j].s); // premiere inter
		printf("xs %d = %f \n",i, xs[i].t);
		xs[++i] = create_inter(((w.obj[j].s.nbr.b * -1) + sqrt(w.obj[j].d)) / (2 * w.obj[j].s.nbr.a), w.obj[j].s); // deuxieme inter
		printf("xs %d = %f\n",i, xs[i].t);
		i++;
		j++;
	}
	xs->count = nbr.count;
	return(xs);
}