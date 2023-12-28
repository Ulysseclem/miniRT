/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inverter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:36:16 by ulysseclem        #+#    #+#             */
/*   Updated: 2023/12/28 17:09:08 by ulysseclem       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix* inverse(t_matrix *m)
{
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

	// Gaussian elimination to transform 
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







// float determinant3x3(float **mat) 
// {
//     return mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]) -
//            mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]) +
//            mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);
// }

// void cofactor(t_matrix *m, t_matrix *adjoint) {
//     t_matrix *tempMat;
//     int row = 0, col, ii, jj;

// 	tempMat = create_matrix(3, 3);
//     while (row < m->r) {
//         col = 0;
//         while (col < m->c) {
//             ii = 0;
//             int i = 0;
//             while (i < m->r) {
//                 if (i == row) {
//                     i++;
//                     continue;
//                 }
//                 jj = 0;
//                 int j = 0;
//                 while (j < m->c) {
//                     if (j == col) {
//                         j++;
//                         continue;
//                     }
//                     tempMat->data[ii][jj] = m->data[i][j];
//                     jj++;
//                     j++;
//                 }
//                 ii++;
//                 i++;
//             }
//             adjoint->data[row][col] = determinant3x3(tempMat->data);
//             if ((row + col) % 2 != 0) {
//                 adjoint->data[row][col] = -adjoint->data[row][col];
//             }
//             col++;
//         }
//         row++;
//     }
// 	free_matrix(tempMat);
// }

// t_matrix* inverse(t_matrix *m) 
// {
//     float		det;
// 	t_matrix	*adjoint;
// 	t_matrix	*result;
// 	int			i;
// 	int			j;

// 	det = determinant3x3(m->data);
//     if (det == 0) {
//         printf("Matrix is singular, inverse does not exist.\n");
//         return NULL;
//     }
// 	adjoint = create_matrix(m->r, m->c);
//     cofactor(m, adjoint);
// 	result = create_matrix(m->r, m->c);
// 	i = 0;
//     while (i < m->r) 
// 	{
// 		j = 0;
//         while (j < m->c)
// 		{
//             result->data[i][j] = adjoint->data[j][i] / det;
// 			j++;
//         }
// 		i++;
//     }
//     free_matrix(adjoint);
//     return result;
// }