/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:51:13 by uclement          #+#    #+#             */
/*   Updated: 2023/12/18 13:40:30 by uclement         ###   ########.fr       */
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

# ifndef WIDTH
# define WIDTH 11
# endif

# ifndef HEIGHT
# define HEIGHT 11
# endif

# ifndef CENTER
# define CENTER 50
# endif

# ifndef PI
# define PI 3.1415
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

typedef struct s_sphere {
	t_tuple 	point;
	t_matrix 	*transform;
	t_material	material;
	int		id;
	float	a;
	float	b;
	float	c;
	float	d;
} t_sphere;

typedef struct s_world {
	t_sphere	*s;
	t_light		l;
	int			count;
} t_world;

typedef struct s_inter {
	float		t;
	t_sphere	object;
	int			count;
	bool		hit;
} t_inter;

typedef struct s_proj {
	t_tuple	pos;
	t_tuple	vel;
}	t_proj;

typedef struct s_env {
	t_tuple	grav;
	t_tuple	wind;
}	t_env;

typedef struct s_comps {
	t_sphere	object;
	float		t;
	t_tuple		p;
	t_tuple		eyev;
	t_tuple		normalv;
	bool		inside;
}	t_comps;

typedef struct s_camera {
	float			hsize;
	float			vsize;
	float		fov;
	t_matrix	*transform;
	float		half_width;
	float		half_height;
	float			pixel_size;
}	t_camera;


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
void	print_color(t_color	t);
t_tuple cross_product(t_tuple a, t_tuple b);
void	my_mlx_pixel_put(t_data *data, int x, int y, t_color color);

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
t_inter hit(t_inter *xs);
t_ray trnsform_ray(t_ray r, t_matrix *m);
void set_transform(t_sphere *s, t_matrix *m);
t_tuple position_f(t_ray r, float t);

//light & shading

t_tuple	normale_at(t_sphere s, t_tuple p);
t_tuple	reflect(t_tuple vector_in, t_tuple normal);
void	light(t_light *l, t_tuple position, t_color color);
t_material	material_default();
t_color lightning(t_material m, t_light l, t_tuple p, t_tuple eyev, t_tuple normalv);
t_color lightning_no_specular(t_material m, t_light l, t_tuple p, t_tuple normalv);

//world
t_world set_world();
t_inter	*intersect_world(t_world w, t_ray r2);
t_comps prepare_computation(t_inter xs, t_ray r);
t_color shade_hit(t_world w, t_comps c);
t_color shade_hit_no_specular(t_world w, t_comps c);
t_color	color_at(t_world w, t_ray r);

// view
t_matrix *view_transform(t_tuple from, t_tuple to, t_tuple up);
t_camera	camera(int hsize, int vsize, float fov);
t_ray	ray_for_pixel(t_camera c, float px, float py);
void	render(t_camera c, t_world w);

#endif