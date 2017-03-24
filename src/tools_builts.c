/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_builts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 10:21:36 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/24 18:14:28 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_oldpwd_or_home(char ***env_bis, int flag)
{
	char	*str;
	int		index;
	int		i;

	if (flag == 0)
		index = ft_get_env("OLDPWD", *env_bis);
	else
		index = ft_get_env("HOME", *env_bis);
	if ((str = (char *)malloc(sizeof(char)
					* (ft_strlen(env_bis[0][index]) + 1))) == NULL)
		return (NULL);
	i = 0;
	while (env_bis[0][index][i] != '=' && env_bis[0][index][i])
		i++;
	i++;
	ft_at_strcpy(str, env_bis[0][index], i);
	return (str);
}

void	ft_switch_pwd(char ***env_bis)
{
	char	*str;
	char	*tmp;

	str = ft_oldpwd_or_add(env_bis);
	tmp = ft_oldpwd_or_home(env_bis, 0);
	*env_bis = ft_setenv("OLDPWD", str, *env_bis);
	free(str);
	*env_bis = ft_setenv("PWD", tmp, *env_bis);
	free(tmp);
}

char			*ft_get_home(char ***env_bis)
{
	int		i;
	int		flag;
	char	*path;

	i = 0;
	flag = 0;
	if ((i = ft_get_env("HOME", *env_bis)) >= 0)
	{
		flag = 1;
		path = ft_oldpwd_or_home(env_bis, flag);
		return (path);
	}
	return (NULL);
}

void	ft_check_dollar_n_acco(char **av, int *flag)
{
	int count;
	int	count2;
	int i;

	i = -1;
	count = 0;
	count2 = 0;
	while (av[++i])
	{
		if ((ft_strchr(av[i], '$')) != NULL)
			count++;
		if (((ft_strchr(av[i], '"')) != NULL
					|| ft_strchr(av[i], '\'') != NULL)
				&& ft_strcmp(av[i], "\"echo\"") != 0)
			count2++;
	}
	if (count >= 1 && count2 >= 1)
		*flag = 2;
	else if (count >= 1 && !count2)
		*flag = 1;
	else if (count2 >= 1 && !count)
		*flag = 3;
	else
		*flag = 0;
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
