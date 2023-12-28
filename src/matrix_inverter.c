/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inverter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:36:16 by ulysseclem        #+#    #+#             */
/*   Updated: 2023/12/28 13:11:09 by ulysseclem       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void perform_row_operations(t_matrix *m, int pivot_row, int pivot_col) {
//     int i = 0;
//     while (i < m->r) {
//         if (i != pivot_row) {
//             float factor = m->data[i][pivot_col] / m->data[pivot_row][pivot_col];
//             int j = 0;
//             while (j < m->c) {
//                 m->data[i][j] -= m->data[pivot_row][j] * factor;
//                 j++;
//             }
//         }
//         i++;
//     }
// }

// // Function to calculate the inverse matrix using Gauss-Jordan method
// t_matrix* inverse(t_matrix *m) 
// {
//     if (m->r != 4 || m->c != 4) {
//         printf("Invalid matrix dimensions. Expected 4x4 matrix.\n");
//         return NULL;
//     }

//     t_matrix *inverse = create_matrix(4, 4);

//     // Initialize the inverse matrix as an identity matrix
//     int i = 0;
//     while (i < 4) {
//         int j = 0;
//         while (j < 4) {
//             inverse->data[i][j] = (i == j) ? 1.0f : 0.0f;
//             j++;
//         }
//         i++;
//     }

//     i = 0;
//     while (i < 4) {
//         if (m->data[i][i] == 0.0f) {
//             printf("The matrix is singular, inverse does not exist.\n");
//             free_matrix(inverse);
//             return NULL;
//         }

//         // Normalize the pivot row
//         float pivot = m->data[i][i];
//         int j = 0;
//         while (j < 4) {
//             m->data[i][j] /= pivot;
//             inverse->data[i][j] /= pivot;
//             j++;
//         }

//         // Perform row operations to get zeros above and below the pivot
//         perform_row_operations(m, i, i);
//         perform_row_operations(inverse, i, i);

//         i++;
//     }

//     return inverse;
// }

t_matrix* inverse(t_matrix *m) {
	t_matrix* copy;
	t_matrix* identity;
	int			i;
	int			j;
	int 		k;
	float 		scalar;
	float		factor;

	copy = create_matrix(4, 4);
	fill_matrix(copy, m->data);
	identity = identify_matrix(4, 4);

	// Gaussian elimination to transform 'copy' into an upper triangular matrix
	i = 0;
	while (i < 4) 
	{
		scalar = 1.0 / copy->data[i][i];
		j = 0;
		while (j < 4) 
		{
			copy->data[i][j] *= scalar;
			identity->data[i][j] *= scalar;
			j++;
		}
		k = 0;
		while (k < 4)
		{
			if (k != i) {
				factor = copy->data[k][i];
				j = 0;
				while (j < 4) 
				{
					copy->data[k][j] -= factor * copy->data[i][j];
					identity->data[k][j] -= factor * identity->data[i][j];
					j++;
				}
			}
			k++;
		}
		i++;
	}
	free_matrix(copy);
	return identity;
}
