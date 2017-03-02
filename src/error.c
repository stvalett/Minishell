/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:59:27 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/02 18:08:18 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_error_dollar_bis(char *av, char **env_bis, int *index)
{
	char	*tmp;
	int		i;
	int		k;

	if ((tmp = (char *)malloc(sizeof(char ) * ft_strlen(av) + 1)) == NULL)
		return (NULL);
	i = 0;
	while (av[i] == '$')
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

void	ft_error_dollar(char **av, char **env_bis)
{
	char	*tmp;
	int 	i;
	int		index;

	i = 0;
	index = 0;
	while (av[++i])
		if ((ft_strchr(av[i], '$')) != NULL && ft_no_digit(av[i]) == 0 && ft_strlen(av[i]) > 1)
		{
			tmp = ft_error_dollar_bis(av[i], env_bis, &index);
			if (tmp == NULL)
			{
				ft_putendl_fd("Illegal variable name.", 2);
				break;
			}
			if (index < 0)
			{
				ft_putstr_fd(tmp, 2);
				ft_putchar_fd(':', 2);
				ft_putendl_fd(" Undefined variable.", 2);
				free(tmp);
				break;
			}
			free(tmp);
		}
}

char *ft_error_acco(char *line, char **av, int flag)
{
	char	*tmp;
	int 	count;
	int 	i;
	int 	j;

	i = -1;
	count = 0;
	tmp = NULL;
	while (line[++i])
	{
		if (line[i] == '"' && flag == 1)
			count++;
		else if (line[i] == '\'' && flag == 0)
			count++;
	}
	if (count % 2 == 1 && ft_is_dollar_n_acco(av) == 0)
		ft_putendl_fd("Unmatched .", 2);
	else if (ft_is_dollar_n_acco(av) == 1)
		ft_putendl_fd("Illegal variable name.", 2);
	else
	{
		if ((tmp = (char *)malloc(sizeof(char) * ft_strlen(line) + 1)) == NULL)
			return (NULL);
		i = 0;
		j = 0;
		while ((line[i] == '"' || line[i] == '\'') && line[i])
			i++;
		while (line[i] != '"' && line[i] != '\'' && line[i])
		{
			tmp[j] = line[i];
			i++;
			j++;
		}
		tmp[j] = '\0';
	}
	return (tmp);
}
