/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaharel <icaharel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:19:14 by uclement          #+#    #+#             */
/*   Updated: 2024/02/18 16:09:55 by icaharel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

int	check_sp(char **line, const int n)
{
	int	size;

	size = len_2(line);
	if (ft_strlen(line[size - 1]) == 1)
		size--;
	if (size != 4)
		return (print_error("sp - Wrong number of parameter", n), 0);
	if (!valid_tuple(line[1], 0, 0))
		return (print_error("sp - Position format not respected", n), 0);
	if (!valid_positive_float(line[2]))
		return (print_error("sp - Diameter format not respected", n), 0);
	if (!valid_rgb(line[3]))
		return (print_error("sp - Color format not respected", n), 0);
	return (1);
}

int	check_pl(char **line, const int n)
{
	int	size;

	size = len_2(line);
	if (ft_strlen(line[size - 1]) == 1)
		size--;
	if (size != 4)
		return (print_error("pl - Wrong number of parameter", n), 0);
	if (!valid_tuple(line[1], 0, 0))
		return (print_error("pl - Position format not respected", n), 0);
	if (!valid_tuple(line[2], -1.0, 1.0))
		return (print_error("pl - Vector format not respected", n), 0);
	if (!valid_rgb(line[3]))
		return (print_error("pl - Color format not respected", n), 0);
	return (1);
}

int	check_cy(char **line, const int n)
{
	int	size;

	size = len_2(line);
	if (ft_strlen(line[size - 1]) == 1)
		size--;
	if (size != 6)
		return (print_error("cy - Wrong number of parameter", n), 0);
	if (!valid_tuple(line[1], 0, 0))
		return (print_error("cy - Position format not respected", n), 0);
	if (!valid_tuple(line[2], -1.0, 1.0))
		return (print_error("cy - Vector format not respected", n), 0);
	if (!valid_positive_float(line[3]))
		return (print_error("cy - Diameter format not respected", n), 0);
	if (!valid_positive_float(line[4]))
		return (print_error("cy - Height format not respected", n), 0);
	if (!valid_rgb(line[5]))
		return (print_error("cy - Color format not respected", n), 0);
	return (1);
}
