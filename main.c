/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:32:54 by fnacarel          #+#    #+#             */
/*   Updated: 2022/12/26 14:55:42 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./includes/pipex.h"

int main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	validate_files(argc, argv);
	init_pipex(&pipex, argc, argv, envp);
	pipe(pipex.kernel_fd);
	pipex.pid = fork();
	if (pipex.pid == 0)
	{
		if (pipex.program_path[0] == NULL)
		{
			ft_printf("%s: command not found\n", pipex.commands[0][0]);
			ft_free_matrix_size_n((void **)pipex.program_path, pipex.n_cmds);
			ft_free_spatial_matrix((void ***)pipex.commands);
			exit(127);
		}
		dup2(pipex.infile_fd, 0);
		dup2(pipex.kernel_fd[1], 1);
		close(pipex.infile_fd);
		close(pipex.kernel_fd[0]);
		close(pipex.kernel_fd[1]);
		execve(pipex.program_path[0], pipex.commands[0], NULL);
	}
	waitpid(pipex.pid, NULL, 0);
	pipex.pid = fork();
	if (pipex.pid == 0)
	{
		if (pipex.program_path[1] == NULL)
		{
			ft_printf("%s: command not found\n", pipex.commands[1][0]);
			ft_free_matrix_size_n((void **)pipex.program_path, pipex.n_cmds);
			ft_free_spatial_matrix((void ***)pipex.commands);
			exit(127);
		}
		dup2(pipex.kernel_fd[0], 0);
		dup2(pipex.outfile_fd, 1);
		close(pipex.outfile_fd);
		close(pipex.kernel_fd[0]);
		close(pipex.kernel_fd[1]);
		execve(pipex.program_path[1], pipex.commands[1], NULL);
	}
	close(pipex.infile_fd);
	close(pipex.outfile_fd);
	close(pipex.kernel_fd[0]);
	close(pipex.kernel_fd[1]);
	if (pipex.program_path[1] == NULL)
	{
		ft_free_matrix_size_n((void **)pipex.program_path, pipex.n_cmds);
		ft_free_spatial_matrix((void ***)pipex.commands);
		return (127);
	}
	ft_free_matrix_size_n((void **)pipex.program_path, pipex.n_cmds);
	ft_free_spatial_matrix((void ***)pipex.commands);
	return (0);
}
