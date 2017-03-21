/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 13:13:26 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/10 12:49:19 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strcpy_cara(char *av)
{
	int 	i;
	int	j;
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

char    *ft_strcpy_acco(char *line)
{
    char    *tmp;
    int     i;
    int     j;

    tmp = NULL;
    if ((tmp = (char *)malloc(sizeof(char) * ft_strlen(line) + 1)) == NULL)
			return (NULL);
		i = 0;
		j = -1;
		while ((line[i] == '"' || line[i] == '\'') && line[i])
			i++;
		while (line[i++] != '"' && line[i++] != '\'' && line[i++])
			tmp[++j] = line[i];
		tmp[j] = '\0';
        return (tmp);
}

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
