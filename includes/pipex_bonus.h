/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:58:54 by fnacarel          #+#    #+#             */
/*   Updated: 2023/01/02 14:48:42 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef	PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "../libft/libft.h"
# include "../42-get-next-line/get_next_line.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	pid_t	pid;
	int		infile_fd;
	int		outfile_fd;
	int		kernel_fd[128][2];
	int		n_cmds;
	int		here_doc;
	char	*path_env;
	char	**program_path;
	char	***commands;
}	t_pipex;

char	*set_err_msg(char **envp, char *suffix);
void	treat_quotes(char *str, char ***commands);
void	format_splitted_path_env(char **splitted_env);
void	validate_input(int argc, char **argv, char **envp);
void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp);
void	run_first_cmd(t_pipex *pipex, char **envp);
void	run_n_cmd(t_pipex *pipex, char **envp, int i);
void	run_last_cmd(t_pipex *pipex, char **envp, int i);
int		copy_stdin_to_tmpfile(char **argv);

#endif
