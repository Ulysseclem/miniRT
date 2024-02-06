/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:23:12 by uclement          #+#    #+#             */
/*   Updated: 2024/02/06 10:32:56 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"


void test()
{
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
	// middle.transform = mul_matrix(	// t_world w;
	// t_ray	ray;
	// t_shape *shape;
	// t_sphere s1;
	// t_sphere s2;
	// t_inter	*xs;
	
	// shape = malloc(sizeof(t_shape) * 2);
	// shape[0] = test_shape();
	// shape[1] = test_shape();
	// s1 = sphere();
	// s2 = sphere();
	// shape[0].sphere = s1;
	// shape[1].sphere = s2;


	// w = set_world();
	// w.count = 2;
	// w.shape = shape;

	// ray.direction = vector(0, 0 ,1);
	// ray.origin = point(0, 0 , -5);

	// xs = inter_world(w, ray);
	// (void)xs;
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

	//test 5
	
	// float fov;
	// t_camera c;
	// t_world	w;
	// t_shape *shape;

	// shape = malloc(sizeof(t_shape) * 3);
	// shape[0] = init_shape("sphere"); // TYPEDEF enumeration
	// shape[1] = init_shape("plane");
	// shape[2] = init_shape("plane");
	// shape[3] = init_shape("plane");
	// shape[4] = init_shape("sphere");
	// shape[5] = init_shape("sphere");

	// free_matrix(shape[3].transform);
	// shape[3].transform = matrix_scaling(10, 0.01, 10);
	// shape[3].material = material_default();
	// shape[3].material.color = set_color(1, 0.9, 0.9);
	// shape[3].material.specular = 0;

	// free_matrix(shape[4].transform);
	// shape[4].transform = mul_matrix(mul_matrix(mul_matrix(matrix_translation(0, 0, 5), matrix_rotation_y(-45)), matrix_rotation_x(90)), matrix_scaling(10, 0.01, 10));
	// shape[4].material = shape[0].material;

	// free_matrix(shape[5].transform);
	// shape[5].transform = mul_matrix(mul_matrix(mul_matrix(matrix_translation(0, 0, 5), matrix_rotation_y(45)), matrix_rotation_x(90)), matrix_scaling(10, 0.01, 10));
	// shape[5].material = shape[0].material;

	// free_matrix(shape[1].transform);
	// shape[1].transform = mul_matrix(matrix_translation(-2, 0.8, -0.5), matrix_scaling(0.8, 0.8, 0.8));
	// shape[1].material = material_default();
	// shape[1].material.color = set_color(0.5, 1, 0.1);
	// shape[1].material.diffuse = 0.7;

	// free_matrix(shape[2].transform);
	// shape[2].transform = mul_matrix(matrix_translation(-1, 0.8, 0.5), matrix_scaling(0.5, 0.5, 0.5));
	// shape[2].material = material_default();
	// shape[2].material.color = set_color(1, 0.8, 0.1);
	// shape[2].material.diffuse = 0.7;
	
	// free_matrix(shape[0].transform);
	// shape[0].transform = mul_matrix(matrix_translation(-0.5, 10/10, 0), matrix_scaling(0.5, 0.5, 0.5));
	// shape[0].material = material_default();
	// shape[0].material.color = set_color(0.1, 1, 0.5);
	// shape[0].material.diffuse = 0.7;

	// // free_matrix(shape[1].transform);
	// shape[1].transform = mul_matrix( matrix_translation(0, 0, 3), matrix_rotation_x(-90));
	// // print_matrix(shape[1].transform);
	// shape[1].material = material_default();
	// shape[1].material.color = set_color(0, 0, 1);
	// shape[1].material.diffuse = 0.7;

	// free_matrix(shape[1].transform);
	// shape[1].transform =matrix_translation(0, 0, 0);
	// print_matrix(shape[2].transform);
	// shape[1].material = material_default();
	// shape[1].material.color = set_color(1, 0, 0);
	// shape[1].material.diffuse = 0.7;

	// free_matrix(shape[2].transform);
	// shape[2].transform = mul_matrix(mul_matrix(matrix_translation(2, 0, 0), matrix_rotation_x(-90)),matrix_rotation_z(90) );
	// print_matrix(shape[3].transform);
	// shape[2].material = material_default();
	// shape[2].material.color = set_color(1, 1, 1);
	// shape[2].material.diffuse = 0.7;

	// w = set_world();
	// w.shape = shape;
	// w.count = 3;
	
	// fov = PI/3;
	// c = camera(WIDTH, HEIGHT, fov);	
	// c.transform = view_transform(point(-4, 1, 2), point(0,1,2), vector(0,1,0));
	// render(c, w, &img);
	
	// free_matrix(shape[0].transform);
	// free_matrix(shape[1].transform);
	// free_matrix(shape[2].transform);
	// free_matrix(c.transform);
	

	/* ************************************************************************** */
	/*					TEST PLANE											  */
	/* ************************************************************************** */

	// t_plane p = plane();
	// t_shape	shape;
	// t_ray	r;
	// t_inter *xs;

	// ray(&r, point(0,1,0), vector(0, -1, 0));
	// shape = init_shape("plane"); // TYPEDEF enumeration
	// shape.plane = p;
	// xs = plane_intersect(&shape, r);
	// if(!xs)
	// 	return 0;
	// printf("%ftest \n ", xs[0].t);
	// print_xs(xs);

	// print_tuple(n1);


	// test camera anngl
	
	float fov;
	t_camera c;
	t_world	w;
	t_shape *shape;

	shape = malloc(sizeof(t_shape) * 4);
	shape[0] = init_shape("sphere"); // TYPEDEF enumeration
	shape[1] = init_shape("sphere");
	shape[2] = init_shape("sphere");
	shape[3] = init_shape("sphere");
	// shape[4] = init_shape("sphere");
	// shape[5] = init_shape("sphere");
	// shape[6] = init_shape("sphere");
	// shape[7] = init_shape("sphere");


	// free_matrix(shape[3].transform);
	// shape[3].transform = matrix_scaling(10, 0.01, 10);
	// shape[3].material = material_default();
	// shape[3].material.color = set_color(1, 0.9, 0.9);
	// shape[3].material.specular = 0;

	// free_matrix(shape[4].transform);
	// shape[4].transform = mul_matrix(mul_matrix(mul_matrix(matrix_translation(0, 0, 5), matrix_rotation_y(-45)), matrix_rotation_x(90)), matrix_scaling(10, 0.01, 10));
	// shape[4].material = shape[0].material;

	// free_matrix(shape[5].transform);
	// shape[5].transform = mul_matrix(mul_matrix(mul_matrix(matrix_translation(0, 0, 5), matrix_rotation_y(45)), matrix_rotation_x(90)), matrix_scaling(10, 0.01, 10));
	// shape[5].material = shape[0].material;

	// free_matrix(shape[1].transform);
	// shape[1].transform = mul_matrix(matrix_translation(-2, 0.8, -0.5), matrix_scaling(0.8, 0.8, 0.8));
	// shape[1].material = material_default();
	// shape[1].material.color = set_color(0.5, 1, 0.1);
	// shape[1].material.diffuse = 0.7;

	// free_matrix(shape[2].transform);
	// shape[2].transform = mul_matrix(matrix_translation(-1, 0.8, 0.5), matrix_scaling(0.5, 0.5, 0.5));
	// shape[2].material = material_default();
	// shape[2].material.color = set_color(1, 0.8, 0.1);
	// shape[2].material.diffuse = 0.7;
	
	// free_matrix(shape[0].transform);
	shape[0].transform = matrix_translation(0, 0, 10);
	shape[0].material = material_default();
	shape[0].material.color = set_color(0.1, 1, 0.5);
	shape[0].material.diffuse = 0.7;

	// free_matrix(shape[1].transform);
	shape[1].transform =  matrix_translation(0, 0, -10);
	shape[1].material = material_default();
	shape[1].material.color = set_color(1, 0.1, 0.5);
	shape[1].material.diffuse = 0.7;

	// free_matrix(shape[2].transform);
	shape[2].transform = matrix_translation(5, 0, 10);
	shape[2].material = material_default();
	shape[2].material.color = set_color(1, 0.1, 1);
	shape[2].material.diffuse = 0.7;

	// free_matrix(shape[2].transform);
	shape[3].transform = matrix_translation(-5, 0, 10);
	shape[3].material = material_default();
	shape[3].material.color = set_color(1, 1, 1);
	shape[3].material.diffuse = 0.7;
	
	// free_matrix(shape[4].transform);
	// shape[4].transform = mul_matrix(matrix_translation(1, 0, 0), matrix_scaling(0.5, 0.5, 0.5));
	// shape[4].material = material_default();
	// shape[4].material.color = set_color(0.1, 1, 0.5);
	// shape[4].material.diffuse = 0.7;

	// free_matrix(shape[5].transform);
	// shape[5].transform = mul_matrix(matrix_translation(1, 0, 0), matrix_scaling(0.5, 0.5, 0.5));
	// shape[5].material = material_default();
	// shape[5].material.color = set_color(0.1, 1, 0.5);
	// shape[5].material.diffuse = 0.7;

	// free_matrix(shape[6].transform);
	// shape[6].transform = mul_matrix(matrix_translation(1, 0, 0), matrix_scaling(0.5, 0.5, 0.5));
	// shape[6].material = material_default();
	// shape[6].material.color = set_color(0.1, 1, 0.5);
	// shape[6].material.diffuse = 0.7;

	// free_matrix(shape[7].transform);
	// shape[7].transform = mul_matrix(matrix_translation(1, 0, 0), matrix_scaling(0.5, 0.5, 0.5));
	// shape[7].material = material_default();
	// shape[7].material.color = set_color(0.1, 1, 0.5);
	// shape[7].material.diffuse = 0.7;




	// TEST PATTERN

	// t_color white = set_color (1,1,1);
	// t_color black = set_color(0,0,0);
	// t_pattern pat;

	// pat = stripe_pattern(white, black);

	// t_material mat;
	// mat.is_pat = true;
	// mat.pat = pat;
	// mat.ambiant = 1;
	// mat.diffuse = 0;
	// mat.specular = 0;
	// t_tuple eyev = vector(0,0,-1);
	// t_tuple normalv = vector(0,0,-1);
	// t_light light;
	// light.position = point(0,0,-10);
	// light.intensity = set_color(1,1,1);
	// t_color c1 = lightning(mat, light, point(0.9,0,0), eyev, normalv, false);
	// t_color c2 = lightning(mat, light, point(1.1,0,0), eyev, normalv, false);
	// print_color(c1);
	// print_color(c2);
}