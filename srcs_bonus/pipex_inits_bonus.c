/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_inits_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:02:32 by fnacarel          #+#    #+#             */
/*   Updated: 2023/01/02 14:49:16 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/pipex_bonus.h"

static char	*get_path_env(char **envp);
static void	set_cmds(t_pipex *pipex, char **argv);
static void	set_program_path(t_pipex *pipex, char **envp);
static void	where_is(char **splitted_path, t_pipex *pipex, int i);

void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		pipex->here_doc = 1;
	else
		pipex->here_doc = 0;
	if (pipex->here_doc)
	{
		pipex->n_cmds = argc - 4;
		pipex->infile_fd = copy_stdin_to_tmpfile(argv);
	}
	else
	{
		pipex->n_cmds = argc - 3;
		pipex->infile_fd = open(argv[1], O_RDONLY);
	}
	pipex->outfile_fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC,
			0644);
	if (pipex->outfile_fd == -1)
	{
		ft_printf("Failed to open/create outfile.\n");
		exit(1);
	}
	pipex->commands = ft_calloc(sizeof(char **), pipex->n_cmds + 1);
	pipex->program_path = ft_calloc(sizeof(char *), pipex->n_cmds + 1);
	set_cmds(pipex, argv);
	set_program_path(pipex, envp);
}

static void	set_program_path(t_pipex *pipex, char **envp)
{
	int		i;
	char	*path_env_var;
	char	**splitted_path_env;

	i = 0;
	path_env_var = get_path_env(envp);
	splitted_path_env = ft_split(path_env_var, ':');
	free(path_env_var);
	format_splitted_path_env(splitted_path_env);
	while (i < pipex->n_cmds)
	{
		where_is(splitted_path_env, pipex, i);
		i++;
	}
	ft_free_matrix((void **)splitted_path_env);
}

static void	where_is(char **splitted_path, t_pipex *pipex, int i)
{
	int		j;
	char	*cmd_to_eval;

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
	if (access(pipex->commands[i][0], F_OK | X_OK) == 0 \
			&& ft_strchr(pipex->commands[i][0], 47))
		pipex->program_path[i] = ft_strdup(pipex->commands[i][0]);
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
	char	**split;
	int		split_len;

	i = 0;
	while (i < pipex->n_cmds)
	{
		j = 0;
		if (ft_strchr(argv[2 + i + pipex->here_doc], '\''))
			treat_quotes(argv[2 + i + pipex->here_doc], &(pipex->commands[i]));
		else
		{
			split = ft_split(argv[2 + i + pipex->here_doc], ' ');
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
