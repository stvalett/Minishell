/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 10:45:17 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/23 12:02:26 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char    *ft_oldpwd_or_add(char ***env_bis, char *av, int flag)
{
    int     index;
    int     i;
    char    *tmp;

    tmp = NULL;
    index = ft_get_env("PWD", *env_bis);
    if ((tmp = (char *)malloc(sizeof(char) * (ft_strlen(env_bis[0][index]) + 1))) == NULL)
        return (NULL);
    i = 0;
    while (env_bis[0][index][i] != '=' && env_bis[0][index][i])
        i++;
    i++;
    ft_at_strcpy(tmp, env_bis[0][index], i);
    if (flag == 1)
    {
        ft_strcat(tmp, "/");
        ft_strcat(tmp, av);
    }
    return (tmp);
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
