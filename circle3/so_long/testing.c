#include "so_long.h"

void print_string_array(char **array)
{
    int i = 0;

    while (array[i] != NULL)
    {
        printf("%s", array[i]);
        i++;
    }
}