/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:43:53 by uclement          #+#    #+#             */
/*   Updated: 2024/01/04 13:10:59 by ulysseclem       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix *create_matrix(int r, int c) // ok
{
	t_matrix	*matrix;
	int 		i;

	matrix = malloc(sizeof(t_matrix));
	if (!matrix)
		return(NULL);
	matrix->r = r;
	matrix->c = c;
	matrix->data = malloc(sizeof(float *) * r);
	if (!matrix->data)
		return(NULL);
	i = 0;
	while (i < c)
	{
		matrix->data[i] = malloc(sizeof(float) * c);
			if (!matrix->data[i])
		return(NULL);
		i++;
	}
	return(matrix);
}

void fill_matrix(t_matrix *m, float **value) //ok
{
	int	i;
	int j;

	i = 0;
	while (i < m->r)
	{
		j = 0;
		while (j < m->c)
		{
			m->data[i][j] = value[i][j];
			j++;
		}
		i++;
	}
}

/* ************************************************************************** */
/*cree une matrice de '1', utile pour la transformation					      */
/* ************************************************************************** */

t_matrix *identify_matrix(int r, int c) // ok
{
	int 		i;
	int			j;
	t_matrix	*matrix;

	matrix = create_matrix(r, c);
	i = 0;
	while (i < r)
	{
		j = 0;
		while (j < c)
		{
			if (i == j)
				matrix->data[i][j] = 1;
			else
				matrix->data[i][j] = 0;
			j++;
		}
		i++;
	}
	return(matrix);
}

int	equal_matrix(t_matrix *a, t_matrix *b) // ok I guess
{
	int i;
	int j;


	if (a->c != b->c || a->r != b->r)
		return (0);
	i = 0;
	while (i < a->r)
	{
		j = 0;
		while (j < a->c)
		{
			if (!equal(a->data[i][j], b->data[i][j]))
				return(0);
			j++;
		}
		i++;
	}
	return(1);
}

/* ************************************************************************** */
/*Multiplie 2 matrices													      */
/* ************************************************************************** */

t_matrix* mul_matrix(t_matrix *a, t_matrix *b) 
{
	t_matrix	*result = create_matrix(a->r, b->c);
	int 		i;
	int 		k;
	float 		sum;

	i = 0;
	while (i < a->r) 
	{
		int j = 0;
		while (j < b->c) 
		{
			k = 0;
			sum = 0;
			while (k < a->c) 
			{
				sum += a->data[i][k] * b->data[k][j];
				k++;
			}
			result->data[i][j] = sum;
			j++;
		}
		i++;
	}
	// free_matrix(a); //maybe
	// free_matrix(b); //maybe
	return (result);
}

/* ************************************************************************** */
/*Multiplie une matrice et un truple, renvoi un tuple					      */
/* ************************************************************************** */

t_tuple	mul_matrix_tuple(t_matrix *a, t_tuple b)
{
	t_tuple		result;	

	result.x = a->data[0][0] * b.x + a->data[0][1] * b.y + a->data[0][2] * b.z + a->data[0][3] * b.w;
    result.y = a->data[1][0] * b.x + a->data[1][1] * b.y + a->data[1][2] * b.z + a->data[1][3] * b.w;
    result.z = a->data[2][0] * b.x + a->data[2][1] * b.y + a->data[2][2] * b.z + a->data[2][3] * b.w;
    result.w = a->data[3][0] * b.x + a->data[3][1] * b.y + a->data[3][2] * b.z + a->data[3][3] * b.w;
	return (result);
}

/* ************************************************************************** */
/*transpose la ligne et la colonne d'une matrice							  */
/* ************************************************************************** */
t_matrix	*transp_matrix(t_matrix *m)
{
	t_matrix	*transpose;
	int			i;
	int			j;

	transpose = create_matrix(m->r, m->c);
	if (!transpose)
		return(NULL);
	i = 0;
	while (i < m->r)
	{
		j = 0;
		while (j < m->c)
		{
			transpose->data[i][j] = m->data[j][i];
			j++;
		}
		i++;
	}
	// free_matrix(m); //maybe
	return (transpose);
}

void free_matrix(t_matrix *mat) 
{
    for (int i = 0; i < mat->r; i++) {
        free(mat->data[i]);
    }
    free(mat->data);
    free(mat);
}

// PRINT
// void print_matrix(t_matrix *matrix) 
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while (i < matrix->r)
// 	{
// 		j = 0;
// 		while (j < matrix->c)
// 		{
// 			printf("%f ", matrix->data[i * matrix->c + j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }

