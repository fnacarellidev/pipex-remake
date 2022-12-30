/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:43:14 by fnacarel          #+#    #+#             */
/*   Updated: 2022/12/30 18:03:36 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static void	strcat_gnl(char *dest, const char *src)
{
	int		i;
	size_t	dest_len;

	i = 0;
	dest_len = ft_strlen(dest);
	if (src)
	{
		while (*(src + i))
		{
			*(dest + dest_len + i) = *(src + i);
			i++;
		}
	}
}

char	*strjoin_gnl(char *str, char *buf)
{
	char	*finalstr;

	if (!str)
	{
		str = malloc(1 * sizeof(char));
		str[0] = '\0';
	}
	if (!str || !buf)
		return (NULL);
	finalstr = ft_calloc(sizeof(char), ft_strlen(str) + ft_strlen(buf) + 1);
	if (!finalstr)
		return (NULL);
	strcat_gnl(finalstr, str);
	strcat_gnl(finalstr, buf);
	*(finalstr + ft_strlen(str) + ft_strlen(buf)) = '\0';
	free(str);
	return (finalstr);
}

char	*strchr_gnl(char *s, int c)
{
	int			i;
	const char	*first_occurence;

	i = 0;
	first_occurence = 0;
	if (s)
	{
		while (*(s + i))
		{
			if (*(s + i) == (unsigned char) c)
			{
				first_occurence = (s + i);
				return ((char *) first_occurence);
			}
			i++;
		}
		if (c == 0)
			first_occurence = (s + ft_strlen(s));
		return ((char *) first_occurence);
	}
	return (NULL);
}
