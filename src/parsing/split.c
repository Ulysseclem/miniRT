#include "minirt.h"
#include "struct.h"

int	count(char *str, char delimiter, int mode)
{
	int		i;

	i = 0;
	if (mode == 0)
		while (str[i] && str[i] != delimiter)
			i++;
	else
		while (str[i] && str[i] == delimiter)
			i++;
	return (i);
}

int	wordcount(char *str, char delimiter)
{
	int		n;
	int		i;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == delimiter)
			i += count(str + i, delimiter, TRUE);
		else
		{
			i += count(str + i, delimiter, FALSE);
			n++;
		}
	}
	return (n);
}

char	**ft_split(char *str, char delimiter)
{
	char	**result;
	int		size;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	size = wordcount(str, delimiter);
	result = malloc(sizeof(char *) * (size + 1));
	if (!result)
		return (NULL);
	while (str[i])
	{
		len = count(str + i, delimiter, FALSE);
		if (len > 0)
		{
			result[j] = ft_strndup(str + i, len);
			if (!result[j])
				return (free_2(result), NULL);
			i = i + len;
			j++;
		}
		else
			i++;
	}
	result[wordcount(str, delimiter)] = NULL;
	return (result);
}
