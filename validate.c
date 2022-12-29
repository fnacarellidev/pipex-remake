/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:25:36 by fnacarel          #+#    #+#             */
/*   Updated: 2022/12/29 11:05:45 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./includes/pipex.h"
#include "libft/libft.h"

static void	check_if_infile_is_valid(char **argv, char **envp);

void	validate_files(int argc, char **argv, char **envp)
{
	size_t	len_arg1;
	size_t	len_arg2;

	if (argc != 5)
		exit(0);
	len_arg1 = ft_strlen(argv[2]);
	len_arg2 = ft_strlen(argv[argc - 2]);
	if (len_arg1 == 0 && len_arg2 == 0)
	{
		ft_printf("Program should be used like this: "
			"./pipex [FILE_TO_READ] [cmd1] [cmd2] [FILE_TO_WRITE].\n");
		exit(1);
	}
	check_if_infile_is_valid(argv, envp);
}

static void	check_if_infile_is_valid(char **argv, char **envp)
{
	char	*err;
	char	*suffix;

	if (access(argv[1], F_OK) == -1)
	{
		suffix = ft_strjoin(" no such file or directory: ", argv[1]);
		err = set_err_msg(envp, suffix);
		ft_printf("%s\n", err);
		free(err);
		free(suffix);
	}
	else if (access(argv[1], R_OK) == -1)
	{
		suffix = ft_strjoin(" permission denied: ", argv[1]);
		err = set_err_msg(envp, suffix);
		ft_printf("%s\n", err);
		free(err);
		free(suffix);
	}
}
