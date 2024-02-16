/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saveShape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaharel <icaharel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:53:47 by uclement          #+#    #+#             */
/*   Updated: 2024/02/16 11:42:29 by icaharel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

int	init_sp(char **param, t_shape *shape, t_world *world)
{
	t_sphere	*sphere;

	sphere = malloc (sizeof(t_sphere));
	if (!sphere)
		return (0);
	shape->point = str_to_point(param[1]);
	sphere->diameter = ft_strtof(param[2]);
	shape->material = str_to_material(param[3], world);
	shape->transform = matrix_translation(shape->point.x, \
	shape->point.y, shape->point.z);
	shape->ptr_type = sphere;
	shape->type = SPHERE;
	return (1);
}

int	init_pl(char **param, t_shape *shape, t_world *world)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (0);
	shape->point = str_to_point(param[1]);
	shape->pl_dir = str_to_vector(param[2]);
	shape->material = str_to_material(param[3], world);
	shape->transform = identify_matrix(4, 4);
	shape->ptr_type = plane;
	shape->type = PLANE;
	return (1);
}

void direction_to_degrees(float x_dir, float y_dir, float z_dir, float *x_deg, float *y_deg, float *z_deg) {
    // Calculate azimuth angle (rotation around z-axis)
    *z_deg = atan2(y_dir, x_dir) * 180.0 / PI;

    // Calculate elevation angle (angle above xy-plane)
    float xy_projection = sqrt(x_dir * x_dir + y_dir * y_dir);
    *x_deg = atan2(z_dir, xy_projection) * 180.0 / PI;

    // Calculate roll angle (rotation around x-axis)
    *y_deg = atan2(-x_dir * z_dir, xy_projection) * 180.0 / PI;
}


t_matrix *identity_matrix(int rows, int cols) {
    // Allouer de la mémoire pour la structure de la matrice
    t_matrix *m = malloc(sizeof(t_matrix));
    if (!m)
        return NULL;

    // Initialiser les dimensions de la matrice
    m->r = rows;
    m->c = cols;

    // Allouer de la mémoire pour les données de la matrice
    m->data = malloc(rows * sizeof(float *));
    if (!m->data) {
        free(m); // Libérer la mémoire allouée pour la structure si l'allocation échoue
        return NULL;
    }

    // Initialiser les éléments de la matrice à 0, sauf les éléments diagonaux à 1
    for (int i = 0; i < rows; i++) {
        m->data[i] = calloc(cols, sizeof(float));
        if (!m->data[i]) {
            // Si une allocation échoue, libérer la mémoire allouée précédemment
            for (int j = 0; j < i; j++) {
                free(m->data[j]);
            }
            free(m->data);
            free(m);
            return NULL;
        }
        m->data[i][i] = 1.0; // Éléments diagonaux égaux à 1
    }

    return m;
}

t_matrix *matrix_rotation_x2(float angle) {
    t_matrix *m = identity_matrix(4, 4);
    float rad = angle * M_PI / 180; // Conversion en radians
    m->data[1][1] = cos(rad);
    m->data[1][2] = -sin(rad);
    m->data[2][1] = sin(rad);
    m->data[2][2] = cos(rad);
    return m;
}

// Fonction de rotation autour de l'axe y
t_matrix *matrix_rotation_y2(float angle) {
    t_matrix *m = identity_matrix(4, 4);
    float rad = angle * M_PI / 180; // Conversion en radians
    m->data[0][0] = cos(rad);
    m->data[0][2] = sin(rad);
    m->data[2][0] = -sin(rad);
    m->data[2][2] = cos(rad);
    return m;
}

// Fonction de rotation autour de l'axe z
t_matrix *matrix_rotation_z2(float angle) {
    t_matrix *m = identity_matrix(4, 4);
    float rad = angle * M_PI / 180 ; // Conversion en radians
    m->data[0][0] = cos(rad);
    m->data[0][1] = -sin(rad);
    m->data[1][0] = sin(rad);
    m->data[1][1] = cos(rad);
    return m;
}

t_matrix *matrix_multiply(const t_matrix *a, const t_matrix *b) {
    // Vérifier que les dimensions des matrices sont compatibles pour la multiplication
    if (a->c != b->r) {
        return NULL; // Impossible de multiplier les matrices
    }

    // Créer et initialiser la matrice résultat
    t_matrix *result = malloc(sizeof(t_matrix));
    if (!result)
        return NULL;

    result->r = a->r;
    result->c = b->c;

    // Allouer de la mémoire pour les données de la matrice résultat
    result->data = malloc(result->r * sizeof(float *));
    if (!result->data) {
        free(result);
        return NULL;
    }

    for (int i = 0; i < result->r; i++) {
        result->data[i] = malloc(result->c * sizeof(float));
        if (!result->data[i]) {
            // Si une allocation échoue, libérer la mémoire allouée précédemment
            for (int j = 0; j < i; j++) {
                free(result->data[j]);
            }
            free(result->data);
            free(result);
            return NULL;
        }
        
        // Initialiser les valeurs de la matrice résultat à 0
        for (int j = 0; j < result->c; j++) {
            result->data[i][j] = 0;
        }
    }

    // Calculer les valeurs de la matrice résultat
    for (int i = 0; i < result->r; i++) {
        for (int j = 0; j < result->c; j++) {
            for (int k = 0; k < a->c; k++) {
                result->data[i][j] += a->data[i][k] * b->data[k][j];
            }
        }
    }

    return result;
}

t_matrix *rotation_matrix(t_tuple axis, float angle) {
    // Normaliser l'axe de rotation
    t_tuple axis_normalized = norm(axis);

    // Extraire les composantes de l'axe de rotation normalisé
    float x = axis_normalized.x;
    float y = axis_normalized.y;
    float z = axis_normalized.z;

    // Calculer les termes de la matrice de rotation
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);
    float one_minus_cos = 1 - cos_angle;

    float m00 = cos_angle + x * x * one_minus_cos;
    float m01 = x * y * one_minus_cos - z * sin_angle;
    float m02 = x * z * one_minus_cos + y * sin_angle;
    float m10 = y * x * one_minus_cos + z * sin_angle;
    float m11 = cos_angle + y * y * one_minus_cos;
    float m12 = y * z * one_minus_cos - x * sin_angle;
    float m20 = z * x * one_minus_cos - y * sin_angle;
    float m21 = z * y * one_minus_cos + x * sin_angle;
    float m22 = cos_angle + z * z * one_minus_cos;

    // Créer et initialiser la matrice de rotation
    t_matrix *rotation = malloc(sizeof(t_matrix));
    if (!rotation)
        return NULL;
    rotation->r = 4;
    rotation->c = 4;

    // Allouer de la mémoire pour les données de la matrice
    rotation->data = malloc(4 * sizeof(float *));
    if (!rotation->data) {
        free(rotation);
        return NULL;
    }

    for (int i = 0; i < 4; i++) {
        rotation->data[i] = malloc(4 * sizeof(float));
        if (!rotation->data[i]) {
            // Si une allocation échoue, libérer la mémoire allouée précédemment
            for (int j = 0; j < i; j++) {
                free(rotation->data[j]);
            }
            free(rotation->data);
            free(rotation);
            return NULL;
        }
    }

    // Remplir la matrice avec les termes calculés
    rotation->data[0][0] = m00; rotation->data[0][1] = m01; rotation->data[0][2] = m02; rotation->data[0][3] = 0;
    rotation->data[1][0] = m10; rotation->data[1][1] = m11; rotation->data[1][2] = m12; rotation->data[1][3] = 0;
    rotation->data[2][0] = m20; rotation->data[2][1] = m21; rotation->data[2][2] = m22; rotation->data[2][3] = 0;
    rotation->data[3][0] = 0;   rotation->data[3][1] = 0;   rotation->data[3][2] = 0;   rotation->data[3][3] = 1;

    return rotation;
}

float angle_between_vectors(t_tuple v, t_tuple o) {
    // Calculer le produit scalaire entre les deux vecteurs
    float dot_product = v.x * o.x + v.y * o.y + v.z * o.z;

    // Calculer les normes des vecteurs
    float norm_v = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    float norm_o = sqrt(o.x * o.x + o.y * o.y + o.z * o.z);

    // Vérifier si l'une des normes est nulle pour éviter une division par zéro
    if (norm_v == 0.0f || norm_o == 0.0f) {
        return 0.0f; // Ou gérer ce cas de manière appropriée
    }

    // Calculer le cosinus de l'angle entre les vecteurs
    float cos_theta = dot_product / (norm_v * norm_o);

    // Assurer que le cosinus est dans la plage [-1, 1] pour éviter les erreurs d'arrondi
    cos_theta = fmaxf(-1.0f, fminf(1.0f, cos_theta));

    // Calculer l'angle en radians en utilisant la fonction acos
    float angle_radians = acos(cos_theta);

    // Convertir l'angle en degrés
    float angle_degrees = angle_radians * (180.0f / M_PI);

    return angle_degrees;
}

int	init_cy(char **param, t_shape *shape, t_world *world)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(cylinder));
	if (!cylinder)
		return (0);
	shape->point = str_to_point(param[1]);
	printf("%s\n", param[2]);
	shape->pl_dir = str_to_vector(param[2]);
	cylinder->diameter = ft_strtof(param[3]);
	cylinder->height = ft_strtof(param[4]);
	shape->material = str_to_material(param[5], world);
	
	t_matrix *transform = identify_matrix(4,4);
  	shape->transform  = transform;
	
	
	shape->ptr_type = cylinder;
	shape->type = CYLINDER;
	return (1);
}	
