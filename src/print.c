/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:44:50 by stvalett          #+#    #+#             */
/*   Updated: 2017/02/27 18:21:09 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_dollar_bis(char **av, char **env_bis)
{
	char	*tmp;
	int		flag;
	int		i;
	int		k;
	int		j;
	int		save;

	i = 0;
	flag = 0;
	while (av[++i])
	{
		if ((tmp = (char *)malloc(sizeof(char) * (ft_strlen(av[i]) + 1))) == NULL)
			exit(1);
		k = -1;
		j = 0;
		while (av[i][++k])
		{
			if(av[i][k] != '$')
			{
				tmp[j] = av[i][k];
				j++;
			}
			if (av[i][k] == ' ')
				break;
		}
		tmp[j] = '\0';
		j = -1;
		save = 0;
		while (env_bis[++j])
			if ((ft_strncmp(tmp, env_bis[j], ft_strlen(tmp))) == 0)
			{
				flag = 1;
				//ft_putendl(env_bis[j]);
				free(tmp);
				//return ;
				save = j;
				break;
			}
	}
	if (flag == 0)
	{
		ft_error(tmp);
		free(tmp);
	}
	else
	{
		i = 0;
		while (av[++i])
			if ((ft_strchr(av[i], '$')) == NULL)
			{
				ft_putstr(av[i]);
				ft_putchar(' ');
				if (flag == 1)
				{
					ft_putstr(env_bis[save]);
					ft_putchar(' ');
					flag = 0;
				}
			}
	}
	ft_putchar('\n');
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
