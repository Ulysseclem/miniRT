/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:08:52 by uclement          #+#    #+#             */
/*   Updated: 2024/02/12 13:15:13 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

int	checktype(char **line, int line_nbr)
{
	int		ret;

	ret = 0;
	if (strcmp(line[0], "A") == 0)
		ret = check_a(line, line_nbr);
	else if (strcmp(line[0], "C") == 0)
		ret = check_c(line, line_nbr);
	else if (strcmp(line[0], "L") == 0)
		ret = check_l(line, line_nbr);
	else if (strcmp(line[0], "sp") == 0)
		ret = check_sp(line, line_nbr);
	else if (strcmp(line[0], "pl") == 0)
		ret = check_pl(line, line_nbr);
	else if (strcmp(line[0], "cy") == 0)
		ret = check_cy(line, line_nbr);
	else
		return (printf("%d | Invalid ID\n", line_nbr), 0);
	return (ret);
}

int	checker(char *line)
{
	char		**s_line;
	static int	line_nbr = 0;
	int			size;

	line_nbr++;
	if (is_empty(line))
		return (1);
	s_line = ft_split(line, ' ');
	if (!s_line)
		return (0);
	size = ft_strlen(s_line[0]);
	if (size > 2 || size < 0)
		return (free_2(s_line), 0);
	if (!checktype(s_line, line_nbr))
		return (free_2(s_line), 0);
	return (free_2(s_line), 1);
}

int	openrt(int argc, char **argv)
{
	int	fd;
	int	n;

	if (argc != 2)
		return (printf("Error\nWrong number of arguments\n"), -1);
	n = ft_strlen(argv[1]);
	if (n < 4 || argv[1][n - 1] != 't' \
	|| argv[1][n - 2] != 'r' || argv[1][n - 3] != '.')
		return (printf("Error\nFile must end by \".rt\"\n"), -1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (printf("Error\nError while opening %s\n", argv[1]), -1);
	return (fd);
}

char	**checkfile(int argc, char **argv)
{
	char	**res;
	char	*line;
	int		fd;

	res = NULL;
	fd = openrt(argc, argv);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (!checker(line))
		{
			if (res)
				free_2(res);
			(free(line), exit(1));
		}
		if (!is_empty(line))
			add_string_to_array(&res, line);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), res);
}
