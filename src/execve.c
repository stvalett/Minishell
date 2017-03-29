#include "../include/minishell.h"

static  char    *ft_get_path_try(char *av, char *dir)
{
    char	*path;
    int		len_max;

    len_max = ((ft_strlen(av) + 1) + (ft_strlen(dir) + 1));
    if ((path = (char *)malloc(sizeof(*path) * len_max)) == NULL)
        return (NULL);
    ft_strcpy(path, dir);
    ft_strcat(path, "/");
    ft_strcat(path, av);
    if (access(path, X_OK) == 0)
        return (path);
    free(path);
    path = NULL;
    return (path);
}

static  char    *ft_get_path(char *av, char **env)
{
    char	*path;
    char	*tmp;
    char	**str;
    int		i;

    path = NULL;
    if ((i = ft_getenv("PATH", env)) >= 0)
        path = env[i] + 5;
    if (path != NULL && (str = ft_strsplit(path, ':')) != NULL)
    {
        i = 0;
        while (str[i])
        {
            if ((tmp = ft_get_path_try(av, str[i])) != NULL)
            {
                ft_free(str, 1);
                return (tmp);
            }
            i++;
        }
    }
    return (av);
}

static  char    *ft_move_to_index(char  *line)
{
    char    *str;
    int     i;
    int     j;

    if ((str = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1))) == NULL)
        return (NULL);
    i = 0;
    while (line[i] != ' ' && line[i])
        i++;
    i++;
    while (line[i])
    {
        str[j] = line[i];
        j++;
        i++;
    }
    str[j] = '\0';
    return (str);
}

int		ft_cmd_execve(char **av, char **env_bis, char *line, int index)
{
    char	**tab;
    char    *str;
    int     ret;
    int     i;

    i = -1;
    ret = 0;
    str = (index == 1) ? ft_move_to_index(line) : NULL;
    if ((execve(ft_get_path(av[index], env_bis), av + index, env_bis)) < 0)
    {
        tab = (index == 1) ? ft_parse_av(str, av, env_bis, &ret) :
            ft_parse_av(line, av, env_bis, &ret);
        if (tab)
        {
            while (tab[++i])
            {
                ft_putstr_fd(tab[i], 2);
                ft_putchar_fd(' ', 2);
                if ((i == 0 || i == 1) && ret == 1)
                    break;
            }
            ft_putendl_fd(": Command not found", 2);
            ft_free(tab, 0);
        }
        return (0);
    }
    return (1);
}


/*int ft_env_execve(char **av, char **env_bis)
{
    char    *str;
    int     flag;
    int     index;

    flag = 0;
    if (av[1] && ft_is_here(av[1], '$', 1) == 1)
    {
        str = ft_env_without_bis(av, 1, '$');
        if ((index = ft_getenv(str, env_bis)) >= 0)
        {
            free(str);
            str = ft_env_without_bis(env_bis, index, '=');
        }
        flag = 1;
    }
    if ((execve(ft_get_path(av[1], env_bis), av + 1, NULL)) == -1)
    {
        if (flag)
        {
            ft_error_env(str, 0);
            free(str);
        }
        else
            ft_error_env(av[1], 0);
        return (0);
    }
    return (1);
}*/
