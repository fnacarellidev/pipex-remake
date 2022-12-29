/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:57:32 by fnacarel          #+#    #+#             */
/*   Updated: 2022/12/29 11:58:16 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	pid_t	pid;
	int		infile_fd;
	int		outfile_fd;
	int		kernel_fd[2];
	int		n_cmds;
	char	*path_env;
	char	**program_path;
	char	***commands;
}	t_pipex;

char	*set_cmd_name(char *cmd);
char	*set_err_msg(char **envp, char *suffix);
void	treat_quotes(char *str, char ***commands);
void	format_splitted_path_env(char **splitted_env);
void	validate_files(int argc, char **argv, char **envp);
void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp);

#endif
