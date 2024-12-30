/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:11:56 by marsenij          #+#    #+#             */
/*   Updated: 2024/10/10 13:33:55 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static void	ft_freeme(char **array, char *str, int i)
{
	free(str);
	while (i >= 0)
	{
		free(array[i]);
		i--;
	}
	free(array);
}

static int	ft_wordcnt(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s != c && *s != '\0')
			s++;
		i++;
		while (*s == c && *s != '\0')
			s++;
	}
	return (i);
}

static int	ft_wordlen(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static int	ft_getnextword(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	while (s[i] == c && s[i] != '\0')
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	int		wordcnt;
	char	**array;
	int		i;
	int		index;
	char	*str;

	index = 0;
	i = -1;
	str = ft_strtrim(s, &c);
	if (str == NULL)
		return (NULL);
	wordcnt = ft_wordcnt(str, c);
	array = (char **) malloc ((wordcnt + 1) * sizeof (char *));
	if (!array)
		return (free(str), NULL);
	while (++i < wordcnt)
	{
		array [i] = (char *) malloc(ft_wordlen(&str[index], c) + 1);
		if (array [i] == NULL)
			return (ft_freeme(array, str, i), NULL);
		ft_strlcpy(&array[i][0], &str[index], (ft_wordlen(&str[index], c) + 1));
		index += ft_getnextword(&str[index], c);
	}
	array[i] = NULL;
	return (free(str), array);
}
