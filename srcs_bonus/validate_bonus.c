/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:58:24 by fnacarel          #+#    #+#             */
/*   Updated: 2022/12/30 18:39:31 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/pipex_bonus.h"

static void	check_if_infile_is_valid(char **argv, char **envp);
static void	check_if_has_valid_command(int argc, char **argv);

void	validate_input(int argc, char **argv, char **envp)
{
	if (argc < 5)
		exit(0);
	check_if_has_valid_command(argc, argv);
	check_if_infile_is_valid(argv, envp);
}

static void	check_if_infile_is_valid(char **argv, char **envp)
{
	char	*err;
	char	*suffix;

	if (ft_strcmp(argv[1], "here_doc") != 0)
	{
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
}

static void	check_if_has_valid_command(int argc, char **argv)
{
	int	i;
	int	j;
	int	number_of_commands;

	j = 0;
	i = 2;
	number_of_commands = argc - 3;
	while (i < argc - 1)
	{
		if (ft_strlen(argv[i]) == 0)
			j++;
		i++;
	}
	if (j == number_of_commands)
	{
		ft_printf("Program should have at least one command.\n");
		exit(1);
	}
}
