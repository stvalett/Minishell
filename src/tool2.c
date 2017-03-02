/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 13:13:26 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/02 14:54:45 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_is_acco(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int	ft_is_dollar_n_acco(char **av)
{
	int i;
	int j;

	i = -1;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
		{
			if (av[i][j] == '$' && av[i][j + 1] == '"')
				return (1);
		}
	}
	return (0);
}
