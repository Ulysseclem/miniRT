#include "minirt.h"
#include "struct.h"

void	print_error(const char *error, const int n)
{
	printf("Error\n\033[31m%d | %s\n\033[0m", n, error);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*al;
	unsigned int	i;
	unsigned int	n;

	i = 0;
	n = size * nmemb;
	al = malloc(size * nmemb);
	if (al == NULL)
		return (NULL);
	while (i < n)
	{
		*((unsigned char *) al + i) = 0;
		i++;
	}
	return (al);
}

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

float	ft_strtof(const char *str)
{
	int		sign;
	int		has_decimal;
	float	result;
	float	decimal_place;

	sign = 1;
	has_decimal = 0;
	result = 0.0;
	decimal_place = 1.0;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		result = result * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		has_decimal = 1;
		str++;
		while (ft_isdigit(*str))
		{
			result = result * 10.0 + (*str - '0');
			decimal_place *= 10.0;
			str++;
		}
	}
	if (has_decimal)
		result /= decimal_place;
	return (result * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = malloc(sizeof(char) * (n + 1));
	if (!dest)
		return (perror("Memory error, please retry"), NULL);
	while (s[i] && i < n)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	int		size;
	int		i;
	char	*str;

	i = 0;
	size = ft_strlen(s);
	str = malloc (sizeof(char) * (size + 1));
	if (!(str))
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*sub;

	i = 0;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub = ft_calloc(sizeof(char), len + 1);
	if (sub == NULL)
		return (NULL);
	while (len > 0)
	{
		sub[i] = s[start + i];
		len--;
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

void	free_2(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	len_2(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		i++;
	}
	return (i);
}
