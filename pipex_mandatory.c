/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_mandatory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:25:17 by fnacarel          #+#    #+#             */
/*   Updated: 2022/12/28 18:10:41 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "includes/pipex.h"
#include "libft/libft.h"

static int	quit_program(t_pipex *pipex);
static void	run_first_cmd(t_pipex *pipex, char **envp);
static void	run_second_cmd(t_pipex *pipex, char **envp);
static void	print_err(char *str);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		return_code;

	validate_files(argc, argv, envp);
	init_pipex(&pipex, argc, argv, envp);
	pipe(pipex.kernel_fd);
	run_first_cmd(&pipex, envp);
	close(pipex.kernel_fd[1]);
	close(pipex.infile_fd);
	run_second_cmd(&pipex, envp);
	close(pipex.kernel_fd[0]);
	close(pipex.outfile_fd);
	wait(NULL);
	wait(NULL);
	return_code = quit_program(&pipex);
	return (return_code);
}

static void	run_first_cmd(t_pipex *pipex, char **envp)
{
	pipex->pid = fork();
	if (pipex->pid == 0)
	{
		if (pipex->program_path[0] == NULL)
		{
			print_err(pipex->commands[0][0]);
			ft_free_matrix_size_n((void **)pipex->program_path, pipex->n_cmds);
			ft_free_spatial_matrix((void ***)pipex->commands);
			exit(127);
		}
		dup2(pipex->infile_fd, 0);
		dup2(pipex->kernel_fd[1], 1);
		close(pipex->infile_fd);
		close(pipex->outfile_fd);
		close(pipex->kernel_fd[0]);
		close(pipex->kernel_fd[1]);
		execve(pipex->program_path[0], pipex->commands[0], envp);
	}
}

static void	print_err(char *str)
{
	if (str != 0)
		ft_printf("%s: command not found\n", str);
	return ;
}

static void	run_second_cmd(t_pipex *pipex, char **envp)
{
	pipex->pid = fork();
	if (pipex->pid == 0)
	{
		if (pipex->program_path[1] == NULL)
		{
			print_err(pipex->commands[1][0]);
			ft_free_matrix_size_n((void **)pipex->program_path, pipex->n_cmds);
			ft_free_spatial_matrix((void ***)pipex->commands);
			exit(127);
		}
		dup2(pipex->kernel_fd[0], 0);
		dup2(pipex->outfile_fd, 1);
		close(pipex->infile_fd);
		close(pipex->outfile_fd);
		close(pipex->kernel_fd[0]);
		close(pipex->kernel_fd[1]);
		execve(pipex->program_path[1], pipex->commands[1], envp);
	}
}

static int	quit_program(t_pipex *pipex)
{
	/* close(pipex->infile_fd); */
	/* close(pipex->outfile_fd); */
	/* close(pipex->kernel_fd[0]); */
	/* close(pipex->kernel_fd[1]); */
	if (pipex->program_path[1] == NULL)
	{
		ft_free_matrix_size_n((void **)pipex->program_path, pipex->n_cmds);
		ft_free_spatial_matrix((void ***)pipex->commands);
		return (127);
	}
	ft_free_matrix_size_n((void **)pipex->program_path, pipex->n_cmds);
	ft_free_spatial_matrix((void ***)pipex->commands);
	return (0);
}
