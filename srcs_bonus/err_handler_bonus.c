/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handler_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:52:40 by fnacarel          #+#    #+#             */
/*   Updated: 2022/12/29 16:52:44 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/pipex_bonus.h"

static char	*get_shell_env(char **envp);

char	*set_err_msg(char **envp, char *suffix)
{
	char	*err_msg;
	int		matr_size;
	char	*shell_env;
	char	*current_shell;
	char	**splitted_shell_env;

	shell_env = get_shell_env(envp);
	splitted_shell_env = ft_split(shell_env, '/');
	matr_size = ft_count_matrix((void **)splitted_shell_env);
	current_shell = ft_strjoin(splitted_shell_env[matr_size - 1], ":");
	err_msg = ft_strjoin(current_shell, suffix);
	ft_free_matrix((void **)splitted_shell_env);
	free(shell_env);
	free(current_shell);
	return (err_msg);
}

static char	*get_shell_env(char **envp)
{
	int		i;
	char	*shell_line;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "SHELL=", 6) == 0)
		{
			shell_line = ft_strdup(envp[i]);
			return (shell_line);
		}
		i++;
	}
	return (NULL);
}
