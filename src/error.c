/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:59:27 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/23 14:06:58 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	char	*ft_error_dollar_bis(char *av, char **env_bis, int *index)
{
	char	*tmp;
	int		i;
	int		k;

	if ((tmp = (char *)malloc(sizeof(char ) * ft_strlen(av) + 1)) == NULL)
		return (NULL);
	i = 0;
	while (av[i] == '$' && av[i])
		i++;
	k = 0;
	if (av[i] == '"')
	{
		free(tmp);
		return (NULL);
	}
	while (av[i] != ' ' && av[i])
	{
		tmp[k] = av[i];
		k++;
		i++;
	}
	tmp[k] = '\0';
	*index = ft_get_env(tmp, env_bis);
	return (tmp);
}

void			ft_error_dollar(char **av, char **env_bis)
{
	char	*tmp;
	int		i;
	int		index;

	i = 0;
	index = 0;
	while (av[++i])
		if ((ft_strchr(av[i], '$')) != NULL
				&& ft_no_digit(av[i]) == 0 && ft_strlen(av[i]) > 1)
		{
			tmp = ft_error_dollar_bis(av[i], env_bis, &index);
			if (tmp == NULL)
			{
				ft_putendl_fd("Illegal variable name.", 2);
				break ;
			}
			if (index < 0)
			{
				ft_error_setenv(tmp, 3);
				break ;
			}
			free(tmp);
		}
}

int				ft_error(int count, char **av)
{
	if (count % 2 == 1 && ft_is_dollar_n_acco(av) == 0)
	{
		ft_putendl_fd("Unmatched .", 2);
		return (0);
	}
	else if (ft_is_dollar_n_acco(av) == 1)
	{
		ft_putendl_fd("Illegal variable name.", 2);
		return (0);
	}
	return (1);
}

void			ft_error_setenv(char *str, int flag)
{
	if (flag == 1)
		ft_putendl_fd("setenv: Variable name must begin with a letter", 2);
	else if (flag == 2)
	{
		ft_putstr_fd("setenv: Variable name must contain", 2);
		ft_putendl_fd(" alphanumeric characters", 2);
	}
	else if (flag == 3)
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": Undefined variable", 2);
		free(str);
	}
}
