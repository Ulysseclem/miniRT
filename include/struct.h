/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:51:13 by uclement          #+#    #+#             */
/*   Updated: 2024/01/14 13:08:48 by ulysseclem       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include "minirt.h"

typedef struct s_prog {
	void		*mlx;
	void		*win;
}	t_prog;

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
	float	**data;
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
	int		id;
	float	a;
	float	b;
	float	c;
	float	d;
} t_sphere;

typedef struct s_inter t_inter;

typedef struct s_shape {
	t_matrix 	*transform;
	t_material	material;
	char *		type;
	t_sphere	sphere;
	t_inter		*xs;
}	t_shape;

typedef struct s_inter {
	float		t;
	int			count;
	bool		hit;
	t_shape		shape;
} t_inter;

typedef struct s_world {
	t_shape		*shape;
	t_light		l;
	int			count;
} t_world;

typedef struct s_proj {
	t_tuple	pos;
	t_tuple	vel;
}	t_proj;

typedef struct s_env {
	t_tuple	grav;
	t_tuple	wind;
}	t_env;

typedef struct s_comps {
	t_shape		shape;
	float		t;
	t_tuple		p;
	t_tuple		over_p;
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

#endif