#include "../include/minishell.h"

int     ft_check_setenv(char **av, char ***env_bis)
{
    int     count;

    count = ft_count_av(av);
    if (count >= 4)
    {
        ft_putendl_fd("Error too few argument", 2);
        return (1);
    }
    else if (count == 1)
    {
        ft_print_env(*env_bis, 0);
        return (1);
    }
    else if (av[1] != NULL || av[2] != NULL)
    {
        if (ft_parse_setenv(av[1]) == 1)
            return (1);
        else if (av[2] != NULL && av[2][0] == '$')
        {
            if ((ft_parse_setenv2(av, env_bis)) == 1)
                return (1);
        }
    }
    return (0);
}

int     ft_parse_setenv(char *av)
{
    int i;
    int flag;

    i = -1;
    flag = 0;
    while (av[++i])
    {
        if (ft_isdigit(av[i]) == 1 && i == 0
                && ft_strncmp(av, "_", 1) != 0 && (flag = 1))
            break;
        else if (ft_isalpha(av[i]) == 0 && i == 0
                && ft_strncmp(av, "_", 1) != 0 && (flag = 1))
            break;
        else if (ft_isalnum(av[i]) == 0 && i > 0 && (flag = 2))
            break;
    }
    if (flag == 1 || flag == 2)
    {
        ft_error_setenv(NULL, flag);
        return (1);
    }
    return (0);
}

int     ft_parse_setenv2(char **av, char ***env_bis)
{
    int     index;
    int     i;
    char    *str;

    if ((str = (char *)malloc(sizeof(char) * ft_strlen(av[2]) + 1)) == NULL)
        return (1);
    i = 0;
    while (av[2][i] != '$' && av[2][i])
        i++;
    i++;
    ft_at_strcpy(str, av[2], i);
    if ((index = ft_get_env(str, *env_bis)) >= 0)
    {
        free(str);
        str = ft_env_without_bis(*env_bis, index);
        *env_bis = ft_setenv(av[1], str, *env_bis);
        return (1);
    }
    else
    {
        ft_error_setenv(str, 3);
        return (1);
    }
    return (0);
}
