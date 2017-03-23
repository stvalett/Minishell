/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 11:25:05 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/23 14:55:35 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char			*ft_env_without_bis(char **env_bis, int index)
{
	char	*tmp;
	int		i;

	if ((tmp = (char*)malloc(sizeof(char)
					* ft_strlen(env_bis[index]) + 1)) == NULL)
		return (NULL);
	i = 0;
	while (env_bis[index][i] != '=' && env_bis[index][i])
		i++;
	i++;
	ft_at_strcpy(tmp, env_bis[index], i);
	return (tmp);
}

static	void	ft_env_without2(char **env_bis, int index)
{
	char	*tmp;

	tmp = ft_env_without_bis(env_bis, index);
	ft_putstr(tmp);
	free(tmp);
}

static	int		ft_free_getpatch(char *s1, char *s2, int flag)
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

void			ft_env_without(char **av, char **env_bis)
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

char			*ft_getpath_bis(char *s1, char *s2)
{
	char	*tmp;
	char	*path;

	path = ft_strdup(s1);
	tmp = path;
	free(path);
	path = ft_strjoin(tmp, "=");
	tmp = path;
	free(path);
	if (s2 != NULL)
		path = ft_strjoin(tmp, s2);
	return (path);
}

char			*ft_getpath(const char *line, const char *value)
{
	char	*path;
	char	*s1;
	char	*s2;
	int		flag;

	flag = 0;
	s1 = ft_no_metachr((char *)line);
	s2 = NULL;
	if (value != NULL)
	{
		s2 = ft_no_metachr((char *)value);
		flag = 1;
	}
	path = ft_getpath_bis(s1, s2);
	ft_free_getpatch(s1, s2, flag);
	return (path);
}
