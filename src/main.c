/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:49:57 by uclement          #+#    #+#             */
/*   Updated: 2023/12/14 16:03:07 by ulysseclem       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* ************************************************************************** */
/*					Magrnitude & norm pour normer des tuples				  */
/* ************************************************************************** */
float magnitude(t_tuple t)
{
	return sqrt(t.x * t.x + t.y * t.y + t.z * t.z + t.w * t.w);
}

t_tuple norm(t_tuple t)
{
	float mag = magnitude(t);

	if (mag != 0)
	{
		t.x = t.x / mag;
		t.y = t.y / mag;
		t.z = t.z / mag;
		t.w = t.w / mag;
	}
	return (t);
}

/* ************************************************************************** */
/*					Cree les tuples Point & Vecteur							  */
/* ************************************************************************** */
t_tuple	point(float x, float y, float z)
{
	t_tuple p;
	
	p.x = x;
	p.y = y;
	p.z = z;
	p.w = 1;
	return (p);
}

t_tuple	vector(float x, float y, float z)
{
	t_tuple v;
	
	v.x = x;
	v.y = y;
	v.z = z;
	v.w = 0;
	return (v);
}

/* ************************************************************************** */
/*					Arithmetie de Tuple (+, -, *, neg)						  */
/* ************************************************************************** */
t_tuple	add_tuple(t_tuple a, t_tuple b)
{
	t_tuple c;
	
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	c.w = a.w + b.w;
	// if (c.w == 2)
	// {
	// 	perror("w = 2");
	// 	exit(1);
	// }
	return(c);
}

t_tuple	sub_tuple(t_tuple a, t_tuple b)
{
	t_tuple c;
	
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	c.w = a.w - b.w;
	// if (c.w == -1)
	// {
	// 	perror("w = -1");
	// 	exit(1);
	// }
	return(c);
}
t_tuple	neg_tuple(t_tuple a)
{	
	a.x *= -1;
	a.y *= -1;
	a.z *= -1;
	a.w *= -1;
	return(a);
}

t_tuple	mul_sca_tuple(t_tuple a, float mul)
{
	a.x *= mul;
	a.y *= mul;
	a.z *= mul;
	a.w *= mul;
	return (a);	
}

t_tuple cross_product(t_tuple a, t_tuple b)
{
	t_tuple c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return(c);
}

