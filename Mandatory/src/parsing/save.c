#include "minirt.h"
#include "struct.h"

void free_shape(t_shape *s, int nshapes)
{
    for (int i = 0; i < nshapes; i++) {
        free(s[i].ptrType);
    }
    free(s);
}

int	search(char **file, t_shape **s, t_world *w)
{
	int		i;
	int		j;
	int		ret;
	char	**line;

	i = 0;
	j = 0;
	ret = 0;
	while (file[i])
	{
		line = ft_split(file[i], ' ');
		if (strcmp(line[0], "A") == 0)
			ret = init_ambiant(line, w);
		else if (strcmp(line[0], "L") == 0)
			ret = init_light(line, w);
		free_2(line);
		i++;
	}
	i = 0;
	while (file[i])
	{
		line = ft_split(file[i], ' ');
		if (strcmp(line[0], "sp") == 0)
			ret = init_sp(line, &(*s)[j++], w);
		else if (strcmp(line[0], "pl") == 0)
			ret = init_pl(line, &(*s)[j++], w);
		else if (strcmp(line[0], "cy") == 0)
			ret = init_cy(line, &(*s)[j++], w);
		free_2(line);
		if (!ret)
			return (0); // gerer memoire
		i++;
	}
	return (1);
}

int	initWorld(char **file, t_world *w)
{
	int		i;
	int		nshape;
	char	**line;
	t_shape *s;

	i = 0;
	nshape = 0;
	while (file[i])
	{
		line = ft_split(file[i], ' ');
		if (strcmp(line[0], "sp") == 0 || strcmp(line[0], "pl") == 0
			|| strcmp(line[0], "cy") == 0)
			nshape++;
		free_2(line);
		i++;
	}
	s = malloc(sizeof(t_shape) * nshape);
	if (!s)
		return (0);
	if (!search(file, &s, w))
		return (free(s), 0); //need to be free
	w->shape = s;
	w->count = nshape;
	return (nshape);
}

int	initCamera(char **file, t_camera *c)
{
	int			i;
	int 		ret;
	char		**line;

	i = 0;
	ret = 0;
	while (file[i])
	{
		line = ft_split(file[i], ' ');
		if (strcmp(line[0], "C") == 0)
		{
			ret = init_cam(line, c);
		}
		free_2(line);
		i++;
	}
	return (ret);
}