/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 13:19:00 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/29 16:00:42 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static  char    *ft_good_index(char **av, char **env_bis, int *flag)
{
    char        *tmp;
    int         i;
    int         index;

    i = -1;
    tmp = NULL;
    while (av[++i])
    {
        if (ft_strchr(av[i], '$') != NULL)
        {
            *flag = 2;
            tmp = ft_env_without_bis(av, i, '$');
            if ((index = ft_getenv(tmp, env_bis)) >= 0)
            {
                free(tmp);
                tmp = ft_env_without_bis(env_bis, index, '=');
                *flag = 1;
                return (tmp);
            }
        }
    }
    return (NULL);
}

static  char    **ft_parse_av2(char *line, char **env_bis, int *ret)
{
    char    **tab;
    char    *tmp;
    int     flag;
    int     i;

    tab = NULL;
    flag = 0;
    *ret = 1;
    tab = ft_strsplit2(line);
    tmp = ft_good_index(tab, env_bis, &flag);
    if (tmp == NULL && flag == 2)
    {
        i = -1;
        while (tab[++i])
            if (ft_is_here(tab[i], '$', 1) == 1 && i == 0)
            {
                ft_error_setenv(tab[i], 3);
                return (NULL);
            }
    }
    i = -1;
    while (tab[++i])
        if (ft_is_here(tab[i], '$', 1) == 1 && (i == 0 || i == 1) && tmp)
        {
            free(tab[i]);
            tab[i] = ft_strdup(tmp);
        }
    free(tmp);
    return (tab);
}

static  char    **ft_parse_av1(char **env_bis, char *tmp)
{
    int     i;
    int     flag;
    char    *tmp2;
    char    **tab;

    flag = 0;
    tab = NULL;
    i = 0;
    tab = ft_strsplit2(tmp);
    while (tab[i])
    {
        tmp2 = ft_good_index(tab, env_bis, &flag); 
        if (tmp2 == NULL && flag == 2 && ft_is_here(tab[i], '$', 1) == 1)
        {
            ft_error_setenv(tab[i], 3);
            return (NULL);
        }
        if (ft_is_here(tab[i], '$', 1) == 1 && tmp2)
        {
            free(tab[i]);
            tab[i] = ft_strdup(tmp2);
        }
        i++;
    }
	free(tmp2);
    return (tab);
}

char    **ft_parse_av(char *line, char **av, char **env_bis, int *ret)
{
    int     flag;
    char    **tab;
    char    *str;

    flag = 0;
    tab = NULL;
    if (ft_is_acco(line, &flag) == 1)
    {
        if ((str = ft_parse_acco(line, av, flag)) != NULL)
            return (tab = ft_parse_av1(env_bis, str));
    }
    else
        return (tab = ft_parse_av2(line, env_bis, ret));
	return (NULL);
}

void	ft_print_env(char **env_bis, int flag)
{
    int	i;

    i = 0;
    if (flag == 1)
        i = 1;
    while (env_bis[i])
    {
        if (flag == 1)
        {
            ft_putstr(env_bis[i]);
            ft_putchar(' ');
        }
        else
            ft_putendl(env_bis[i]);
        i++;
    }
    if (flag == 1)
        ft_putchar('\n');
}

char			*ft_get_home(char ***env_bis)
{
    int		i;
    int		flag;
    char	*path;

    i = 0;
    flag = 0;
    if ((i = ft_getenv("HOME", *env_bis)) >= 0)
    {
        flag = 1;
        path = ft_oldpwd_or_home(env_bis, flag);
        return (path);
    }
    return (NULL);
}

void	ft_check_dollar_n_acco(char **av, int *flag)
{
    int count;
    int	count2;
    int i;

    i = -1;
    count = 0;
    count2 = 0;
    while (av[++i])
    {
        if ((ft_strchr(av[i], '$')) != NULL)
            count++;
        if (((ft_strchr(av[i], '"')) != NULL
                    || ft_strchr(av[i], '\'') != NULL)
                && ft_strcmp(av[i], "\"echo\"") != 0)
            count2++;
    }
    if (count >= 1 && count2 >= 1)
        *flag = 2;
    else if (count >= 1 && !count2)
        *flag = 1;
    else if (count2 >= 1 && !count)
        *flag = 3;
    else
        *flag = 0;
}
