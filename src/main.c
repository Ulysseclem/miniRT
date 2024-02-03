/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:49:57 by uclement          #+#    #+#             */
/*   Updated: 2024/02/03 16:25:14 by uclement         ###   ########.fr       */
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


	prog.mlx = mlx_init();
	prog.win = mlx_new_window(prog.mlx, WIDTH, HEIGHT, "Hello world!");
	img.img = mlx_new_image(prog.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

    clock_t start, end;
    double cpu_time_used;
	start = clock();




	char **file;
	t_camera c;
    t_shape *shape;
	t_world	w;
	int n = 0;
	
	shape = NULL;
    file = checkfile(argc, argv);
    if (file)
    {
        n = init(file, &shape, &c);
		if (n)
		{
			for (int i = 0; i < n; i++) {
				printf("Shape %d:\n", i + 1);
				printf("Type: %d\n", shape[i].type);
        	}
		}
		free_2(file);
		if (!n)
			return (1);
    }
	else
		return (1);

	w = set_world();
	set_objects(&shape, n);
	w.shape = shape;
	w.count = n;
	
	// c.transform = view_transform(point(0, 1.5, -5), point(0,1,0), vector(0,1,0));
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