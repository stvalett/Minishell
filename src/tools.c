/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 10:34:04 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/24 18:14:25 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_here(char *av, char c, int flag)
{
	int i;

	i = 0;
	if (ft_strlen(av) == 1 || flag == 1)
	{
		if (av[i] == c)
			return (1);
        if (flag == 1)
        {
            while (av[i])
            {
                if (av[i] == c)
                    return (1);
                i++;
            }
        }
	}
	return (0);
}

int	ft_no_digit(char *av)
{
	int i;
	int	flag;

	i = -1;
	flag = 0;
	while (av[++i])
	{
		if (ft_isdigit(av[i]) == 1)
			flag = 1;
	}
	return (flag);
}

int	ft_free(char **str, int flag)
{
	int i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	if (flag == 1)
		return (1);
	else
		return (0);
}

int		ft_free_str(char *s1, char *s2, int flag)
{
	if (flag == 1)
	{
		free(s1);
		free(s2);
	}
	else
		free(s1);
	return (0);
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
