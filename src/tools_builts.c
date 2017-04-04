/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_builts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 10:09:09 by stvalett          #+#    #+#             */
/*   Updated: 2017/04/03 11:23:40 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	char	*ft_oldpwd_or_add(char ***env_bis)
{
	int		index;
	int		i;
	char	*tmp;

	tmp = NULL;
	if ((index = ft_getenv("PWD", *env_bis)) >= 0)
	{
		if ((tmp = (char *)malloc(sizeof(char)
						* (ft_strlen(env_bis[0][index]) + 1))) == NULL)
			return (NULL);
		i = 0;
		while (env_bis[0][index][i] != '=' && env_bis[0][index][i])
			i++;
		i++;
		ft_at_strcpy(tmp, env_bis[0][index], i);
	}
	return (tmp);
}

static	void	ft_switch_pwd(char ***env_bis)
{
	char	*str;
	char	*tmp;

	str = ft_oldpwd_or_add(env_bis);
	tmp = ft_oldpwd_or_home(env_bis, 0);
	if (str)
	{
		*env_bis = ft_setenv("OLDPWD", str, *env_bis);
		free(str);
	}
	if (tmp)
	{
		*env_bis = ft_setenv("PWD", tmp, *env_bis);
		free(tmp);
	}
}

char			*ft_oldpwd_or_home(char ***env_bis, int flag)
{
	char	*str;
	int		index;
	int		i;

	str = NULL;
	if (flag == 0)
	{
		index = ft_getenv("OLDPWD", *env_bis);
		if (index < 0)
			return (NULL);
	}
	else
		index = ft_getenv("HOME", *env_bis);
	if (index >= 0)
	{
		if ((str = (char *)malloc(sizeof(char)
						* (ft_strlen(env_bis[0][index]) + 1))) == NULL)
			return (NULL);
		i = 0;
		while (env_bis[0][index][i] != '=' && env_bis[0][index][i])
			i++;
		i++;
		ft_at_strcpy(str, env_bis[0][index], i);
	}
	return (str);
}

int				ft_pwd_n_oldpwd(char ***env_bis, char *path, int flag)
{
	char	*tmp;
	char	str[1024];

	getcwd(str, sizeof(str));
	tmp = ft_oldpwd_or_add(env_bis);
	if (tmp)
	{
		*env_bis = ft_setenv("OLDPWD", tmp, *env_bis);
		free(tmp);
	}
	if (flag == 0)
		*env_bis = ft_setenv("PWD", str, *env_bis);
	else
		*env_bis = ft_setenv("PWD", path, *env_bis);
	return (0);
}

int				ft_add_pwd_n_oldpwd(char ***env_bis, char *av, int flag)
{
	char	*tmp;
	char	str[1024];

	getcwd(str, sizeof(str));
	if ((ft_strncmp(av, "-", 1)) == 0)
	{
		ft_switch_pwd(env_bis);
		return (0);
	}
	else if (flag == 1)
		return (0);
	tmp = ft_oldpwd_or_add(env_bis);
	*env_bis = ft_setenv("OLDPWD", tmp, *env_bis);
	free(tmp);
	*env_bis = ft_setenv("PWD", str, *env_bis);
	return (0);
}
