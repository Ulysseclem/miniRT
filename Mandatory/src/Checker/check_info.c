/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaharel <icaharel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:19:02 by uclement          #+#    #+#             */
/*   Updated: 2024/02/18 16:09:37 by icaharel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

int	check_a(char **line, const int n)
{
	static int	a = 0;
	int			size;

	size = len_2(line);
	if (ft_strlen(line[size - 1]) == 1)
		size--;
	if (a == 1)
		return (print_error("A - More than one ambient light", n), 0);
	if (size != 3)
		return (print_error("A - Wrong number of parameter", n), 0);
	if (!valid_range(line[1], 1, 0.0, 1.0))
		return (print_error("A - Ratio not respected", n), 0);
	if (!valid_rgb(line[2]))
		return (print_error("A - Color format not respected", n), 0);
	a++;
	return (1);
}

int	check_c(char **line, const int n)
{
	static int	c = 0;
	int			size;

	size = len_2(line);
	if (ft_strlen(line[size - 1]) == 1)
		size--;
	if (c == 1)
		return (print_error("C - More than one camera", n), 0);
	if (size != 4)
		return (print_error("C - Wrong number of parameter", n), 0);
	if (!valid_tuple(line[1], 0, 0))
		return (print_error("C - Position format not respected", n), 0);
	if (!valid_tuple(line[2], -1.0, 1.0))
		return (print_error("C - Vector format not respected", n), 0);
	if (!valid_range(line[3], 1, 0.0, 180.0))
		return (print_error("C - FOV format not respected", n), 0);
	c++;
	return (1);
}

int	check_l(char **line, const int n)
{
	static int	l = 0;
	int			size;

	size = len_2(line);
	if (ft_strlen(line[size - 1]) == 1)
		size--;
	if (l == 1)
		return (print_error("L - More than one spot light", n), 0);
	if (size < 3 || size > 4)
		return (print_error("L - Wrong number of parameter", n), 0);
	if (size == 4 && !valid_rgb(line[3]))
		return (print_error("L - Color format not respected", n), 0);
	if (!valid_tuple(line[1], 0, 0))
		return (print_error("L - Position format not respected", n), 0);
	if (!valid_range(line[2], 1, 0.0, 1.0))
		return (print_error("L - Ratio not respected", n), 0);
	l++;
	return (1);
}
