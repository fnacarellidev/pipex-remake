/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:25:36 by fnacarel          #+#    #+#             */
/*   Updated: 2022/12/12 14:15:08 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./includes/pipex.h"

int	validate_files(int argc, char **argv)
{
	if (argc < 5)
	{
		ft_printf("Missing arguments, program should be used like this: "
			"./pipex [FILE_TO_READ] [cmd1] [cmd2] [FILE_TO_WRITE].\n");
		exit(1);
	}
	else if (access(argv[1], F_OK | R_OK) == -1)
	{
		perror("infile: ");
		exit(1);
	}
	else if (access(argv[argc - 1], F_OK | W_OK) == -1)
	{
		perror("outfile: ");
		exit(1);
	}
	return (0);
}
