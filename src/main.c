/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaharel <icaharel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:49:57 by uclement          #+#    #+#             */
/*   Updated: 2024/02/04 17:28:06 by icaharel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"


void set_objects(t_shape **shape, int n)
{
	while (n > 0)
	{
		(*shape)->transform = matrix_translation((*shape)->point.x/10, \
		(*shape)->point.y/10, (*shape)->point.z/10);
		n--;
	}
}


int	handle_exit(t_prog *prog)
{
	mlx_destroy_window(prog->mlx, prog->win);
	mlx_destroy_display(prog->mlx);
	return (0);
}

int	handle_keypress(int key, t_prog *prog)
{
	if (key == XK_Escape)
	{
		handle_exit(prog);
	}
	return (0);
}



int main(int argc, char **argv)
{
/* ************************************************************************** */
/*					LIBX LAUCNHER											  */
/* ************************************************************************** */
	t_prog prog;
	t_data	img;
    clock_t start, end;
    double cpu_time_used;
	start = clock();


	char **file;
	t_camera c;
	t_world	w;
	
    file = checkfile(argc, argv);
    if (!file)
		return (1);
    if (!initWorld(file, &w))
		return (free_2(file), 1);
	if (!initCamera(file, &c))
		return (free_2(file), 1); // gerer memoire world
	free_2(file);
 

 	printf("World:\n");
    printf("Light position: (%.2f, %.2f, %.2f)(x,y,z)\n", w.l.position.x, w.l.position.y, w.l.position.z);
    printf("Light color: %.2f, %.2f, %.2f (unit RGB)\n", w.l.color.r, w.l.color.g, w.l.color.b);
    printf("Ambiant color: %.2f, %.2f, %.2f (unit RGB)\n", w.ambiant.r, w.ambiant.g, w.ambiant.b);
    printf("Shape count: %d\n", w.count);
    printf("\nCamera:\n");
    printf("HSize: %.f\n", c.hsize);
    printf("VSize: %.2f\n", c.vsize);
    printf("FOV: %.2f\n", c.fov);
    printf("Half Width: %.2f\n", c.half_width);
    printf("Half Height: %.2f\n", c.half_height);
    printf("Pixel Size: %.2f\n", c.pixel_size);

	for (int j = 0; j < w.count; j++) {
		t_shape shape = w.shape[j];
		printf("Shape %d:\n", j);
		(void)shape;
		printf("	type: %d\n", shape.type);
		printf("	color: %.2f, %.2f, %.2f (unit RGB)\n", shape.material.color.r, shape.material.color.g, shape.material.color.b);
		printf("	position: (%.2f, %.2f, %.2f)(x,y,z)\n", shape.point.x, shape.point.y, shape.point.z);
	}

	prog.mlx = mlx_init();
	prog.win = mlx_new_window(prog.mlx, WIDTH, HEIGHT, "Hello world!");
	img.img = mlx_new_image(prog.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	render(c, w, &img);
	
	mlx_put_image_to_window(prog.mlx, prog.win, img.img, 0, 0);
	// mlx_hook(prog.mlx, KeyPress, KeyPressMask, &handle_keypress, &prog);
	// mlx_hook(prog.mlx, 17, 1L << 1, &handle_exit, &prog);

	end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("CPU time used: %f seconds\n", cpu_time_used);
	
	mlx_loop(prog.mlx);
	return(0);
}