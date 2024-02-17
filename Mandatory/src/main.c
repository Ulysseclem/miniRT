/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaharel <icaharel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:49:57 by uclement          #+#    #+#             */
/*   Updated: 2024/02/17 15:41:31 by icaharel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

int	handle_exit(t_prog *prog)
{
	mlx_destroy_image(prog->mlx, prog->data.img);
	mlx_destroy_window(prog->mlx, prog->win);
	mlx_destroy_display(prog->mlx);
	free(prog->mlx);
	exit(0);
}

int	handle_keypress(int key, t_prog *prog)
{
	if (key == XK_Escape)
		handle_exit(prog);
	return (0);
}

int	main(int argc, char **argv)
{
	t_prog		prog;
	t_data		img;
	char		**file;
	t_camera	c;
	t_world		w;

	file = checkfile(argc, argv);
	if (!file)
		return (1);
	if (!init_world(file, &w))
		return (free_2(file), 1);
	if (!init_camera(file, &c))
		return (free_2(file), 1); // gerer memoire world
	prog.mlx = mlx_init();
	if (prog.mlx == NULL)
		return (1);
	prog.win = mlx_new_window(prog.mlx, WIDTH, HEIGHT, "miniRT!");
	img.img = mlx_new_image(prog.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
	&img.line_length, &img.endian);
	prog.data = img;
	render(c, w, &img);
	mlx_put_image_to_window(prog.mlx, prog.win, img.img, 0, 0);
	mlx_hook(prog.win, KeyPress, KeyPressMask, &handle_keypress, &prog);
	mlx_hook(prog.win, DestroyNotify, ButtonPressMask, &handle_exit, &prog);
	mlx_loop(prog.mlx);
	return (0);
}
