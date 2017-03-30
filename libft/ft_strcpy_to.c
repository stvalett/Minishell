#include "libft.h"

char    *ft_strcpy_to(const char *src, char c)
{
    char    *dest;
    int     i;

    if ((dest = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1))) == NULL)
        return (NULL);
    i = 0;
    while (src[i] != c && src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}
