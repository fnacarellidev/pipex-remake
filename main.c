/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:32:54 by fnacarel          #+#    #+#             */
/*   Updated: 2022/12/21 14:11:41 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./includes/pipex.h"

int main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int	i = 0;
	int	j = 0;

	init_pipex(&pipex, argc, argv, envp);
	while (i < 2)
	{
		j = 0;
		while (pipex.commands[i][j])
		{
			ft_printf("%s\n", pipex.commands[i][j]);
			j++;
		}
		i++;
	}
	i = 0;
	while (pipex.program_path[i])
	{
		ft_putstr(pipex.program_path[i]);
		write(1, "\n", 1);
		i++;
	}
	/* ft_putstr(pipex.program_path[i]); */
	/* write(1, "\n", 1); */
	ft_free_matrix((void **)pipex.program_path);
	ft_free_spatial_matrix((void ***)pipex.commands);
}
