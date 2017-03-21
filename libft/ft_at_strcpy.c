#include "libft.h"

char    *ft_at_strcpy(char  *dest, const char *src, int index)
{
    int j;

    j = 0;
    while (src[index])
    {
        dest[j] = src[index];
        j++;
        index++;
    }
    dest[j] = '\0';
    return (dest);
}
