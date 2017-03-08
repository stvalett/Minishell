#include "../include/minishell.h"

char    *ft_add_pwd(char ***env_bis, char *av)
{
    int     index;
    int     i;
    int     j;
    char    *tmp;

    index = ft_get_env("PWD", *env_bis);
    if ((tmp = (char *)malloc(sizeof(char)
                    * (ft_strlen(env_bis[0][index]) + ft_strlen(av) + 1))) == NULL)
        return (NULL);
    i = 0;
    while (env_bis[0][index][i] != '=')
        i++;
    i++;
    j = 0;
    while (env_bis[0][index][i])
    {
        tmp[j] = env_bis[0][index][i];
        j++;
        i++;
    }
    tmp[j] = '\0';
    ft_strcat(tmp, "/");
    ft_strcat(tmp, av);
    return (tmp);
}
