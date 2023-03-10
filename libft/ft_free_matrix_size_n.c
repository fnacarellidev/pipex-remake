/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix_size_n.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:21:29 by fnacarel          #+#    #+#             */
/*   Updated: 2022/12/21 16:21:56 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_free_matrix_size_n(void **matrix, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
