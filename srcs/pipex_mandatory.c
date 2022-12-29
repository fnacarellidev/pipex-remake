/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_mandatory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:25:17 by fnacarel          #+#    #+#             */
/*   Updated: 2022/12/29 13:59:10 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/pipex.h"

static void	close_fds(t_pipex *pipex);
static int	quit_program(t_pipex *pipex, int status);
static void	run_first_cmd(t_pipex *pipex, char **envp);
static void	run_second_cmd(t_pipex *pipex, char **envp);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		return_code;
	int		status;

	validate_files(argc, argv, envp);
	init_pipex(&pipex, argc, argv, envp);
	pipe(pipex.kernel_fd);
	if (pipex.infile_fd != -1)
	{
		run_first_cmd(&pipex, envp);
		close(pipex.infile_fd);
	}
	close(pipex.kernel_fd[1]);
	run_second_cmd(&pipex, envp);
	close(pipex.kernel_fd[0]);
	close(pipex.outfile_fd);
	if (pipex.infile_fd != -1)
		wait(NULL);
	wait(&status);
	return_code = quit_program(&pipex, status);
	return (return_code);
}

static void	run_first_cmd(t_pipex *pipex, char **envp)
{
	pipex->pid = fork();
	if (pipex->pid == 0)
	{
		if (pipex->program_path[0] == NULL)
		{
			close_fds(pipex);
			ft_free_matrix_size_n((void **)pipex->program_path, pipex->n_cmds);
			ft_free_spatial_matrix((void ***)pipex->commands);
			exit(127);
		}
		dup2(pipex->infile_fd, 0);
		dup2(pipex->kernel_fd[1], 1);
		close_fds(pipex);
		execve(pipex->program_path[0], pipex->commands[0], envp);
	}
}

static void	run_second_cmd(t_pipex *pipex, char **envp)
{
	pipex->pid = fork();
	if (pipex->pid == 0)
	{
		if (pipex->program_path[1] == NULL)
		{
			close_fds(pipex);
			ft_free_matrix_size_n((void **)pipex->program_path, pipex->n_cmds);
			ft_free_spatial_matrix((void ***)pipex->commands);
			exit(127);
		}
		dup2(pipex->kernel_fd[0], 0);
		dup2(pipex->outfile_fd, 1);
		close_fds(pipex);
		execve(pipex->program_path[1], pipex->commands[1], envp);
	}
}

static int	quit_program(t_pipex *pipex, int status)
{
	if (pipex->program_path[0] == NULL)
	{
		if (pipex->commands[0][0] != 0)
			ft_printf("%s: command not found\n", pipex->commands[0][0]);
	}
	if (pipex->program_path[1] == NULL)
	{
		if (pipex->commands[1][0] != 0)
			ft_printf("%s: command not found\n", pipex->commands[1][0]);
		ft_free_matrix_size_n((void **)pipex->program_path, pipex->n_cmds);
		ft_free_spatial_matrix((void ***)pipex->commands);
		return (127);
	}
	ft_free_matrix_size_n((void **)pipex->program_path, pipex->n_cmds);
	ft_free_spatial_matrix((void ***)pipex->commands);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

static void	close_fds(t_pipex *pipex)
{
	if (pipex->infile_fd != -1)
		close(pipex->infile_fd);
	close(pipex->outfile_fd);
	close(pipex->kernel_fd[0]);
	close(pipex->kernel_fd[1]);
}
