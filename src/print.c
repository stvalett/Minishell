/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:44:50 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/30 15:06:36 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	void	ft_print_dollar_bis(char **av, char **env_bis)
{
	char	*tmp;
	int		flag;
	int		index;
	int		i;

	flag = 0;
	index = 0;
	i = 0;
	while (av[++i])
		if ((ft_strchr(av[i], '$')) != NULL
				&& ft_no_digit(av[i]) == 0 && ft_strlen(av[i]) > 1)
		{
			tmp = ft_strcpy_cara(av[i]);
			if ((index = ft_getenv(tmp, env_bis)) < 0)
				flag = 1;
			if (tmp)
				free(tmp);
		}
	if (flag == 1)
		ft_error_dollar(av, env_bis);
	else
	{
		ft_env_without(av, env_bis);
		ft_putchar('\n');
	}
}

void			ft_print_dollar(char **av, char **env_bis)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == '$' && ft_isdigit(av[i][j + 1]) == 1)
				;
			if ((av[i][j] == '$' && ft_isalpha(av[i][j + 1]) == 1)
					|| av[i][j] == '$')
			{
				ft_print_dollar_bis(av, env_bis);
				return ;
			}
			j++;
		}
	}
	ft_putchar('\n');
}

void			ft_print_dollar_n_acco(char **av, char **env_bis, int flag)
{
	char	**tmp;
	int		i;

	if (ft_print_acco(av, flag) == 0)
		return ;
	if ((tmp = (char **)malloc(sizeof(char *) * ft_count_av(av) + 1)) == NULL)
		exit(1);
	i = -1;
	while (++i < ft_count_av(av))
		tmp[i] = ft_no_metachr(av[i]);
	tmp[i] = NULL;
	ft_print_dollar(tmp, env_bis);
	ft_free(tmp, 0);
}

static	void	ft_print_acco_bis(char **av)
{
	char	*tmp;
	int		i;

	i = 0;
	while (av[++i])
	{
		tmp = ft_no_metachr(av[i]);
		ft_putstr(tmp);
		ft_putchar(' ');
		free(tmp);
	}
	ft_putchar('\n');
}

int				ft_print_acco(char **av, int flag)
{
	int		i;
	int		j;
	int		count;

	count = 0;
	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
        {
			if (av[i][j] == '"' || av[i][j] == '\'')
				count++;
        }
	}
	if (ft_error_bracket(count, av, flag) == 0)
		return (0);
	else if (flag == 3)
		ft_print_acco_bis(av);
	return (1);
}
