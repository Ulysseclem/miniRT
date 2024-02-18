#include "minirt.h"
#include "struct.h"

int valid_range(char *str, float min, float max)
{
    float  ratio;

    ratio = ft_strtof(str, 1, 1.0, 0);
    if (ratio > max || ratio < min)
        return(0);
    return (1);
}

int valid_float(char *str)
{
    int sign;

    sign = 0;
    if (*str == '-' || *str == '+')
        str++;
    while (*str)
    {
        if (sign == 0 && *str == '.')
            sign = 1;
        else if(!ft_isdigit(*str))
            return (0);
        str++;
    }
    return (1);
}

int valid_tuple(char *str,  float min, float max)
{
    char    **v;
    int     i;

    i = 0;
    v = ft_split(str, ',');
    if (!v)
        return (0);
    if (len_2(v) != 3)
        return (free_2(v), 0);
    while (v[i] && i++)
        if (!valid_float(v[i]))
                return (free_2(v), 0); 
    i = 0;
    if (min && max)
        while (v[i] && i++)
            if (!valid_range(v[i], min, max))
                return (free_2(v), 0); 
    free_2(v);
    return (1);
}

int valid_rgb(char *str)
{
    int        range;
    int        i;
    char       **color;

    color = ft_split(str, ',');
    if (!color)
        return (0);
    if (len_2(color) != 3)
        return (free_2(color), 0);
    i = 0;
    while (color[i])
    {
        if (color[i][0] == '\n')
            return (free_2(color), 0);
        range = atoi(color[i]);
        if (range > 255 || range < 0)
            return (free_2(color), 0);
        i++;
    }
    free_2(color);
    return (1);
}