float dot_product(t_tuple a, t_tuple b)
{
	float nbr;

	nbr = (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
	return (nbr);
}

/* ************************************************************************** */
/*					Permet de verifier l'egalite des floats					  */
/* ************************************************************************** */
bool	equal(float a, float b)
{
	float epsilon;

	epsilon = 0.00001;
	if ((a - b) < epsilon)
		return true;
	else
		return false;
}

bool	equal_tuple(t_tuple a, t_tuple b)
{
	if (equal(a.x, b.x) && equal(a.y, b.y) && equal(a.z, b.z))
		return true;
	else
		return false;
}

/* ************************************************************************** */
/*					gestion des couleurs									  */
/* ************************************************************************** */
int RGB_to_hex(t_color c) 
{
	int red;
	int green;
	int blue;
	int hex_value;

	red = (int)(c.r * 255);
	green = (int)(c.g * 255);
	blue = (int)(c.b * 255);
	red = (red < 0) ? 0 : (red > 255) ? 255 : red;
	green = (green < 0) ? 0 : (green > 255) ? 255 : green;
	blue = (blue < 0) ? 0 : (blue > 255) ? 255 : blue;
	hex_value = (red << 16) + (green << 8) + blue;
	return (hex_value);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, t_color color)
{
	char	*dst;

	if (x > LENGHT || y > HEIGHT)
	{
		printf("pixel out of bound");
		return;
	}
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = RGB_to_hex(color);
}

/* ************************************************************************** */
/*					Pour le test BULLET										  */
/* ************************************************************************** */
// t_proj tick(t_env env, t_proj proj)
// {
// 	t_proj	new_proj;

// 	new_proj.pos = add_tuple(proj.pos, proj.vel);
// 	new_proj.vel = add_tuple(add_tuple(proj.vel, env.grav), env.wind);
// 	return (new_proj);
// }

void	print_tuple(t_tuple	t)
{
	printf("(%f, %f, %f, %d)\n", t.x, t.y, t.z, t.w);
}

void	print_color(t_color	t)
{
	printf("(%f, %f, %f)\n", t.r, t.g, t.b);
}




int main(void)
{
/* ************************************************************************** */
/*					LIBX LAUCNHER											  */
/* ************************************************************************** */
	void	*mlx;
	void	*mlx_win;
	t_data	img;


	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, LENGHT, HEIGHT, "Hello world!");
	img.img = mlx_new_image(mlx, LENGHT, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

/* ************************************************************************** */
/*					TEST BULLET												  */
/* ************************************************************************** */
	// t_color color;
	// int		count = 0;
	// t_proj	p;
	// t_env	e;

	// color = set_color(1, 0, 0);
	// p.pos = point(0, 1, 0);
	// p.vel = mul_sca_tuple(norm(vector(1, 1.8, 0)), 11.25);
	// e.grav = vector(0, -0.1, 0);
	// e.wind = vector(-0.01, 0, 0);
	// while (p.pos.y > 0)
	// {
	// 	p = tick(e, p);
	// 	count++;
	// 	my_mlx_pixel_put(&img, p.pos.x, HEIGHT - p.pos.y, color);
	// 	// printf("%d\n", count);
	// }

/* ************************************************************************** */
/*					TEST MATRIX	CLOCK										  */
/* ************************************************************************** */
	// t_tuple		p;
	// t_tuple		tmp;
	// t_color color;
	
	// int i = 0;
	// color = set_color(1, 0, 0);
	// p = point(0, 0, 0);
	
	// my_mlx_pixel_put(&img, CENTER - p.x, CENTER - p.z, color);
	// tmp = mul_matrix_tuple(matrix_translation(0, 0, 50), p);
	// my_mlx_pixel_put(&img, CENTER - tmp.x, CENTER - tmp.z, color);
	// print_tuple(tmp);
	
	// while (i < 360)
	// {
	// 	tmp = mul_matrix_tuple(matrix_rotation_y(1), tmp);
		// my_mlx_pixel_put(&img, CENTER - tmp.x, CENTER - tmp.z, color);
		// i++;
	// }
	// print_tuple(tmp);

/* ************************************************************************** */
/*					TEST CERCLE RAY											  */
/* ************************************************************************** */
	
	// t_inter *xs;
	// t_ray	r;
	// t_sphere	s;
	// t_color		color;
	// t_tuple		ray_origin;
	// t_tuple position;
	// float	y;
	// float	x;
	// float	w_y;
	// float	w_x;
	// float	half;
	// float 	pixel_size;    // Utile pour eviter que le prog prenne trop de temps
	// float 	wall_size = 7;
	// float	wall_z = 10;
	// float	canva_size = 200;

	// xs = NULL;
	// ray_origin = point(0, 0, -5);
	// pixel_size = wall_size / canva_size;
	// half = wall_size / 2;
	// s = sphere();
	// color = set_color(1, 0, 0);
	// y = 0;
	// // set_transform(&s, matrix_scaling(1, 0.5, 1));
	// while (y < canva_size)
	// {
	// 	w_y = half - pixel_size * y;
	// 	x = 0;
	// 	while (x < canva_size)
	// 	{
	// 		w_x = -half + pixel_size * x;
	// 		position = point(w_x, w_y, wall_z);
	// 		ray(&r, ray_origin, norm((sub_tuple(position, ray_origin))));
	// 		xs = intersect(s, r);
	// 		if (hit(xs))
	// 			my_mlx_pixel_put(&img, 300 - x,  300 - y, color);
	// 		x++;
	// 	}
	// 	y++;
	// }
	

/* ************************************************************************** */
/*					TEST LIGHT & SHADING									  */
/* ************************************************************************** */

	t_inter *xs;
	t_ray	r;
	t_sphere	s;
	t_color		color;
	t_tuple		ray_origin;
	t_tuple 	position;
	t_tuple 	normal;
	t_tuple 	eye;
	t_light l;
	float	y;
	float	x;
	float	w_y;
	float	w_x;
	float	half;
	float 	pixel_size;    // Utile pour eviter que le prog prenne trop de temps
	float 	wall_size = 7;
	float	wall_z = 10;
	float	canva_size = 200;

	xs = NULL;
	ray_origin = point(0, 0, -5);
	pixel_size = wall_size / canva_size;
	half = wall_size / 2;

	s = sphere();
	s.material.color = set_color(1, 0.2, 1);
	set_transform(&s, matrix_scaling(1, 0.8, 1));

	l.position = point(-10, 10, -10);
	l.intensity = set_color (1, 1, 1);

	y = 0;
	while (y < canva_size)
	{
		w_y = half - pixel_size * y;
		x = 0;
		while (x < canva_size)
		{
			w_x = -half + pixel_size * x;
			position = point(w_x, w_y, wall_z);
			ray(&r, ray_origin, norm((sub_tuple(position, ray_origin))));
			xs = intersect(s, r);
			if (hit(xs))
			{
				normal = normale_at(xs->object, position_f(r, xs->t));
				eye = neg_tuple(r.direction);
				color = lightning(xs->object.material, l, position_f(r, xs->t), eye, normal);
				my_mlx_pixel_put(&img, 300 - x,  300 - y, color);
			}
			x++;
		}
		y++;
	}

/* ************************************************************************** */
/*					END TEST											  */
/* ************************************************************************** */

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return(0);
}