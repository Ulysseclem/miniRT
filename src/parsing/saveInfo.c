#include "minirt.h"
#include "struct.h"

// t_camera	camera(int height, int width, float fov)
// {
// 	t_camera c;

// 	c.fov = fov;
// 	c.transform = identify_matrix(4, 4);
// 	half_view = tan(fov / 2);
// 	aspect = c.height / c.width;
// 	if (aspect >= 1)
// 	{
// 		c.half_width = half_view;
// 		c.half_height = half_view / aspect;
// 	}
// 	else
// 	{
// 		c.half_width = half_view * aspect;
// 		c.half_height = half_view;	
// 	}
// 	c.pixel_size = (c.half_width * 2) / c.height;
// 	return (c);
// }


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