/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:25:36 by fnacarel          #+#    #+#             */
/*   Updated: 2022/12/28 18:12:52 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./includes/pipex.h"
#include "libft/libft.h"

int	validate_files(int argc, char **argv, char **envp)
{
	char 	*err;
	char	*suffix;
	size_t	len_arg1;
	size_t	len_arg2;

	if (argc != 5)
		exit(0);
	len_arg1 = ft_strlen(argv[1]);
	len_arg2 = ft_strlen(argv[argc - 1]);
	if (len_arg1 == 0 && len_arg2 == 0)
	{
		ft_printf("Program should be used like this: "
			"./pipex [FILE_TO_READ] [cmd1] [cmd2] [FILE_TO_WRITE].\n");
		exit(1);
	}
	else if (access(argv[1], F_OK) == -1)
	{
		suffix = ft_strjoin(" no such file or directory: ", argv[1]);
		err = set_err_msg(envp, suffix);
		ft_printf("%s\n", err);
		free(err);
		free(suffix);
		/* exit(0); */
	}
	else if (access(argv[1], R_OK) == -1)
	{
		suffix = ft_strjoin(" permission denied: ", argv[1]);
		err = set_err_msg(envp, suffix);
		ft_printf("%s\n", err);
		free(err);
		free(suffix);
		/* exit(0); */
	}
	return (0);
}
