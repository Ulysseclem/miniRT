/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:51:13 by uclement          #+#    #+#             */
/*   Updated: 2023/12/14 16:01:28 by ulysseclem       ###   ########.fr       */
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

# ifndef LENGHT
# define LENGHT 1000
# endif

# ifndef HEIGHT
# define HEIGHT 1000
# endif

# ifndef CENTER
# define CENTER 50
# endif


typedef struct s_tuple {
	float	x;
	float	y;
	float	z;
	int		w;
}	t_tuple;

typedef struct s_color {
	float	r;
	float	g;
	float	b;
}	t_color;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_matrix
{
	int	r;
	int	c;
	float	*data;
}	t_matrix;

typedef struct s_ray {
	t_tuple origin;
	t_tuple	direction;
}	t_ray;

typedef struct s_material {
	t_color	color;
	float ambiant;
	float diffuse;
	float specular;
	float shininess;
}	t_material;

typedef struct s_light {
	t_tuple	position;
	t_color	intensity;
}	t_light;

//test

typedef struct s_sphere {
	t_tuple 	point;
	t_matrix 	*transform;
	t_material	material;
    float 	radius;
	int		id;
} t_sphere;

typedef struct s_inter {
	float		t;
	t_sphere	object;
	int			count;
} t_inter;

typedef struct s_proj {
	t_tuple	pos;
	t_tuple	vel;
}	t_proj;

typedef struct s_env {
	t_tuple	grav;
	t_tuple	wind;
}	t_env;
//end test

//utils
bool	equal(float a, float b);
t_tuple	add_tuple(t_tuple a, t_tuple b);
t_tuple	mul_sca_tuple(t_tuple a, float mul);
t_tuple	point(float x, float y, float z);
t_tuple	sub_tuple(t_tuple a, t_tuple b);
float dot_product(t_tuple a, t_tuple b);
void	print_tuple(t_tuple	t);
t_tuple norm(t_tuple t);
t_tuple	vector(float x, float y, float z);
t_tuple	neg_tuple(t_tuple a);

//color
t_color	add_color(t_color a, t_color b);
t_color	sub_color(t_color a, t_color b);
t_color	mul_sca_color(t_color a, float mul);
t_color	mul_color(t_color a, t_color b);
t_color	set_color(float x, float y, float z);

//matrix
t_matrix	*create_matrix(int r, int c);
void		fill_matrix(t_matrix *m, float *value);
void		print_matrix(t_matrix *matrix);
int			equal_matrix(t_matrix *a, t_matrix *b);
t_matrix *mul_matrix(t_matrix *a, t_matrix *b);
t_tuple	mul_matrix_tuple(t_matrix *a, t_tuple b);
t_matrix *identify_matrix(int r, int c);
t_matrix	*transp_matrix(t_matrix *m);

// matrix inverter
float determinant(t_matrix *m);
t_matrix *submatrix(t_matrix *m, int r, int c);
float minor(t_matrix *m, int r, int c);
float cofactor(t_matrix *m, int r, int c);
t_matrix *inverse(t_matrix *m);

// matrix tranformation
t_matrix *matrix_translation(float x, float y, float z);
t_matrix *matrix_scaling(float x, float y, float z);
float	d_to_r(float deg);
t_tuple matrix_rotation(t_tuple t, float x, float y, float z);
t_matrix *matrix_shearing(float xy, float xz, float yx, float yz, float zx, float zy);
t_matrix *matrix_rotation_x(float r);
t_matrix *matrix_rotation_y(float r);
t_matrix *matrix_rotation_z(float d);

//ray
void 	ray(t_ray *r, t_tuple p, t_tuple v);
// float	discriminant(t_ray r, float a, float b, t_tuple s_t_r);
t_inter	*intersect(t_sphere s, t_ray r2);
t_sphere sphere();
t_inter	create_inter(float t, t_sphere s);
t_inter *intersections(int count, t_inter *inter);
t_inter *hit(t_inter *xs);
t_ray trnsform_ray(t_ray r, t_matrix *m);
void set_transform(t_sphere *s, t_matrix *m);
t_tuple position_f(t_ray r, float t);

//light & shading

t_tuple	normale_at(t_sphere s, t_tuple p);
t_tuple	reflect(t_tuple vector_in, t_tuple normal);
t_light	light(t_tuple position, t_color color);
t_material	material_default();
t_color lightning(t_material m, t_light l, t_tuple p, t_tuple eyev, t_tuple normalv);



#endif