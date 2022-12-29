/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_manipulate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:44:24 by fnacarel          #+#    #+#             */
/*   Updated: 2022/12/29 13:56:52 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/pipex.h"

static char	*del_at_start_of_str(char *str, char *str_to_del);
static char	*add_char_at_end_of_str(char *str, char c);

void	format_splitted_path_env(char **splitted_env)
{
	int	i;

	i = 0;
	splitted_env[i] = del_at_start_of_str(splitted_env[i], "PATH=");
	while (splitted_env[i])
	{
		splitted_env[i] = add_char_at_end_of_str(splitted_env[i], '/');
		i++;
	}
}

static char	*del_at_start_of_str(char *str, char *str_to_del)
{
	char	*updated_string;
	int		str_to_del_len;

	str_to_del_len = ft_strlen(str_to_del);
	if (ft_strncmp(str, str_to_del, str_to_del_len) == 0)
	{
		updated_string = ft_substr(str, str_to_del_len, 2147483647);
		free(str);
		return (updated_string);
	}
	return (NULL);
}

static char	*add_char_at_end_of_str(char *str, char c)
{
	int		i;
	int		len_str;
	char	*updated_string;

	i = 0;
	len_str = ft_strlen(str);
	updated_string = ft_calloc(sizeof(char), len_str + 2);
	while (i < len_str)
	{
		updated_string[i] = str[i];
		i++;
	}
	updated_string[i] = c;
	updated_string[++i] = '\0';
	free(str);
	return (updated_string);
}
