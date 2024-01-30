#include "minirt.h"
#include "struct.h"

void free_shape(t_shape *s, int nshapes)
{
    for (int i = 0; i < nshapes; i++) {
        free(s[i].ptrType);
    }
    free(s);
}

int search(char **file, t_shape **s)
{
    int   i;
    int   j;
    char **line;

    i = 0;
    j = 0;
    while (file[i])
    {
        line = ft_split(file[i], ' ');
        if (strcmp(line[0], "sp") == 0)
            init_sp(line, &(*s)[j++]);
        else if (strcmp(line[0], "pl") == 0)
            init_pl(line, &(*s)[j++]);
        else if (strcmp(line[0], "cy") == 0)
            init_cy(line, &(*s)[j++]);
        free_2(line);
        i++;
    }
    return (1);
}

int init(char **file, t_shape **s)
{
    int   i;
    int   nshape;
    char    **line;

    i = 0;
    nshape = 0;
    while (file[i])
    {
        line = ft_split(file[i],' ');
        if (strcmp(line[0], "sp") == 0 || strcmp(line[0], "pl") == 0 || strcmp(line[0], "cy") == 0)
            nshape++;
        free_2(line);
        i++;
    }
    *s = malloc(sizeof(t_shape) * nshape);
    if (!*s)
        return(0);
    if (!search(file, s))
        return (free(*s), 0); //need to be free
    return (nshape);
}