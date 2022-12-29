/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:17:06 by fnacarel          #+#    #+#             */
/*   Updated: 2022/12/29 19:01:04 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/pipex_bonus.h"

/* static void	close_fds(t_pipex *pipex); */
void		run_first_cmd(t_pipex *pipex, char **envp);
void		run_second_cmd(t_pipex *pipex, char **envp);
void		run_n_cmd(t_pipex *pipex, char **envp, int i);

void	run_first_cmd(t_pipex *pipex, char **envp)
{
	pipex->pid = fork();
	if (pipex->pid == 0)
	{
		if (pipex->program_path[0] == NULL)
		{
			close(pipex->infile_fd);
			close(pipex->outfile_fd);
			close(pipex->kernel_fd[0][0]);
			close(pipex->kernel_fd[0][1]);
			ft_free_matrix_size_n((void **)pipex->program_path, pipex->n_cmds);
			ft_free_spatial_matrix((void ***)pipex->commands);
			exit(127);
		}
		dup2(pipex->infile_fd, 0);
		dup2(pipex->kernel_fd[0][1], 1);
		close(pipex->infile_fd);
		close(pipex->outfile_fd);
		close(pipex->kernel_fd[0][0]);
		close(pipex->kernel_fd[0][1]);
		execve(pipex->program_path[0], pipex->commands[0], envp);
	}
}

void	run_n_cmd(t_pipex *pipex, char **envp, int i)
{
	pipe(pipex->kernel_fd[i]);
	pipex->pid = fork();
	if (pipex->pid == 0)
	{
		if (pipex->program_path[i] == NULL)
		{
			close(pipex->infile_fd);
			close(pipex->outfile_fd);
			close(pipex->kernel_fd[i - 1][0]);
			close(pipex->kernel_fd[i][1]);
			ft_free_matrix_size_n((void **)pipex->program_path, pipex->n_cmds);
			ft_free_spatial_matrix((void ***)pipex->commands);
			exit(127);
		}
		dup2(pipex->kernel_fd[i - 1][0], 0);
		dup2(pipex->kernel_fd[i][1], 1);
		close(pipex->infile_fd);
		close(pipex->outfile_fd);
		close(pipex->kernel_fd[i - 1][0]);
		execve(pipex->program_path[i], pipex->commands[i], envp);
	}
	close(pipex->kernel_fd[i - 1][0]);
	close(pipex->kernel_fd[i - 1][1]);
	close(pipex->kernel_fd[i][1]);
}

void	run_last_cmd(t_pipex *pipex, char **envp, int i)
{
	pipex->pid = fork();
	if (pipex->pid == 0)
	{
		if (pipex->program_path[i] == NULL)
		{
			close(pipex->infile_fd);
			close(pipex->outfile_fd);
			close(pipex->kernel_fd[i - 1][0]);
			close(pipex->kernel_fd[i][1]);
			ft_free_matrix_size_n((void **)pipex->program_path, pipex->n_cmds);
			ft_free_spatial_matrix((void ***)pipex->commands);
			exit(127);
		}
		dup2(pipex->kernel_fd[i - 1][0], 0);
		dup2(pipex->outfile_fd, 1);
		close(pipex->infile_fd);
		close(pipex->outfile_fd);
		close(pipex->kernel_fd[i - 1][0]);
		execve(pipex->program_path[i], pipex->commands[i], envp);
	}
	close(pipex->kernel_fd[i - 1][0]);
}

/* static void	close_fds(t_pipex *pipex) */
/* { */
/* 	if (pipex->infile_fd != -1) */
/* 		close(pipex->infile_fd); */
/* 	close(pipex->outfile_fd); */
/* 	/1* close(pipex->kernel_fd[0]); *1/ */
/* 	/1* close(pipex->kernel_fd[1]); *1/ */
/* } */
