/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 10:34:04 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/24 18:14:25 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_here(char *av, char c, int flag)
{
	int i;

	i = 0;
	if (ft_strlen(av) == 1 || flag == 1)
	{
		if (av[i] == c)
			return (1);
        if (flag == 1)
        {
            while (av[i])
            {
                if (av[i] == c)
                    return (1);
                i++;
            }
        }
	}
	return (0);
}

int	ft_no_digit(char *av)
{
	int i;
	int	flag;

	i = -1;
	flag = 0;
	while (av[++i])
	{
		if (ft_isdigit(av[i]) == 1)
			flag = 1;
	}
	return (flag);
}

int	ft_free(char **str, int flag)
{
	int i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	if (flag == 1)
		return (1);
	else
		return (0);
}

int		ft_free_str(char *s1, char *s2, int flag)
{
	if (flag == 1)
	{
		free(s1);
		free(s2);
	}
	else
		free(s1);
	return (0);
}

char	*ft_no_metachr(char *av)
{
	char		*str;
	char const	*start;
	char const	*end;

	start = NULL;
	if (!av)
		return (av);
	while (*av)
	{
		if (!(*av == '"' || *av == '\''))
		{
			start = (start == NULL) ? av : start;
			end = av;
		}
		av++;
	}
	if (start == NULL)
		return (ft_strnew(1));
	if ((str = (char *)malloc(sizeof(*str) * (end - start) + 2)) == NULL)
		return (NULL);
	av = (char *)start;
	while (av <= end)
		*str++ = *av++;
	*str = '\0';
	return (str - (end - start + 1));
}
