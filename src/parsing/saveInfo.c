#include "minirt.h"
#include "struct.h"

t_color intense(float intensity, t_color color) // mul_sca_color
{
	t_color new_color;

	new_color.r = color.r * intensity;
	new_color.g = color.g * intensity;
	new_color.b = color.b * intensity;
	return (new_color);
}

t_light	light(t_tuple position, t_color color)
{
	t_light l;
	l.position = position;
	l.color = color;
	return (l);
}

int init_light(char **param, t_world *w)
{
	w->l = light(str_to_point(param[1]), mul_sca_color(str_to_color(param[3]), ft_strtof(param[2])));
	return (1);
}

int init_ambiant(char **param, t_world *w)
{
	w->ambiant = mul_sca_color(str_to_color(param[2]), ft_strtof(param[1]));
	return (1);
}

int init_cam(char **param, t_camera *c)
{
	float		half_view;
	float		aspect;
	t_tuple		pos;
	
	c->hsize = HEIGHT;
	c->vsize = WIDTH;
	c->fov = d_to_r(ft_strtof(param[3]));
	c->fov = PI/3;
	half_view = tan(c->fov / 2);
	aspect = c->hsize / c->vsize;
	if (aspect >= 1)
	{
		c->half_width = half_view;
		c->half_height = half_view / aspect;
	}
	else
	{
		c->half_width = half_view * aspect;
		c->half_height = half_view;	
	}
	c->pixel_size = (c->half_width * 2) / c->hsize;
	pos = str_to_point(param[1]);
	c->transform = view_transform(point(0,0,-5), point(0,0,0), vector(0,1,0));
	c->transform = mul_matrix(matrix_translation(pos.x, pos.y, pos.z), c->transform);
	return(1);
}
