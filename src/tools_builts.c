/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 10:45:17 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/09 11:52:23 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char    *ft_pwdbis(char *str)
{
    int     i;
    int     j;
    char    *tmp2;

    tmp2 = NULL;
    if ((tmp2 = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))) == NULL)
        return (NULL);
    i = 0;
    j = 0;
    while (str[i] != '=' && str[i])
        i++;
    i++;
    while (str[i])
    {
        tmp2[j] = str[i];
        j++;
        i++;
    }
    tmp2[j] = '\0';
    return (tmp2);
}

char    *ft_oldpwd(char ***env_bis)
{
    int     index;
    int     i;
    int     j;
    char    *tmp;

    tmp = NULL;
    index = ft_get_env("PWD", *env_bis);
    if ((tmp = (char *)malloc(sizeof(char) * (ft_strlen(env_bis[0][index]) + 1))) == NULL)
        return (NULL);
    i = 0;
    while (env_bis[0][index][i] != '=' && env_bis[0][index][i])
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
    return (tmp);
}

char    *ft_pwd(char ***env_bis)
{
    int     i;
    int     j;
    int     index;
    char    *tmp;
    char    *str;

    str = NULL;
    tmp = NULL;
    index = ft_get_env("PWD", *env_bis);
    if ((tmp = (char *)malloc(sizeof(char) * (ft_strlen(env_bis[0][index]) + 1))) == NULL)
        return (NULL);
    j = ft_strlen(env_bis[0][index]) - 1;
    while (env_bis[0][index][j] != '/')
        j--;
    i = 0;
    while (env_bis[0][index][i] && i < j)
    {
        tmp[i] = env_bis[0][index][i];
        i++;
    }
    tmp[i] = '\0';
    str = ft_pwdbis(tmp);
    free(tmp);
    return (str);
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
        if (((ft_strchr(av[i], '"')) != NULL  || ft_strchr(av[i], '\'') != NULL)
                && ft_strcmp(av[i], "\"echo\"") != 0)
            count2++;
    }
    if (count >= 1 && count2 >= 1)
        *flag = 2;
    else if(count >= 1 && !count2)
        *flag = 1;
    else if (count2 >= 1 && !count)
        *flag = 3;
    else
        *flag = 0;
}

char	*ft_no_metachr(char *av)
{
    char		*str;
    char const	*start;
    char const	*end;

    start = NULL;
    if (!av)
        return (av);
    while (*av)
    {
        if (!(*av == '"' || *av == '\''))
        {
            start = (start == NULL) ? av : start;
            end = av;
        }
        av++;
    }
    if (start == NULL)
        return (ft_strnew(1));
    if ((str = (char *)malloc(sizeof(*str) * (end - start) + 2)) == NULL)
        return (NULL);
    av = (char *)start;
    while (av <= end)
        *str++ = *av++;
    *str = '\0';
    return (str - (end - start + 1));

}
