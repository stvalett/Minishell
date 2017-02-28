/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 10:34:04 by stvalett          #+#    #+#             */
/*   Updated: 2017/02/28 13:24:01 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	ft_count_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	ft_free(char **str, int flag)
{
	int i;

	i = 0;
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
