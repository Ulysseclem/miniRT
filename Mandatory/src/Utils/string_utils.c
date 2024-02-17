/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:55:14 by uclement          #+#    #+#             */
/*   Updated: 2024/02/17 18:51:54 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

int	ft_isspace(int c)
{
	if (c >= 9 && c <= 13)
		return (1);
	if (c == ' ')
		return (1);
	return (0);
}

int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	add_string_to_array(char ***array, const char *str)
{
	char	**new_array;
	int		size;
	int		i;

	i = 0;
	size = 0;
	if (*array)
		size = len_2(*array);
	size++;
	new_array = (char **)malloc((size + 1) * sizeof(char *));
	if (!new_array)
		return (perror("Memory error, please retry"), 0);
	if (*array)
	{
		while (i < size - 1)
		{
			new_array[i] = ft_strdup((*array)[i]);
			if (!new_array[i])
				return (free_2(new_array), 0);
			i++;
		}
	}
	new_array[size - 1] = ft_strdup(str);
	if (!new_array[size - 1])
		return (free_2(new_array), 0);
	new_array[size] = NULL;
	if (*array)
		free_2(*array);
	*array = new_array;
	return (1);
}

char	*ft_strncpy(char *dest, const char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

int	ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int	i;
	unsigned int	a;

	i = 0;
	a = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[a] != '\0' && a < nb)
	{
		dest[i + a] = src[a];
		a++;
	}
	dest[i + a] = '\0';
	return (a);
}
int len_2(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		i++;
	}
	return (i);
}