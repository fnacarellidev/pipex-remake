/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_names_and_params.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:11:07 by fnacarel          #+#    #+#             */
/*   Updated: 2022/12/29 13:56:45 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/pipex.h"

char	*set_cmd_name(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i])
	{
		while (cmd[i] != ' ')
			i++;
		return (ft_substr(cmd, 0, i));
	}
	return (NULL);
}

char	**get_flags_from_cmd(char *cmd)
{
	int		i;
	int		cmd_len;
	char	*flags;
	char	**splitted_flags;

	i = 0;
	cmd_len = ft_strlen(cmd);
	while (cmd[i] != ' ' && cmd[i] != '\0')
		i++;
	if (cmd[i] != '\0')
	{
		flags = ft_substr(cmd, i + 1, cmd_len - 1);
		if (ft_strchr(cmd, 39))
			splitted_flags = ft_split(flags, 39);
		else
			splitted_flags = ft_split(flags, ' ');
		free(flags);
		return (splitted_flags);
	}
	return (NULL);
}
