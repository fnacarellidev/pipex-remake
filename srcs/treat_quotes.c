/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:49:36 by fnacarel          #+#    #+#             */
/*   Updated: 2022/12/29 13:59:20 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/pipex.h"

static void	remove_single_quotes(char **commands);
static void	fix_splitted_string(char **splitted_str, char char_to_fix);
static char	*replace_c1_between_c2(char *str, char c1, char c2, char c3);

void	treat_quotes(char *str, char ***commands)
{
	int		i;
	int		matr_size;
	char	**splitted_str;
	char	*replaced_string;

	replaced_string = replace_c1_between_c2(str, ' ', '\'', '[');
	splitted_str = ft_split(replaced_string, ' ');
	fix_splitted_string(splitted_str, '[');
	matr_size = ft_count_matrix((void **)splitted_str);
	*commands = ft_calloc(sizeof(char *), matr_size + 1);
	i = 0;
	while (splitted_str[i])
	{
		(*commands)[i] = ft_strdup(splitted_str[i]);
		free(splitted_str[i]);
		i++;
	}
	remove_single_quotes(*commands);
	free(splitted_str);
	free(replaced_string);
}

static void	remove_single_quotes(char **commands)
{
	int		i;
	size_t	len_str;
	char	*store_prev_addr;

	i = 0;
	while (commands[i])
	{
		len_str = ft_strlen(commands[i]);
		if (commands[i][0] == '\'' && commands[i][len_str - 1] == '\'')
		{
			store_prev_addr = commands[i];
			commands[i] = ft_substr(commands[i], 1, len_str - 2);
			free(store_prev_addr);
		}
		i++;
	}
}

static void	fix_splitted_string(char **splitted_str, char char_to_fix)
{
	int	i;
	int	j;

	i = 0;
	while (splitted_str[i])
	{
		j = 0;
		while (splitted_str[i][j])
		{
			if (splitted_str[i][j] == char_to_fix)
				splitted_str[i][j] = ' ';
			j++;
		}
		i++;
	}
}

static char	*replace_c1_between_c2(char *str, char c1, char c2, char c3)
{
	int		i;
	char	*str_modified;

	i = 0;
	str_modified = ft_strdup(str);
	while (str[i])
	{
		if (str[i] == c2)
		{
			i++;
			while (str[i] != c2)
			{
				if (str[i] == c1)
					str_modified[i] = c3;
				i++;
			}
		}
		i++;
	}
	return (str_modified);
}
