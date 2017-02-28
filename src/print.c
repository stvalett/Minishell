/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:44:50 by stvalett          #+#    #+#             */
/*   Updated: 2017/02/28 11:16:26 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_dollar_bis(char **av, char **env_bis)
{
	char			*tmp;
	int				flag;
	int				index;
	int				i;

	i = 0;
	flag = 0;
	index = 0;
	while (av[++i])
	{
		tmp = ft_strcpy_cara(av[i]);
		if ((index = ft_get_env(tmp, env_bis)) >= 0)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 0)
		ft_error(av);
	else
		ft_env_without(av, env_bis, &flag, index);
	ft_putchar('\n');
	free(tmp);
}

void	ft_print_dollar(char **av, char **env_bis)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = 0;
		if (av[i][j] == '$')
		{
			while (av[i][j])
			{
				if (av[i][j] == '$' && (av[i][j + 1] == ' ' || av[i][j + 1] == '\0'))
				{
					ft_putchar(av[i][j]);
					ft_putchar(' ');
				}
				else if (av[i][j] == '$' && ft_isdigit(av[i][j + 1]) == 1)
					;
				else if (av[i][j] == '$' && ft_isalpha(av[i][j + 1]) == 1)
				{
					ft_print_dollar_bis(av, env_bis);
					return ;
				}
				j++;
			}
		}
	}
	ft_putchar('\n');
}
