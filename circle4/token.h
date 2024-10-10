/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:29:32 by marsenij          #+#    #+#             */
/*   Updated: 2024/10/10 14:37:20 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdlib.h>


typedef struct s_token
{
	char			*word;
	char			*op;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
	struct s_token	**head;
}	t_token;

//for split
char	*ft_strtrim(char const *s1, char const *set);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strdup(const char *src);
int	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
void printlist(t_token *head);
//for testing
void printCharPointerArray(char **arr);
void printlist_type(t_token *head);
#endif
