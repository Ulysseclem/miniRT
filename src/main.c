/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:49:57 by uclement          #+#    #+#             */
/*   Updated: 2023/12/04 22:46:16 by ulysseclem       ###   ########.fr       */
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
int RGB_to_hex(t_color c) {
    int scaledRed = (int)(c.r * 255);
    int scaledGreen = (int)(c.g * 255);
    int scaledBlue = (int)(c.b * 255);

    scaledRed = (scaledRed < 0) ? 0 : (scaledRed > 255) ? 255 : scaledRed;
    scaledGreen = (scaledGreen < 0) ? 0 : (scaledGreen > 255) ? 255 : scaledGreen;
    scaledBlue = (scaledBlue < 0) ? 0 : (scaledBlue > 255) ? 255 : scaledBlue;

    int hexValue = (scaledRed << 16) + (scaledGreen << 8) + scaledBlue;

    return hexValue;
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
t_proj tick(t_env env, t_proj proj)
{
	t_proj	new_proj;

	new_proj.pos = add_tuple(proj.pos, proj.vel);
	new_proj.vel = add_tuple(add_tuple(proj.vel, env.grav), env.wind);
	return (new_proj);
}

void	print_tuple(t_tuple	t)
{
	printf("(%f, %f, %f, %d)\n", t.x, t.y, t.z, t.w);
}

int main(void)
{
/* ************************************************************************** */
/*					LIBX LAUCNHER											  */
/* ************************************************************************** */
	// void	*mlx;
	// void	*mlx_win;
	// t_data	img;


	// mlx = mlx_init();
	// mlx_win = mlx_new_window(mlx, LENGHT, HEIGHT, "Hello world!");
	// img.img = mlx_new_image(mlx, LENGHT, HEIGHT);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
	// 							&img.endian);

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
/*					TEST MATRIX												  */
/* ************************************************************************** */
	t_matrix	*m;
	t_matrix	*m2;

	float	value[16];

	value[0] = 1;
	value[1] = 5;
	value[2] = 0;
	value[3] = -3;
	value[4] = 2;
	value[5] = 7;
	value[6] = 0;
	value[7] = 6;
	value[8] = -3;

	value[9] = 6;
	value[10] = 4;
	value[11] = 1;
	value[12] = 0;
	value[13] = 0;
	value[14] = 0;
	value[15] = 1;

	m = create_matrix(3, 3);
	fill_matrix(m, value);
	// print_matrix(m);
	m2 = submatrix(m, 0, 2);
	(void)m2;
/* ************************************************************************** */
/*					END TEST MATRIX											  */
/* ************************************************************************** */

	// mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	// mlx_loop(mlx);
	return(0);
}