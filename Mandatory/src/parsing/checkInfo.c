/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkInfo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:19:02 by uclement          #+#    #+#             */
/*   Updated: 2024/02/12 12:19:03 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

int	check_a(char **line, const int n)
{
	static int	a = 0;

	if (a == 1)
		return (print_error("a - More than one ambient light", n), 0);
	if (len_2(line) != 3)
		return (print_error("a - Wrong number of parameter", n), 0);
	if (!valid_range(line[1], 0.0, 1.0))
		return (print_error("a - Ratio not respected", n), 0);
	if (!valid_rgb(line[2]))
		return (print_error("a - color format not respected", n), 0);
	a++;
	return (1);
}

int	check_c(char **line, const int n)
{
	static int	c = 0;

	if (c == 1)
		return (print_error("c - More than one camera", n), 0);
	if (len_2(line) != 4)
		return (print_error("c - Wrong number of parameter", n), 0);
	if (!valid_tuple(line[1], 0, 0))
		return (print_error("c - Position format not respected", n), 0);
	if (!valid_tuple(line[2], -1.0, 1.0))
		return (print_error("c - Vector format not respected", n), 0);
	if (!valid_range(line[3], 0.0, 180.0))
		return (print_error("c - FOV format not respected", n), 0);
	c++;
	return (1);
}

int	check_l(char **line, const int n)
{
	static int	l = 0;

	if (l == 1)
		return (print_error("l - More than one spot light", n), 0);
	if (len_2(line) != 4)
		return (print_error("l - Wrong number of parameter", n), 0);
	if (!valid_tuple(line[1], 0, 0))
		return (print_error("l - Position format not respected", n), 0);
	if (!valid_range(line[2], 0.0, 1.0))
		return (print_error("l - Ratio not respected", n), 0);
	l++;
	return (1);
}
