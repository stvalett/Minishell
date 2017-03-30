/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 13:19:00 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/30 15:25:52 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
