/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:49:57 by uclement          #+#    #+#             */
/*   Updated: 2024/01/02 12:54:19 by uclement         ###   ########.fr       */
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
	long long int red;
	long long int green;
	long long int blue;
	long long int hex_value;

	red = (long long int)(c.r * 255);
	green = (long long int)(c.g * 255);
	blue = (long long int)(c.b * 255);
	red = (red < 0) ? 0 : (red > 255) ? 255 : red;
	green = (green < 0) ? 0 : (green > 255) ? 255 : green;
	blue = (blue < 0) ? 0 : (blue > 255) ? 255 : blue;
	hex_value = (red << 16) + (green << 8) + blue;
	return (hex_value);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, t_color color)
{
	char	*dst;

	if (x > WIDTH || y > HEIGHT)
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




int	handle_exit(t_prog *prog)
{
	mlx_destroy_window(prog->mlx, prog->win);
	mlx_destroy_display(prog->mlx);
	return (0);
}

int	handle_keypress(int key, t_prog *prog)
{
	if (key == XK_Escape)
	{
		handle_exit(prog);
	}
	return (0);
}



int main(void)
{
/* ************************************************************************** */
/*					LIBX LAUCNHER											  */
/* ************************************************************************** */
	t_prog prog;
	t_data	img;


	prog.mlx = mlx_init();
	prog.win = mlx_new_window(prog.mlx, WIDTH, HEIGHT, "Hello world!");
	img.img = mlx_new_image(prog.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

    clock_t start, end;
    double cpu_time_used;

	start = clock();

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

	// t_inter *xs;
	// t_ray	r;
	// t_sphere	s;
	// t_color		color;
	// t_tuple		ray_origin;
	// t_tuple 	position;
	// t_tuple 	normal;
	// t_tuple 	eye;
	// t_light l;
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
	// s.material.color = set_color(1, 0.2, 1);
	// // set_transform(&s, matrix_scaling(1, 0.5, 1));

	// l.position = point(10, -10, -10);
	// l.intensity = set_color (1, 1, 1);

	// y = 0;
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
	// 		{
	// 			normal = normale_at(xs->object, position_f(r, xs->t));
	// 			eye = neg_tuple(r.direction);
	// 			color = lightning(xs->object.material, l, position_f(r, xs->t), eye, normal);
	// 			// color = lightning_no_specular(xs->object.material, l, position_f(r, xs->t), normal);
	// 			my_mlx_pixel_put(&img, 300 - x,  HEIGHT - y, color);
	// 		}
	// 		x++;
	// 	}
	// 	y++;
	// }


/* ************************************************************************** */
/*					MAKING A SCENE											  */
/* ************************************************************************** */

	// t_world 	w;
	// t_ray		r;
	// t_color		c;
	// t_sphere	s1;
	// t_sphere	s2;

	// s1 = sphere();
	// s2 = sphere();
	
	// s1.material.color = set_color(0.8, 1.0, 0.6);
	// s1.material.ambiant = 1;
	// s1.material.diffuse = 0.7;
	// s1.material.specular = 0.2;
	
	// s2.transform = matrix_scaling(0.5, 0.5, 0.5);
	// s1.material.ambiant = 1;

	// w = set_world();
	// w.s = malloc(sizeof(t_sphere) * 2);
	// w.s[0] = s1;
	// w.s[1] = s2;
	// w.count = 2;
	// ray(&r, point(0, 0, 0.75), vector(0, 0, -1));
	// c = color_at(w, r);
	// print_color(c);

/* ************************************************************************** */
/*					VIEW TEST												  */
/* ************************************************************************** */

	// float fov;
	// t_camera c;
	// t_world	w;


	// t_sphere	f1;
	
	// f1 = sphere();
	// f1.transform = matrix_scaling(10, 0.01, 10);
	// f1.material = material_default();
	// f1.material.color = set_color(1, 0.9, 0.9);
	// f1.material.specular = 0;
	
	// t_sphere l_wall;
	
	// l_wall = sphere();
	// l_wall.transform = mul_matrix(mul_matrix(mul_matrix(matrix_translation(0, 0, 5), matrix_rotation_y(-45)), matrix_rotation_x(90)), matrix_scaling(10, 0.01, 10));
	// l_wall.material = f1.material;

	// t_sphere r_wall;
	
	// r_wall = sphere();
	// r_wall.transform = mul_matrix(mul_matrix(mul_matrix(matrix_translation(0, 0, 5), matrix_rotation_y(45)), matrix_rotation_x(90)), matrix_scaling(10, 0.01, 10));
	// r_wall.material = f1.material;
	
	// t_sphere middle;

	// middle = sphere();
	// middle.transform = mul_matrix(matrix_translation(-1, 0.5, 1), matrix_scaling(0.5, 0.5, 0.5));
	// middle.material = material_default();
	// middle.material.color = set_color(0.1, 1, 0.5);
	// middle.material.diffuse = 0.7;
	// middle.material.specular = 0.3;

	// t_sphere right;

	// right = sphere();
	// right.transform = mul_matrix(matrix_translation(-2, 0.8, -0.5), matrix_scaling(0.8, 0.8, 0.8));
	// right.material = material_default();
	// right.material.color = set_color(0.5, 1, 0.1);
	// right.material.diffuse = 0.7;
	// right.material.specular = 0.3;

	// t_sphere left;

	// left = sphere();
	// left.transform = mul_matrix(matrix_translation(0, 2, 0.5), matrix_scaling(0.5, 0.5, 0.5));
	// left.material = material_default();
	// left.material.color = set_color(1, 0.8, 0.1);
	// left.material.diffuse = 0.7;
	// left.material.specular = 0.3;



	// w = set_world();
	// w.s = malloc(sizeof(t_sphere) * 6);
	// w.s[0] = middle;
	// w.s[1] = right;
	// w.s[2] = left;
	// w.s[3] = f1;
	// w.s[4] = l_wall;
	// w.s[5] = r_wall;


	// w.count = 6;
	
	// fov = PI/3;
	// c = camera(WIDTH, HEIGHT, fov);
	// c.transform = view_transform(point(0,1.5,-5), point(0,1,0), vector(0,1,0));
	// render(c, w, &img);


/* ************************************************************************** */
/*					SHADOW TEST												  */
/* ************************************************************************** */
	//*******************
	// test 1
	//*******************
	
	// t_tuple	eyev = vector(0, 0, -1);
	// t_tuple	normalv = vector(0, 0 ,-1);
	// t_light l;
	// bool	in_shadow = true;
	// t_sphere s;

	// s.material = material_default();
	// light(&l, point(0, 0 ,-10), set_color(1, 1, 1));

	// print_color(lightning(s.material, l, point(0, 0, 0), eyev, normalv, in_shadow));

	//*******************
	//test 2
	//*******************
	
	// t_world 	w;
	// t_sphere	s1;
	// t_sphere	s2;

	// s1 = sphere();
	// s2 = sphere();
	
	// s1.material.color = set_color(0.8, 1.0, 0.6);
	// s1.material.ambiant = 1;
	// s1.material.diffuse = 0.7;
	// s1.material.specular = 0.2;
	
	// s2.transform = matrix_scaling(0.5, 0.5, 0.5);
	// s1.material.ambiant = 1;

	// w = set_world();
	// w.s = malloc(sizeof(t_sphere) * 2);
	// w.s[0] = s1;
	// w.s[1] = s2;
	// w.count = 2;

	// printf ("%d\n", is_shadowed(w, point(0, 10, 0)));
	// printf ("%d\n", is_shadowed(w, point(10, -10, 10)));
	// printf ("%d\n", is_shadowed(w, point(-20, 20, -20)));
	// printf ("%d\n", is_shadowed(w, point(-2, 2, -2)));

	//*******************
	//test 3
	//*******************

	// t_world 	w;
	// t_sphere	s1;
	// t_sphere	s2;

	// s1 = sphere();
	// s2 = sphere();
	
	// s1.material.color = set_color(0.8, 1.0, 0.6);
	// s1.material.ambiant = 1;
	// s1.material.diffuse = 0.7;
	// s1.material.specular = 0.2;
	
	// s2.transform = matrix_translation(0, 0, 1);

	// w = set_world();
	// w.s = malloc(sizeof(t_sphere) * 2);
	// w.s[0] = s1;
	// w.s[1] = s2;
	// w.count = 2;

	// t_ray	r;
	// r.direction = vector(0,0,-5);
	// r.origin = point(0,0,1);
	
	// t_inter i;
	// i.t = 5;
	// i.object = s2;

	// t_comps c;
	// c = prepare_computation(i, r);
	// if (c.over_p.z < -0.00001/2)
	// 	printf("true");
	// else
	// 	printf("false");
	// if (c.over_p.z < c.p.z)
	// 	printf("true");


/* ************************************************************************** */
/*					TEST PLANE												  */
/* ************************************************************************** */

	// t_sphere s;
	// t_inter *xs;
	// t_ray	ray;

	// ray.direction = vector(0, 0, 1);
	// ray.origin = point( 0, 0, -5);
	// s = sphere();
	// set_transform(&s, matrix_scaling(2,2,2));

	// xs = intersect (s, ray);
	// print_tuple(xs[0].object.saved_ray.origin);
	
	//test 2

	// t_world	w;
	// t_ray	r;
	// t_shape	*shape;
	// t_sphere s;
	// t_inter *xs;
	// t_sphere s2;

	// r.direction = vector(0, 0, 1);
	// r.origin = point(0, 0, -5);

	// shape = malloc(sizeof(t_shape) * 2);

	// shape[0] = test_shape();
	// s = sphere();
	// shape[0].sphere = s;

	// shape[1] = test_shape();
	// s2 = sphere();
	// shape[1].transform = matrix_scaling(0.5 ,0.5 , 0.5);
	// shape[1].sphere = s2;
	
	// w = set_world();
	// w.shape = shape;
	// w.count = 2;

	// xs = intersect_world(w, r);
	// if (!xs)
	// 	printf("NULL");
	// else
	// {
	// 	printf("test : %f\n", xs[0].t);
	// 	printf("test : %f\n", xs[1].t);
	// 	printf("test : %f\n", xs[2].t);
	// 	printf("test : %f\n", xs[3].t);
	// }

	// test 3

	float fov;
	t_camera c;
	t_world	w;
	t_shape	*shape;

	shape = malloc(sizeof(t_shape) * 6);
	shape[0] = test_shape();
	shape[1] = test_shape();
	shape[2] = test_shape();
	shape[3] = test_shape();
	shape[4] = test_shape();
	shape[5] = test_shape();

	t_sphere	f1;
	f1 = sphere();
	shape[3].transform = matrix_scaling(10, 0.01, 10);
	shape[3].material = material_default();
	shape[3].material.color = set_color(1, 0.9, 0.9);
	shape[3].material.specular = 0;
	shape[3].sphere = f1;
	
	t_sphere l_wall;
	l_wall = sphere();
	shape[4].transform = mul_matrix(mul_matrix(mul_matrix(matrix_translation(0, 0, 5), matrix_rotation_y(-45)), matrix_rotation_x(90)), matrix_scaling(10, 0.01, 10));
	shape[4].material = shape[0].material;
	shape[4].sphere = l_wall;

	t_sphere r_wall;
	r_wall = sphere();
	shape[5].transform = mul_matrix(mul_matrix(mul_matrix(matrix_translation(0, 0, 5), matrix_rotation_y(45)), matrix_rotation_x(90)), matrix_scaling(10, 0.01, 10));
	shape[5].material = shape[0].material;
	shape[5].sphere = r_wall;

	t_sphere middle;
	middle = sphere();
	shape[0].transform = mul_matrix(matrix_translation(-1, 0.5, 1), matrix_scaling(0.5, 0.5, 0.5));
	shape[0].material = material_default();
	shape[0].material.color = set_color(0.1, 1, 0.5);
	shape[0].material.diffuse = 0.7;
	shape[0].material.specular = 0.3;
	shape[0].sphere = middle;

	t_sphere right;
	right = sphere();
	shape[1].transform = mul_matrix(matrix_translation(-2, 0.8, -0.5), matrix_scaling(0.8, 0.8, 0.8));
	shape[1].material = material_default();
	shape[1].material.color = set_color(0.5, 1, 0.1);
	shape[1].material.diffuse = 0.7;
	shape[1].material.specular = 0.3;
	shape[1].sphere = right;


	t_sphere left;
	left = sphere();
	shape[2].transform = mul_matrix(matrix_translation(0, 2, 0.5), matrix_scaling(0.5, 0.5, 0.5));
	shape[2].material = material_default();
	shape[2].material.color = set_color(1, 0.8, 0.1);
	shape[2].material.diffuse = 0.7;
	shape[2].material.specular = 0.3;
	shape[2].sphere = left;


	w = set_world();
	w.count = 6;
	w.shape = shape;
	fov = PI/3;
	c = camera(WIDTH, HEIGHT, fov);
	c.transform = view_transform(point(0,1.5,-5), point(0,1,0), vector(0,1,0));
	render(c, w, &img);
	

/* ************************************************************************** */
/*					END TEST											  */
/* ************************************************************************** */
	mlx_put_image_to_window(prog.mlx, prog.win, img.img, 0, 0);

	// mlx_hook(prog.mlx, KeyPress, KeyPressMask, &handle_keypress, &prog);
	// mlx_hook(prog.mlx, 17, 1L << 1, &handle_exit, &prog);

	
	end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("CPU time used: %f seconds\n", cpu_time_used);


	
	mlx_loop(prog.mlx);
	return(0);
}