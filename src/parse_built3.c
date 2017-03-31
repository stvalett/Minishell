/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_built3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 13:01:19 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/30 13:11:27 by stvalett         ###   ########.fr       */
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

static  char    **ft_parse_avbis(char **tab, char *tmp, int flag)
{
    int i;

    i = -1;
    if (flag == 2)
    {
        while (tab[++i])
            if (ft_is_here(tab[i], '$', 1) == 1 && i == 0)
            {
                ft_error_setenv(tab[i], 3);
                return (NULL);
            }
    }
    else
    {
        i = -1;
        while (tab[++i])
            if (ft_is_here(tab[i], '$', 1) == 1 && (i == 0 || i == 1) && tmp)
            {
                free(tab[i]);
                tab[i] = ft_strdup(tmp);
            }
        free(tmp);
    }
    return (tab);
}

static  char    **ft_parse_av2(char *line, char **env_bis, int *ret)
{
    char    **tab;
    char    *tmp;
    int     flag;

    tab = NULL;
    flag = 0;
    *ret = 1;
    tab = ft_strsplit2(line);
    tmp = ft_good_index(tab, env_bis, &flag);
    if (tmp == NULL && flag == 2)
        return (ft_parse_avbis(tab, tmp, flag));
    return (ft_parse_avbis(tab, tmp, flag));
}

static  char    **ft_parse_av1(char **env_bis, char *tmp)
{
    int     i;
    int     flag;
    char    *tmp2;
    char    **tab;

    flag = 0;
    tab = NULL;
    i = -1;
    tab = ft_strsplit2(tmp);
    while (tab[++i])
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
        {
            if (line[0] != '"')
                *ret = 1;
            return (tab = ft_parse_av1(env_bis, str));
        }
    }
    else
    {
        return (tab = ft_parse_av2(line, env_bis, ret));
    }
	return (NULL);
}
