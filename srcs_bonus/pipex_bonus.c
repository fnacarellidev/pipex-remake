/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 14:13:45 by fnacarel          #+#    #+#             */
/*   Updated: 2022/12/30 19:59:00 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/pipex_bonus.h"
#include <unistd.h>

static void	print_not_found_cmds(t_pipex pipex);
static int	no_heredoc(int argc, char **argv, char **envp);
static int	heredoc_pipex(char **argv);

int	main(int argc, char **argv, char **envp)
{
	int	ret_code;

	validate_input(argc, argv, envp);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		ret_code = heredoc_pipex(argv);
	else
		ret_code = no_heredoc(argc, argv, envp);
	return (ret_code);
}

static int	heredoc_pipex(char **argv)
{
	int 	tempfile;
	char	*gnl_ret;
	char	*argv_with_nl;

	tempfile = open(".tmpheredocz", O_CREAT | O_APPEND | O_WRONLY, 0644);
	argv_with_nl = ft_strjoin(argv[2], "\n");
	while (1)
	{
		write(1, "heredoc> ", 9);
		gnl_ret = get_next_line(0, 0);
		if (!gnl_ret || ft_strcmp(gnl_ret, argv_with_nl) == 0)
		{
			get_next_line(0, 1);
			free(argv_with_nl);
			free(gnl_ret);
			break ;
		}
		write(tempfile, gnl_ret, ft_strlen(gnl_ret));
		free(gnl_ret);
	}
	return (0);
}

static int	no_heredoc(int argc, char **argv, char **envp)
{
	int		i;
	t_pipex	pipex;
	int		status;

	i = 1;
	init_pipex(&pipex, argc, argv, envp);
	run_first_cmd(&pipex, envp);
	while (i < argc - 4)
		run_n_cmd(&pipex, envp, i++);
	run_last_cmd(&pipex, envp, i);
	if (pipex.infile_fd != -1)
		close(pipex.infile_fd);
	close(pipex.outfile_fd);
	waitpid(pipex.pid, &status, 0);
	i = 1;
	while (i++ < argc - 4)
		wait(NULL);
	print_not_found_cmds(pipex);
	ft_free_matrix_size_n((void **)pipex.program_path, pipex.n_cmds);
	ft_free_spatial_matrix((void ***)pipex.commands);
	if (WIFEXITED(status))
		return (status);
	return (1);
}

static void	print_not_found_cmds(t_pipex pipex)
{
	int	i;

	i = 0;
	while (i < pipex.n_cmds)
	{
		if (pipex.program_path[i] == NULL)
		{
			if (pipex.commands[i][0] != 0)
				ft_printf("%s: command not found\n", pipex.commands[i][0]);
		}
		i++;
	}
}
