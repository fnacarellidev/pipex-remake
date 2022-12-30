/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:30:28 by fnacarel          #+#    #+#             */
/*   Updated: 2022/12/30 19:56:28 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*fd_analysis(int fd, char *static_str);
char	*get_line(char *str);
char	*update_main_string(char *s);

char	*get_next_line(int fd, int last_exec)
{
	static char	*str;
	char		*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (last_exec)
	{
		free(str);
		return (NULL);
	}
	str = fd_analysis(fd, str);
	if (!ft_strlen(str))
	{
		free(str);
		return (NULL);
	}
	else
	{
		new_line = get_line(str);
		str = update_main_string(str);
	}
	return (new_line);
}

char	*fd_analysis(int fd, char *static_str)
{
	char	*buf;
	int		read_val;

	buf = malloc(BUFFER_SIZE + 1);
	while (!strchr_gnl(static_str, '\n'))
	{
		read_val = read(fd, buf, BUFFER_SIZE);
		if (read_val <= 0)
		{
			free(buf);
			return (static_str);
		}
		buf[read_val] = '\0';
		static_str = strjoin_gnl(static_str, buf);
		if (!static_str)
		{
			free(buf);
			return (NULL);
		}
	}
	free(buf);
	return (static_str);
}

char	*get_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*update_main_string(char *outdated_string)
{
	int		j;
	char	*updated_string;
	size_t	i;
	size_t	len_old_string;

	i = 0;
	j = 0;
	if (!outdated_string)
		return (NULL);
	len_old_string = ft_strlen(outdated_string);
	while (outdated_string[i] != '\n' && outdated_string[i] != '\0')
		i++;
	if (outdated_string[i] == '\n')
		i++;
	updated_string = malloc(len_old_string - i + 1);
	if (!updated_string)
		return (NULL);
	while (outdated_string[i + j])
	{
		updated_string[j] = outdated_string[i + j];
		j++;
	}
	updated_string[j] = '\0';
	free(outdated_string);
	return (updated_string);
}
