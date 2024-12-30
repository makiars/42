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

#include <stdio.h>

int add_tokentype(char *word)
{
    if (word[1] != '\0') // Ensure only single characters are checked
        return 0;

    if (word[0] == '~')
        return 1;  // Home directory
    else if (word[0] == '`')
        return 2;  // Command substitution (archaic)
    else if (word[0] == '#')
        return 3;  // Comment
    else if (word[0] == '$')
        return 4;  // Variable expression
    else if (word[0] == '&')
        return 5;  // Background job
    else if (word[0] == '*')
        return 6;  // String wildcard
    else if (word[0] == '(')
        return 7;  // Start subshell
    else if (word[0] == ')')
        return 8;  // End subshell
    else if (word[0] == '\\')
        return 9;  // Quote next character
    else if (word[0] == '|')
        return 10; // Pipe
    else if (word[0] == '[')
        return 11; // Start character-set wildcard
    else if (word[0] == ']')
        return 12; // End character-set wildcard
    else if (word[0] == '{')
        return 13; // Start command block
    else if (word[0] == '}')
        return 14; // End command block
    else if (word[0] == ';')
        return 15; // Shell command separator
    else if (word[0] == '\'')
        return 16; // Strong quote
    else if (word[0] == '"')
        return 17; // Weak quote
    else if (word[0] == '<')
        return 18; // Input redirect
    else if (word[0] == '>')
        return 19; // Output redirect
    else if (word[0] == '/')
        return 20; // Pathname directory separator
    else if (word[0] == '?')
        return 21; // Single-character wildcard
    else if (word[0] == '!')
        return 22; // Pipeline logical NOT
    else
        return 0;  // If no match, return 0
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
		//printf("NOPIPE ARRAY:%s\n\n",nopipe[i]);	
		words = ft_split(nopipe[i], ' ');
		while (words[j])
		{
			//printf("WORDS ARRAY:%s\n\n",words[j]);	
			newtoken = ft_lstnew(words[j]);
			ft_lstadd_back(&token, newtoken);
			j++;
			newtoken->type = add_tokentype(newtoken->word);
		}
		//free words
		if(nopipe[i+1] != NULL)
		{
			newtoken = ft_lstnew("|");
			ft_lstadd_back(&token, newtoken);
			newtoken->type = 9;
		}
		j = 0;
		i++;
	}
	//free nopipe
	printlist(token);
	printlist_type(token);
//printCharPointerArray(res);
}
