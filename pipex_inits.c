/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:59:42 by fnacarel          #+#    #+#             */
/*   Updated: 2022/12/20 18:41:51 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./includes/pipex.h"

static void	set_cmds(t_pipex *pipex, char **argv);

void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	if (envp)
	{}
	pipex->n_cmds = argc - 3;
	pipex->infile_fd = open(argv[1], O_RDONLY);
	pipex->outfile_fd = open(argv[argc - 1], O_WRONLY | O_TRUNC);
	if (pipex->infile_fd == -1 || pipex->outfile_fd == -1)
	{
		ft_printf("Failed to open one of the files, please try again.\n");
		exit(1);
	}
	pipex->commands = ft_calloc(sizeof(char **), pipex->n_cmds + 1);
	pipex->cmd_name = ft_calloc(sizeof(char *), pipex->n_cmds + 1);
	pipex->abs_path = ft_calloc(sizeof(char *), pipex->n_cmds + 1);
	set_cmds(pipex, argv);
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
		split = ft_split(argv[2 + i], ' ');
		split_len = ft_count_matrix((void **)split);
		pipex->commands[i] = ft_calloc(sizeof(char *), split_len + 1);
		while (split[j] != NULL)
		{
			pipex->commands[i][j] = ft_strdup(split[j]);
			j++;
		}
		ft_free_matrix((void **)split);
		i++;
	}
}
