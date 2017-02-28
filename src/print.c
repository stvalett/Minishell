/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:44:50 by stvalett          #+#    #+#             */
/*   Updated: 2017/02/28 13:48:46 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_print_env(char **env_bis)
{
  int i;

  if (env_bis == NULL)
    return ;
  i = 0;
  while (env_bis[i])
  {
    ft_putendl(env_bis[i]);
    i++;
  }
}

void	ft_print_dollar_bis(char **av, char **env_bis)
{
	char			*tmp;
	int				flag;
	int				index;
	int				i;

	flag = 0;
	index = 0;
	i = 0;
	while (av[++i])
		if ((ft_strchr(av[i], '$')) != NULL && ft_no_digit(av[i]) == 0)
		{
			tmp = ft_strcpy_cara(av[i]);
			if ((index = ft_get_env(tmp, env_bis)) < 0)
				flag = 1;
		}
	if (flag == 1)
		ft_error_dollar(av, env_bis);
	else
		ft_env_without(av, env_bis, &flag);
	ft_putchar('\n');
	free(tmp);
}

void	ft_print_dollar(char **av, char **env_bis)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (av[++i])
	{
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
			j = 0;
		}
	}
	ft_putchar('\n');
}
