/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:51:13 by uclement          #+#    #+#             */
/*   Updated: 2024/01/25 12:01:56 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include "libft.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <mlx.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <time.h> // to remove
#include <stdint.h>
#include "struct.h"


# ifndef WIDTH
# define WIDTH 200
# endif

# ifndef HEIGHT
# define HEIGHT 100
# endif

# ifndef CENTER
# define CENTER 150
# endif

# ifndef PI
# define PI 3.1415
# endif

# ifndef EPSILON
# define EPSILON 0.0001
# endif

/* ************************************************************************** */
/*								MATRIX										  */
/* ************************************************************************** */

//matrix
t_matrix	*create_matrix(int r, int c);
void 		fill_matrix(t_matrix *m, float **value);
int			equal_matrix(t_matrix *a, t_matrix *b);
t_matrix 	*mul_matrix(t_matrix *a, t_matrix *b);
t_tuple		mul_matrix_tuple(t_matrix *a, t_tuple b);
t_matrix 	*identify_matrix(int r, int c);
t_matrix	*transp_matrix(t_matrix *m);

// matrix inverter
t_matrix* inverse(t_matrix *m);

// matrix tranformation
t_matrix 	*matrix_translation(float x, float y, float z);
t_matrix 	*matrix_scaling(float x, float y, float z);
t_tuple 	matrix_rotation(t_tuple t, float x, float y, float z);
t_matrix 	*matrix_shearing(float xy, float xz, float yx, float yz, float zx, float zy);
t_matrix 	*matrix_rotation_x(float r);
t_matrix 	*matrix_rotation_y(float r);
t_matrix 	*matrix_rotation_z(float d);


/* ************************************************************************** */
/*								RAY										  	  */
/* ************************************************************************** */

// light & shading
t_tuple		reflect(t_tuple vector_in, t_tuple normal);
void		light(t_light *l, t_tuple position, t_color color);
t_material	material_default();
t_color 	lightning(t_material m, t_light l, t_tuple p, t_tuple eyev, t_tuple normalv, bool in_shadow);
t_color 	lightning_no_specular(t_material m, t_light l, t_tuple p, t_tuple normalv, bool in_shadow);

// ray
void 		ray(t_ray *r, t_tuple p, t_tuple v);
t_inter 	hit(t_inter *xs);
t_ray 		trnsform_ray(t_ray r, t_matrix *m);
void 		set_transform(t_shape *shape, t_matrix *m);
t_tuple 		position_f(t_ray r, float t);

// shadow
bool		is_shadowed(t_world w, t_tuple point);


/* ************************************************************************** */
/*								RENDER										  */
/* ************************************************************************** */

// camera
t_matrix 	*view_transform(t_tuple from, t_tuple to, t_tuple up);
t_camera	camera(int hsize, int vsize, float fov);
t_ray		ray_for_pixel(t_camera c, float px, float py);

// intersection
t_inter		*inter_world(t_world w, t_ray ray);
void 		bubbleSort(t_inter *xs, int n); // FOR IN IT TO FIX
int 		intersect_shape(t_shape *shape, t_ray ray);
t_inter		create_inter_new(float nbr, t_shape shape);

// render
void		render(t_camera c, t_world w, t_data *img);
void		my_mlx_pixel_put(t_data *data, int x, int y, t_color color);
int 		RGB_to_hex(t_color c);

// world
t_world 	set_world();
t_tuple		normale_at(t_shape s, t_tuple world_point);
t_comps 	prepare_computation(t_inter xs, t_ray r);
t_color 	shade_hit(t_world w, t_comps c);
t_color 	shade_hit_no_specular(t_world w, t_comps c); // pas necessaire
t_color		color_at(t_world w, t_ray r);


/* ************************************************************************** */
/*								SHAPE										  */
/* ************************************************************************** */

// shape
t_shape		init_shape(char *type);
t_material	material_default();

// sphere
t_inter 	*sphere_intersect(t_shape *s, t_ray r);
t_sphere 	sphere();


/* ************************************************************************** */
/*								TUPLES										  */
/* ************************************************************************** */

//tuples
t_tuple		point(float x, float y, float z);
t_tuple		vector(float x, float y, float z);
t_tuple		add_tuple(t_tuple a, t_tuple b);
t_tuple		mul_sca_tuple(t_tuple a, float mul);
t_tuple		sub_tuple(t_tuple a, t_tuple b);
float 		dot_product(t_tuple a, t_tuple b);
t_tuple		neg_tuple(t_tuple a);
t_tuple 	cross_product(t_tuple a, t_tuple b);

//color
t_color		add_color(t_color a, t_color b);
t_color		sub_color(t_color a, t_color b);
t_color		mul_sca_color(t_color a, float mul);
t_color		mul_color(t_color a, t_color b);
t_color		set_color(float x, float y, float z);


/* ************************************************************************** */
/*								UTILS										  */
/* ************************************************************************** */

//utils
bool		equal(float a, float b);
bool		equal_tuple(t_tuple a, t_tuple b);
t_tuple 	norm(t_tuple t);
float 		magnitude(t_tuple t);
void 		free_matrix(t_matrix *mat);
float		d_to_r(float deg);


// utils_to_delete
void		print_xs(t_inter *xs);
void		print_tuple(t_tuple	t);
void		print_color(t_color	t);
void		print_matrix(t_matrix *matrix);

#endif