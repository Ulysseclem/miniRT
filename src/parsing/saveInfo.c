#include "minirt.h"
#include "struct.h"

// t_camera	camera(int height, int width, float fov)
// {
// 	t_camera c;
// 	float		half_view;
// 	float		aspect;
	
// 	c.height = height;
// 	c.width = width;
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
