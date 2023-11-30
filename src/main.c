/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:49:57 by uclement          #+#    #+#             */
/*   Updated: 2023/11/30 22:26:37 by ulysseclem       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

	nbr = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	return (nbr);
}

float magnitude(t_tuple t)
{
	return sqrt(t.x * t.x + t.y * t.y + t.z * t.z);
}

t_tuple norm(t_tuple t)
{
	float mag = magnitude(t);

	if (mag != 0) {
		t.x /= mag;
		t.y /= mag;
		t.z /= mag;
	}
	return (t);
}

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
	v.w = 1;
	return (v);
}

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
	a.x *= mul;
	a.z *= mul;
	// a.w *= mul; pas sur de celui la
	return (a);	
}

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

t_proj tick(t_env env, t_proj proj)
{
	t_proj	new_proj;

	new_proj.pos = add_tuple(proj.pos, proj.vel);
	new_proj.vel = add_tuple(add_tuple(proj.vel, env.grav), env.wind);
	return (new_proj);
}

int RGBToHex(t_color c) {
    // Scale the values from [0, 1] to [0, 255]
    int scaledRed = (int)(c.r * 255);
    int scaledGreen = (int)(c.g * 255);
    int scaledBlue = (int)(c.b * 255);

    // Ensure values are within the valid range [0, 255]
    scaledRed = (scaledRed < 0) ? 0 : (scaledRed > 255) ? 255 : scaledRed;
    scaledGreen = (scaledGreen < 0) ? 0 : (scaledGreen > 255) ? 255 : scaledGreen;
    scaledBlue = (scaledBlue < 0) ? 0 : (scaledBlue > 255) ? 255 : scaledBlue;

    // Combine RGB values into a single hexadecimal integer
    int hexValue = (scaledRed << 16) + (scaledGreen << 8) + scaledBlue;

    return hexValue;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, t_color color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = RGBToHex(color);
}

int main(void)
{
	t_proj	p;
	t_env	e;
	int		count = 0;
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_color color;

	color = set_color(0.33,-0.234,-0.600);
	mlx = mlx_init();
	
	mlx_win = mlx_new_window(mlx, 500, 500, "Hello world!");
	img.img = mlx_new_image(mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	p.pos = point(0, 1, 0);
	p.vel = vector(7, 3, 0);
	e.grav = vector(0, -0.1, 0);
	e.wind = vector(-0.01, 0, 0);

	while (p.pos.y > 0)
	{
		p = tick(e, p);
		count++;
		my_mlx_pixel_put(&img, p.pos.x, 500 - p.pos.y, color);
		printf("%d\n", count);
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return(0);
}