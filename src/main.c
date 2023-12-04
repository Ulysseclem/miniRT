/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:49:57 by uclement          #+#    #+#             */
/*   Updated: 2023/12/04 16:40:41 by uclement         ###   ########.fr       */
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

	nbr = (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
	return (nbr);
}

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
	*(unsigned int*)dst = RGBToHex(color);
}

void	print_tuple(t_tuple	t)
{
	printf("(%f, %f, %f, %d)\n", t.x, t.y, t.z, t.w);
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

	color = set_color(1, 0, 0);

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, LENGHT, HEIGHT, "Hello world!");
	img.img = mlx_new_image(mlx, LENGHT, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	p.pos = point(0, 1, 0);
	p.vel = mul_sca_tuple(norm(vector(1, 1.8, 0)), 11.25);
	e.grav = vector(0, -0.1, 0);
	e.wind = vector(-0.01, 0, 0);

	while (p.pos.y > 0)
	{
		p = tick(e, p);
		count++;
		my_mlx_pixel_put(&img, p.pos.x, HEIGHT - p.pos.y, color);
		// printf("%d\n", count);
	}
// // TEST MATRIX

	t_matrix	*m;
	t_matrix	*m2;
	t_matrix	*m3;

	float	value[16];

	value[0] = 1;
	value[1] = 2;
	value[2] = 3;
	value[3] = 4;
	value[4] = 2;
	value[5] = 4;
	value[6] = 4;
	value[7] = 2;
	value[8] = 8;
	value[9] = 6;
	value[10] = 4;
	value[11] = 1;
	value[12] = 0;
	value[13] = 0;
	value[14] = 0;
	value[15] = 1;

	m = create_matrix(4, 4);
	fill_matrix(m, value);
	m2 = identify_matrix(4, 4);
	m3 = transp_matrix(m2);
	print_matrix(m2);
	
	
// END TEST MATRIX



// TEST BULLET

// END TES BULLET

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return(0);
}