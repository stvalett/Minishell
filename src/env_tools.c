/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 11:25:05 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/10 12:48:17 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_env_without_bis(char **env_bis, int index)
{
	char	*tmp;
	int	i;
	int	j;

	if ((tmp = (char*)malloc(sizeof(char) * ft_strlen(env_bis[index]) + 1)) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (env_bis[index][i] != '=')
		i++;
	i++;
	while (env_bis[index][i])
	{
		tmp[j] = env_bis[index][i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

static void	ft_env_without2(char **env_bis, int index)
{
	char	*tmp;

	tmp = ft_env_without_bis(env_bis, index);
	ft_putstr(tmp);
	free(tmp);
}

static int	ft_free_getpatch(char *s1, char *s2, int flag)
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

void	ft_env_without(char **av, char **env_bis)
{
	char	*tmp;
	int		i;
	int		index;

	i = 0;
	index = 0;
	while (av[++i])
	{
		tmp = NULL;
		if (ft_print_one_dollar(av[i]) == 1)
			ft_putstr(av[i]);
		if ((ft_strchr(av[i], '$')) == NULL)
			ft_putstr(av[i]);
		if ((ft_strchr(av[i], '$')) != NULL)
		{
			tmp = ft_strcpy_cara(av[i]);
			index = ft_get_env(tmp, env_bis);
			if (tmp)
				free(tmp);
		}
		if (index >= 0 && tmp != NULL)
			ft_env_without2(env_bis, index);
		ft_putchar(' ');
	}
}

char	*ft_getpath(const char *line, const char *value)
{
	char	*path;
	char	*s1;
	char	*s2;
	int		len;
	int		flag;

	flag = 0;
	s1 = ft_no_metachr((char *)line);
	if (value)
	{
		s2 = ft_no_metachr((char *)value);
		len = ft_strlen(s1) + ft_strlen(s2);
		flag = 1;
	}
	else
		len = ft_strlen(s1);
	if ((path = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	ft_strcpy(path, s1);
	ft_strcat(path, "=");
	ft_strcat(path, s2);
	ft_free_getpatch(s1, s2, flag);
	return (path);
}
