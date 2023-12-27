/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:43:53 by uclement          #+#    #+#             */
/*   Updated: 2023/12/21 14:39:36 by ulysseclem       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


t_matrix *create_matrix(int r, int c)
{
	t_matrix	*matrix;

	matrix = malloc(sizeof(t_matrix));
	if (!matrix)
		return(NULL);
	matrix->r = r;
	matrix->c = c;
	matrix->data = malloc(sizeof(float) * (r * c));
	if (!matrix->data)
		return(NULL);
	return(matrix);
}

void fill_matrix(t_matrix *m, float *value)
{
	int	size;
	int	i;

	size = m->r * m->c;
	i = 0;
	while (i < size)
	{
		m->data[i] = value[i];
		i++;
	}
}

/* ************************************************************************** */
/*cree une matrice de '1', utile pour la transformation					      */
/* ************************************************************************** */

t_matrix *identify_matrix(int r, int c)
{
	int 		i;
	int			j;
	t_matrix	*matrix;

	matrix = create_matrix(r, c);
	i = 0;
	j = 0;
	while(i < (r * c))
	{
		if (i % 5 == 0)
		{
			matrix->data[i] = 1;
			j++;
		}
		else
			matrix->data[i] = 0;
		i++;
	}
	return(matrix);
}

int	equal_matrix(t_matrix *a, t_matrix *b)
{
	int i;

	if (a->c != b->c || a->r != b->r)
		return (0);
	i = 0;
	while (i < (a->r * a->c))
	{
		if (!equal(a->data[i], b->data[i]))
			return(0);
		i++;
	}
	return(1);
}

/* ************************************************************************** */
/*Permet d'obtenir la valeur d'une case dans une matrice				      */
/* ************************************************************************** */
float	gmv(t_matrix *m, int r, int c)
{
	return (m->data[c + r * m->r]);
}

/* ************************************************************************** */
/*Multiplie 2 matrices													      */
/* ************************************************************************** */
t_matrix *mul_matrix(t_matrix *a, t_matrix *b)
{
	t_matrix	*m;
	int			r;
	int			c;
	
	m = create_matrix(4, 4);
	r = 0;
	while (r < a->r)
	{
		c = 0;
		while (c < b->c)
		{
			m->data[c + r * m->r] = gmv(a, r, 0) * gmv(b, 0, c) + gmv(a, r, 1) 
			* gmv(b, 1, c) + gmv(a, r, 2) * gmv(b, 2, c) + gmv(a, r, 3) * gmv(b, 3, c);
			c++;
		}
		r++;
	}
	return (m);
}

/* ************************************************************************** */
/*Multiplie une matrice et un truple, renvoi un tuple					      */
/* ************************************************************************** */
t_tuple	mul_matrix_tuple(t_matrix *a, t_tuple b)
{
	t_tuple		t;	
		t.x = gmv(a, 0, 0) * b.x + gmv(a, 0, 1) * b.y + gmv(a, 0, 2) * b.z + gmv(a, 0, 3) * b.w;
		t.y = gmv(a, 1, 0) * b.x + gmv(a, 1, 1) * b.y + gmv(a, 1, 2) * b.z + gmv(a, 1, 3) * b.w;
		t.z = gmv(a, 2, 0) * b.x + gmv(a, 2, 1) * b.y + gmv(a, 2, 2) * b.z + gmv(a, 2, 3) * b.w;
		t.w = gmv(a, 3, 0) * b.x + gmv(a, 3, 1) * b.y + gmv(a, 3, 2) * b.z + gmv(a, 3, 3) * b.w;
	return (t);
}


/* ************************************************************************** */
/*transpose la ligne et la colonne d'une matrice							  */
/* ************************************************************************** */
t_matrix	*transp_matrix(t_matrix *m)
{
	t_matrix	*tmp;
	int			i;
	int			j;

	tmp = create_matrix(m->r, m->c);
	if (!tmp)
		return(NULL);
	i = 0;
	while (i < m->r)
	{
		j = 0;
		while (j < m->c)
		{
			tmp->data[j + i * m->r] = m->data[i + j * m-> r];
			j++;
		}
		i++;
	}
	return (tmp);
}

void	free_matrix(t_matrix *m)
{
	free(m->data);
	free(m);
}


// PRINT
void print_matrix(t_matrix *matrix) 
{
	int i;
	int j;

	i = 0;
	while (i < matrix->r)
	{
		j = 0;
		while (j < matrix->c)
		{
			printf("%f ", matrix->data[i * matrix->c + j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

