#include "minirt.h"
#include "struct.h"

int init_sp(char **param, t_shape *shape)
{
    t_sphere *sphere;
    
    sphere = malloc (sizeof(t_sphere));
    if (!sphere)
        return (0);
    shape->point = str_to_point(param[1]);
    sphere->diameter = ft_strtof(param[2]);
    shape->material = str_to_material(param[3]);
	shape->transform = mul_matrix(matrix_translation(shape->point.x, shape->point.y, shape->point.z),matrix_scaling(sphere->diameter,sphere->diameter,sphere->diameter));
	shape->transform = mul_matrix(shape->transform, matrix_rotation_z(45));
	shape->material.is_pat = TRUE;
	shape->material.pat.a = set_color(1,1,1);
	shape->material.pat.b = set_color(0.5,0,0);
    shape->ptrType = sphere;
    shape->type = SPHERE;
	return(1);
}


int init_pl(char **param, t_shape *shape)
{
    t_plane *plane;

    plane = malloc(sizeof(t_plane));
    if (!plane)
        return (0);
    shape->point = str_to_point(param[1]);
	shape->pl_dir = str_to_vector(param[2]);
    shape->material = str_to_material(param[3]);
	shape->transform = identify_matrix(4,4);
	shape->material.is_pat = TRUE;
	shape->material.pat.a = set_color(1,1,1);
	shape->material.pat.b = set_color(0,0,0);
    shape->ptrType = plane;
    shape->type = PLANE;
    return (1);
}

int init_cy(char **param, t_shape *shape)
{
    t_cylinder *cylinder;

    cylinder = malloc(sizeof(cylinder));
    if (!cylinder)
        return (0);
    shape->point = str_to_point(param[1]);
    cylinder->directions = str_to_vector(param[2]);
    cylinder->diameter = ft_strtof(param[3]);
    cylinder->height = ft_strtof(param[4]);

    shape->material = str_to_material(param[5]);
    shape->transform = identify_matrix(4, 4);
    shape->ptrType = cylinder;
    shape->type = CYLINDER;
    return (1);
}