/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:57:32 by fnacarel          #+#    #+#             */
/*   Updated: 2022/12/20 18:39:58 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	pid_t	pid;
	int		infile_fd;
	int		outfile_fd;
	int		n_cmds;
	char	*path_env;
	char	**cmd_name;
	char	**abs_path;
	char	***commands;
}	t_pipex;

char	*set_cmd_name(char *cmd);
char	**get_flags_from_cmd(char *cmd);
int		validate_files(int argc, char **argv);
void	format_splitted_path_env(char **splitted_env);
void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp);

#endif
