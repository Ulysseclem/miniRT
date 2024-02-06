#include "minirt.h"
#include "struct.h"

t_color	str_to_color(const char *str)
{
	t_color		p;
	float		c;
	char		**tmp;

	tmp = ft_split(str, ',');
	if (tmp)
	{
		c = ft_strtof(tmp[0]);
		p.r = c / 255;
		c = ft_strtof(tmp[1]);
		p.g = c / 255;
		c = ft_strtof(tmp[2]);
		p.b = c / 255;
		free_2(tmp);
	}
	return (p);
}

t_material	str_to_material(const char *str, t_world *w)
{
	t_material	m;
	t_color c;
		
	c = str_to_color(str);
	m.ambiant = mul_color(c, w->ambiant);
	m.color = str_to_color(str);
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.shininess = 200;
	return (m);
}

t_tuple	str_to_point(const char *str)
{
	t_tuple		p;
	char		**tmp;

	tmp = ft_split(str, ',');
	if (tmp)
	{
		p.x = ft_strtof(tmp[0]);
		p.y = ft_strtof(tmp[1]);
		p.z = ft_strtof(tmp[2]);
		p.w = 1;
		free_2(tmp);
	}
	return (p);
}

t_tuple	str_to_vector(const char *str)
{
	t_tuple		v;
	char		**tmp;

	tmp = ft_split(str, ',');
	if (tmp)
	{
		v.x = ft_strtof(tmp[0]);
		v.y = ft_strtof(tmp[1]);
		v.z = ft_strtof(tmp[2]);
		v.w = 0;
		free_2(tmp);
	}
	return (v);
}
