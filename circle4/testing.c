#include <stdio.h>
#include "token.h"

void printCharPointerArray(char **arr) 
{
	int i = 0;

    while (arr[i] != NULL) 
	{
        printf("%s\n", arr[i]);
		i++;
    }
}

void print_words(t_token *head)
{
    t_token *current = head;

    // Traverse the list and print each word
    while (current != NULL)
    {
        if (current->word != NULL)
            printf("%s\n", current->word);
        current = current->next;
    }
}