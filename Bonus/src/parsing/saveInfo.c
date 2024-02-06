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


// int init_cam(char **param, t_camera *c)
// {
// 	float		half_view;
// 	float		aspect;
// 	t_tuple		pos;
// 	t_tuple		orientation;
	
// 	c->hsize = HEIGHT;
// 	c->vsize = WIDTH;
// 	c->fov = d_to_r(ft_strtof(param[3]));
// 	half_view = tan(c->fov / 2);
// 	aspect = c->hsize / c->vsize;
// 	if (aspect >= 1)
// 	{
// 		c->half_width = half_view;
// 		c->half_height = half_view / aspect;
// 	}
// 	else
// 	{
// 		c->half_width = half_view * aspect;
// 		c->half_height = half_view;	
// 	}
// 	c->pixel_size = (c->half_width * 2) / c->hsize;
// 	pos = str_to_point(param[1]);
// 	c->transform = view_transform(point(0,0,-5), point(0,0,0), vector(0,1,0));
// 	c->transform = mul_matrix(matrix_translation(pos.x, -pos.y, pos.z), c->transform);
// 	orientation = str_to_point(param[2]);
// 	c->transform = mul_matrix(matrix_rotation_x(orientation.x*100), c->transform);
// 	c->transform = mul_matrix(matrix_rotation_y(orientation.y*100), c->transform);
// 	c->transform = mul_matrix(matrix_rotation_z(orientation.z*100), c->transform);
// 	(void) orientation;

// 	return(1);
// }

int init_cam(char **param, t_camera *c)
{
	float		half_view;
	float		aspect;
	t_tuple		pos;
	t_tuple		orientation;
	
	c->hsize = HEIGHT;
	c->vsize = WIDTH;
	c->fov = d_to_r(ft_strtof(param[3]));
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
	orientation = str_to_point(param[2]);
	orientation.x += pos.x;
	orientation.y += pos.y; 
	orientation.z += pos.z; 
	c->transform = view_transform(pos, orientation, vector(0,1,0));


	return(1);
}