/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 13:13:26 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/23 14:42:26 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strcpy_cara(char *av)
{
	int		i;
	int		j;
	char	*tmp;

	if ((tmp = (char *)malloc(sizeof(char) * ft_strlen(av) + 1)) == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (av[++i])
	{
		if (av[i] != '$')
		{
			tmp[j] = av[i];
			j++;
		}
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*ft_strcpy_acco(char *line)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = NULL;
	if ((tmp = (char *)malloc(sizeof(char) * ft_strlen(line) + 1)) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while ((line[i] == '"' || line[i] == '\'') && line[i])
		i++;
	while (line[i] != '"' && line[i] != '\'' && line[i])
    {
		tmp[j] = line[i];
        j++;
        i++;
    }
	tmp[j] = '\0';
	return (tmp);
}

char			*ft_parse_acco(char *line, char **av, int flag)
{
	char	*tmp;
	int		count;
	int		i;

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
	if (ft_error_bracket(count, av, flag) == 0)
		return (tmp);
	else
		tmp = ft_strcpy_acco(line);
	return (tmp);
}

int		ft_is_acco(char *line, int *flag)
{
	int	i;

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

int		ft_is_dollar_n_acco(char **av)
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
