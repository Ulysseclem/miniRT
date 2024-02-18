/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaharel <icaharel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:51:13 by uclement          #+#    #+#             */
/*   Updated: 2024/02/18 16:04:41 by icaharel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdint.h>
# include "struct.h"
# include <fcntl.h>
# include <unistd.h>
# define WIDTH 50
# define HEIGHT 50
# define PI 3.1415
# define EPSILON 0.0001
# define RED "\033[31m"
# define RESET "\033[0m"

/* ************************************************************************** */
/*								MATRIX										  */
/* ************************************************************************** */

//matrix
t_matrix	*create_matrix(int r, int c);
void		fill_matrix(t_matrix *m, float **value);
int			equal_matrix(t_matrix *a, t_matrix *b);
t_matrix	*mul_matrix(t_matrix *a, t_matrix *b);
t_tuple		mul_matrix_tuple(t_matrix *a, t_tuple b);
t_matrix	*identify_matrix(int r, int c);
t_matrix	*identify_matrix_reverse(int r, int c);
t_matrix	*transp_matrix(t_matrix *m);

// matrix inverter
t_matrix	*inverse(t_matrix *m);

// matrix tranformation
t_matrix	*matrix_translation(float x, float y, float z);
t_matrix	*matrix_scaling(float x, float y, float z);
t_tuple		matrix_rotation(t_tuple t, float x, float y, float z);
t_matrix	*matrix_rotation_x(float r);
t_matrix	*matrix_rotation_y(float r);
t_matrix	*matrix_rotation_z(float d);

/* ************************************************************************** */
/*								RAY										  	  */
/* ************************************************************************** */

// light & shading
t_tuple		reflect(t_tuple vector_in, t_tuple normal);
t_color		lightning(t_comps c, t_light l, bool in_shadow);
t_light		light(t_tuple position, t_color color);

// ray
void		ray(t_ray *r, t_tuple p, t_tuple v);
t_inter		hit(t_inter *xs);
t_ray		trnsform_ray(t_ray r, t_matrix *m);
void		set_transform(t_shape *shape, t_matrix *m);
t_tuple		position_f(t_ray r, float t);

// shadow
bool		is_shadowed(t_world w, t_tuple point);

/* ************************************************************************** */
/*								RENDER										  */
/* ************************************************************************** */

// camera
t_matrix	*view_transform(t_tuple from, t_tuple to, t_tuple up);
t_camera	camera(int hsize, int vsize, float fov);
t_ray		ray_for_pixel(t_world w, float px, float py);

// intersection
t_inter		*inter_world(t_world w, t_ray ray);
int			intersect_shape(t_shape *shape, t_ray ray, t_world w);
t_inter		create_inter_new(float nbr, t_shape shape);

// render
void		render(t_camera c, t_world w, t_data *img);
void		my_mlx_pixel_put(t_data *data, int x, int y, t_color color);
int			RGB_to_hex(t_color c);

// world
t_tuple		normale_at(t_shape s, t_tuple world_point, t_world w);
t_comps		prepare_computation(t_inter xs, t_ray r, t_world w);
t_color		shade_hit(t_world w, t_comps c);
t_color		color_at(t_world w, t_ray r);

/* ************************************************************************** */
/*								SHAPE										  */
/* ************************************************************************** */
//cylinder_inter.c
t_inter		*cylinder_intersect(t_shape *s, t_ray r, t_world w);

// shape_inter.c
t_inter		*sphere_intersect(t_shape *s, t_ray r, t_world w);
t_inter		*plane_intersect(t_shape *s, t_ray r, t_world w);

/* ************************************************************************** */
/*								TUPLES										  */
/* ************************************************************************** */

//tuples
t_tuple		point(float x, float y, float z);
t_tuple		vector(float x, float y, float z);
t_tuple		add_tuple(t_tuple a, t_tuple b);
t_tuple		mul_sca_tuple(t_tuple a, float mul);
t_tuple		sub_tuple(t_tuple a, t_tuple b);
float		dot_product(t_tuple a, t_tuple b);
t_tuple		neg_tuple(t_tuple a);
t_tuple		cross_product(t_tuple a, t_tuple b);
float		dist(t_tuple p1, t_tuple p2);

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
t_tuple		norm(t_tuple t);
float		magnitude(t_tuple t);
void		free_matrix(t_matrix *mat);
float		d_to_r(float deg);
void		bubble_sort(t_inter *xs, int n);

// utils_to_delete
void		print_xs(t_inter *xs);
void		print_tuple(t_tuple	t);
void		print_color(t_color	t);
void		print_matrix(t_matrix *matrix);

/* ************************************************************************** */
/*								PARSING										  */
/* ************************************************************************** */

//check.c
char		**checkfile(int argc, char **argv);

//check_info.c
int			check_a(char **line, const int n);
int			check_c(char **line, const int n);
int			check_l(char **line, const int n);

//check_shape.c
int			check_sp(char **line, const int n);
int			check_cy(char **line, const int n);
int			check_pl(char **line, const int n);

// validation.c
int			valid_rgb(char *str);
int			valid_float(char *str);
int			valid_positive_float(char *str);
int			valid_tuple(char *str, float min, float max);
int			valid_range(char *str, int nbr, float min, float max);

/* ************************************************************************** */
/*								PARSING										  */
/* ************************************************************************** */

//save.c
int			init(char **file, t_shape **s, t_camera *cam);
int			search(char **file, t_shape **s, t_world *w);
void		free_shape(t_shape *s, int nshapes);

//save_shape.c
int			init_sp(char **param, t_shape *shape, t_world *world);
int			init_pl(char **param, t_shape *shape, t_world *world);
int			init_cy(char **param, t_shape *shape, t_world *world);

//save_info.c
int			init_world(char **file, t_world *w);
int			init_camera(char **file, t_camera *c);
int			init_light(char **param, t_world *w);
int			init_ambiant(char **param, t_world *w);
int			init_cam(char **param, t_camera *c);

//save_matrix.c
t_matrix	*applies_movement(t_tuple direction, t_tuple pos);

// strto.c
t_color		str_to_color(const char *str, int *ret);
t_material	str_to_material(const char *str, t_world *w, int *ret);
t_tuple		str_to_point(const char *str, int *ret);
t_tuple		str_to_vector(const char *str, int *ret);
float		ft_strtof(const char *str, int sign, float decimal_place, \
int has_decimal);

//string_utils.c
int			ft_isdigit(int c);
int			len_2(char **tab);
void		free_2(char **tab);
int			is_empty(char *str);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s);
char		*ft_strndup(const char *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		print_error(const char *error, const int n);
int			ft_strncat(char *dest, char *src, unsigned int nb);
char		*ft_strncpy(char *dest, const char *src, unsigned int n);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			add_string_to_array(char ***array, const char \
			*str, int size, int i);
char		*get_next_line(int fd);
void		free_and_exit(t_world w);

#endif