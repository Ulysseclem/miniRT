/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:51:13 by uclement          #+#    #+#             */
/*   Updated: 2023/12/09 17:49:51 by uclement         ###   ########.fr       */
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
# define LENGHT 900
# endif

# ifndef HEIGHT
# define HEIGHT 550
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

//test
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
t_matrix *matrix_rotation(float r);


#endif