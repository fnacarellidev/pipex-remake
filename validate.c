/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:25:36 by fnacarel          #+#    #+#             */
/*   Updated: 2022/12/26 11:59:13 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./includes/pipex.h"
#include "libft/libft.h"

int	validate_files(int argc, char **argv)
{
	size_t len_arg1;
	size_t len_arg2;

	len_arg1 = ft_strlen(argv[1]);
	len_arg2 = ft_strlen(argv[argc - 1]);
	if (argc != 5 || (len_arg1 == 0 && len_arg2 == 0))
	{
		ft_printf("Program should be used like this: "
			"./pipex [FILE_TO_READ] [cmd1] [cmd2] [FILE_TO_WRITE].\n");
		exit(1);
	}
	else if (access(argv[1], F_OK | R_OK) == -1)
	{
		perror("infile");
		exit(1);
	}
	else if (access(argv[argc - 1], F_OK | W_OK) == -1)
	{
		perror("outfile");
		exit(2);
	}
	return (0);
}
