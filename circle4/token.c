/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:29:23 by marsenij          #+#    #+#             */
/*   Updated: 2024/10/10 15:03:41 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token	*ft_lstnew(char *word)
{
	t_token	*elem;

	elem = malloc(sizeof(t_token));
	if (!elem)
		return (NULL);
	elem->word = word;
	elem->next = NULL;
	return (elem);
}

t_token	*ft_lstlast(t_token *lst)
{
	t_token	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*end;

	if (!new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		end = ft_lstlast(*lst);
		end->next = new;
	}
}

int	main(int argc, char **argv)
{
	t_token	*token;
	char	**nopipe;
	char	**words;
	int		i;
	int		j;
	t_token *newtoken;

	i = 0;
	j = 0;
	nopipe = NULL;
	words = NULL;
	token = NULL;
	nopipe = ft_split(argv[1], '|');
	while (nopipe[i])
	{
		words = ft_split(nopipe[0], ' ');
		while (words[j])
		{
			newtoken = ft_lstnew(words[j]);
			ft_lstadd_back(&token, newtoken);
			j++;
		}
		//free words
		i++;
	}
	
	//free nopipe
//printCharPointerArray(res);
}
