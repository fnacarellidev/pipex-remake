/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:59:42 by fnacarel          #+#    #+#             */
/*   Updated: 2022/12/26 15:43:52 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./includes/pipex.h"
#include "libft/libft.h"

static char	*get_path_env(char **envp);
static void	set_cmds(t_pipex *pipex, char **argv);
static void	set_program_path(t_pipex *pipex, char **envp);
static void	where_is(char **splitted_path, t_pipex *pipex);

void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->n_cmds = argc - 3;
	pipex->infile_fd = open(argv[1], O_RDONLY);
	pipex->outfile_fd = open(argv[argc - 1], O_WRONLY | O_TRUNC);
	if (pipex->infile_fd == -1 || pipex->outfile_fd == -1)
	{
		ft_printf("Failed to open one of the files, please try again.\n");
		exit(1);
	}
	pipex->commands = ft_calloc(sizeof(char **), pipex->n_cmds + 1);
	pipex->program_path = ft_calloc(sizeof(char *), pipex->n_cmds + 1);
	set_cmds(pipex, argv);
	set_program_path(pipex, envp);
}

static void	set_program_path(t_pipex *pipex, char **envp)
{
	char	*path_env_var;
	char	**splitted_path_env;

	path_env_var = get_path_env(envp);
	splitted_path_env = ft_split(path_env_var, ':');
	free(path_env_var);
	format_splitted_path_env(splitted_path_env);
	where_is(splitted_path_env, pipex);
	ft_free_matrix((void **)splitted_path_env);
}

static void	where_is(char **splitted_path, t_pipex *pipex)
{
	int		i;
	int		j;
	char	*cmd_to_eval;

	i = 0;
	while (i < pipex->n_cmds)
	{
		j = 0;
		if (pipex->commands[i][0])
		{
			while (splitted_path[j] != NULL)
			{
				cmd_to_eval = ft_strjoin(splitted_path[j], pipex->commands[i][0]);
				if (access(cmd_to_eval, F_OK | X_OK) == 0)
				{
					pipex->program_path[i] = ft_strdup(cmd_to_eval);
					free(cmd_to_eval);
					break ;
				}
				free(cmd_to_eval);
				j++;
			}
		}
		i++;
	}
}

static char	*get_path_env(char **envp)
{
	int		i;
	char	*path_line;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_line = ft_strdup(envp[i]);
			return (path_line);
		}
		i++;
	}
	return (NULL);
}

static void	set_cmds(t_pipex *pipex, char **argv)
{
	int		i;
	int		j;
	int		split_len;
	char	**split;

	i = 0;
	while (i < pipex->n_cmds)
	{
		j = 0;
		if (ft_strchr(argv[2 + i], '\''))
			treat_quotes(argv[2 + i], pipex->commands, i);
		else
		{
			split = ft_split(argv[2 + i], ' ');
			split_len = ft_count_matrix((void **)split);
			pipex->commands[i] = ft_calloc(sizeof(char *), split_len + 1);
			while (split[j] != NULL)
			{
				pipex->commands[i][j] = ft_strdup(split[j]);
				j++;
			}
			ft_free_matrix((void **)split);
		}
		i++;
	}
}
