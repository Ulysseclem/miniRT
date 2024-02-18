/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_inter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:13:20 by ulysseclem        #+#    #+#             */
/*   Updated: 2024/02/18 14:40:04 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

void	add_intersection(t_inter **xs, float t)
{
	if ((*xs)[0].t < 0)
		(*xs)[0].t = t;
	else if ((*xs)[1].t < 0)
		(*xs)[1].t = t;
}

int	check_cap(t_ray r, float t, float radius)
{
	float	x;
	float	z;

	x = r.origin.x + t * r.direction.x;
	z = r.origin.z + t * r.direction.z;
	if (x * x + z * z <= radius * radius)
		return (TRUE);
	else
		return (FALSE);
}

int	intersect_caps(t_cylinder *cy, t_ray r, t_inter *xs)
{
	float	t;
	float	t1;
	int		ret;

	ret = 0;
	t = (-r.origin.y) / r.direction.y;
	if (t >= 0 && check_cap(r, t, cy->diameter / 2))
	{
		add_intersection(&xs, t);
		ret++;
	}
	t1 = (cy->height - r.origin.y) / r.direction.y;
	if (t1 >= 0 && check_cap(r, t1, cy->diameter / 2))
	{
		add_intersection(&xs, t1);
		ret++;
	}
	return (ret);
}

int	intersect_body(t_cylinder *cy, t_ray r, t_inter *xs)
{
	float	t0;
	float	t1;
	float	y0;
	float	y1;

	t0 = (-cy->b - sqrt(cy->d)) / (2 * cy->a);
	y0 = r.origin.y + t0 * r.direction.y;
	t1 = (-cy->b + sqrt(cy->d)) / (2 * cy->a);
	y1 = r.origin.y + t1 * r.direction.y;
	if (t0 >= 0 && y0 >= 0 && y0 <= cy->height)
		add_intersection(&xs, t0);
	if (t1 >= 0 && y1 >= 0 && y1 <= cy->height)
		add_intersection(&xs, t1);
	return (1);
}

t_inter	*cylinder_intersect(t_shape *s, t_ray r, t_world w)
{
	t_inter		*xs;
	t_cylinder	*cy;

	cy = (t_cylinder *)s->ptr_type;
	xs = malloc(sizeof(t_inter) * 2);
	if (!xs)
		free_and_exit(w);
	xs[0] = create_inter_new(-1, *s);
	xs[1] = create_inter_new(-1, *s);
	cy->a = pow(r.direction.x, 2) + pow(r.direction.z, 2);
	if (equal(cy->a, 0))
	{
		if (intersect_caps(cy, r, xs))
			return (xs);
		else
			return (free(xs), NULL);
	}
	cy->b = 2 * (r.origin.x * r.direction.x + r.origin.z * r.direction.z);
	cy->c = pow(r.origin.x, 2) + pow(r.origin.z, 2) - pow(cy->diameter / 2, 2);
	cy->d = cy->b * cy->b - 4 * cy->a * cy->c;
	if (cy->d >= 0)
		intersect_body(cy, r, xs);
	if (!intersect_caps(cy, r, xs) && cy->d < 0)
		return (free(xs), NULL);
	return (xs);
}
