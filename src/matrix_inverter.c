/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inverter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:36:16 by ulysseclem        #+#    #+#             */
/*   Updated: 2023/12/27 18:37:49 by ulysseclem       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_matrix *submatrix(t_matrix *m, int r, int c)
// {
// 	t_matrix	*new_m;
// 	float		*value;
// 	int			mul;
// 	int			i;
// 	int			j;
	
// 	new_m = create_matrix(m->r - 1, m->c - 1);
// 	value = malloc(sizeof(int) * ((m->r - 1) * (m->c - 1)));
// 	if (!value || !new_m)
// 		return (free(value), NULL);
// 	i = 0;
// 	j = -1;
// 	mul = 0;
// 	while (i < (m->r * m->c))
// 	{
// 		if (i == c + (m->c * mul)) // avoid la colonne
// 		{
// 			i++;
// 			mul++;
// 		}
// 		else if (i >= (r * m->c) && i < (r * m->c + m->c)) // avoid la ligne
// 			i++;
// 		else
// 		{
// 			value[++j] = m->data[i];
// 			i++;
// 		}
// 	}
// 	fill_matrix(new_m, value);
// 	free(value);
// 	return (new_m);
// }

// float determinant(t_matrix *m)
// {
// 	float	det = 0;
// 	int		i = 0;

// 	if (m->c * m->r == 4)
// 		return(m->data[0]*m->data[3] - m->data[1]*m->data[2]);
// 	else
// 	{
// 		while (i < m->c)
// 		{
// 			det = det + (m->data[0 + i] * cofactor(m, 0, i));
// 			i++;
// 		}
// 	}
// 	return (det);
// }

// float minor(t_matrix *m, int r, int c)
// {
// 	t_matrix	*sub;
// 	float		det;

// 	sub = submatrix(m, r, c);
// 	det = determinant(sub);
// 	free(sub->data);
// 	return (det);
// }

// float cofactor(t_matrix *m, int r, int c)
// {
// 	float nbr;
	
// 	nbr = minor(m, r, c);
// 	if ((r + c) % 2 == 0)
// 		return (nbr);
// 	else 
// 		return (nbr * -1);
// }

// t_matrix *inverse(t_matrix *m)
// {
// 	int			r;
// 	int			c;
// 	float		cof;
	
// 	r = 0;
// 	if (determinant(m) == 0) // Matrice non inversible
// 		return(NULL);
// 	while (r < m->r)
// 	{
// 		c = 0;
// 		while (c < m->c)
// 		{
// 			cof = cofactor(m, r, c);
// 			m->data[r + (c * m->c)] = cof / determinant(m); // R et C sont inverse pour accomplir la transposition
// 			c++;
// 		}
// 		r++;
// 	}
// 	return (m);
// }

t_matrix *inverse(t_matrix *m) {
    // Ensure the matrix is 4x4
    if (m->r != 4 || m->c != 4) {
        printf("Invalid matrix size. Must be 4x4.\n");
        return NULL;
    }

    // Create an augmented matrix [A | I] where A is the original matrix and I is the identity matrix
    t_matrix *augmentedMatrix = (t_matrix *)malloc(sizeof(t_matrix));
    augmentedMatrix->r = 4;
    augmentedMatrix->c = 8; // Twice the columns for the augmented matrix [A | I]
    augmentedMatrix->data = (float *)malloc(augmentedMatrix->r * augmentedMatrix->c * sizeof(float));

    // Initialize the augmented matrix with the original matrix and the identity matrix
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            augmentedMatrix->data[i * augmentedMatrix->c + j] = m->data[i * m->c + j];
            augmentedMatrix->data[i * augmentedMatrix->c + j + 4] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Gauss-Jordan elimination
    for (int i = 0; i < 4; i++) {
        // Pivoting
        if (augmentedMatrix->data[i * augmentedMatrix->c + i] == 0.0) {
            printf("Matrix is not invertible.\n");
            free(augmentedMatrix->data);
            free(augmentedMatrix);
            return NULL;
        }

        for (int j = 0; j < 4; j++) {
            if (i != j) {
                float ratio = augmentedMatrix->data[j * augmentedMatrix->c + i] / augmentedMatrix->data[i * augmentedMatrix->c + i];
                for (int k = 0; k < 2 * 4; k++) {
                    augmentedMatrix->data[j * augmentedMatrix->c + k] -= ratio * augmentedMatrix->data[i * augmentedMatrix->c + k];
                }
            }
        }
    }

    // Dividing each row by its diagonal element
    for (int i = 0; i < 4; i++) {
        float div = augmentedMatrix->data[i * augmentedMatrix->c + i];
        for (int j = 0; j < 2 * 4; j++) {
            augmentedMatrix->data[i * augmentedMatrix->c + j] /= div;
        }
    }

    // Extracting the inverted matrix from the augmented matrix
    t_matrix *invertedMatrix = (t_matrix *)malloc(sizeof(t_matrix));
    invertedMatrix->r = 4;
    invertedMatrix->c = 4;
    invertedMatrix->data = (float *)malloc(4 * 4 * sizeof(float));

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            invertedMatrix->data[i * 4 + j] = augmentedMatrix->data[i * augmentedMatrix->c + j + 4];
        }
    }

    // Free the memory allocated for the augmented matrix
    free(augmentedMatrix->data);
    free(augmentedMatrix);
    return invertedMatrix;
}