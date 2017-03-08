/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 13:13:26 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/08 10:03:33 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_is_acco(char *line, int *flag)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			if (line[i] == '"')
				*flag = 1;
			else if (line[i] == '\'')
				*flag = 0;
			return (1);
		}
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
			if (av[i][j] == '$' && (av[i][j + 1] == '"' 
						|| av[i][j + 1] == '\''))
				return (1);
		}
	}
	return (0);
}

void	ft_print_error(char *av)
{
	ft_putstr_fd("cd: No such file or directory: ", 2);
	ft_putendl_fd(av, 2);
}
