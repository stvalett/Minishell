/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 14:39:14 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/23 14:40:55 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_env(char **env_bis, int flag)
{
	int	i;

	i = 0;
	if (flag == 1)
		i = 1;
	while (env_bis[i])
	{
		if (flag == 1)
		{
			ft_putstr(env_bis[i]);
			ft_putchar(' ');
		}
		else
			ft_putendl(env_bis[i]);
		i++;
	}
	if (flag == 1)
		ft_putchar('\n');
}

char	*ft_oldpwd_or_add(char ***env_bis)
{
	int		index;
	int		i;
	char	*tmp;

	tmp = NULL;
	index = ft_get_env("PWD", *env_bis);
	if ((tmp = (char *)malloc(sizeof(char)
					* (ft_strlen(env_bis[0][index]) + 1))) == NULL)
		return (NULL);
	i = 0;
	while (env_bis[0][index][i] != '=' && env_bis[0][index][i])
		i++;
	i++;
	ft_at_strcpy(tmp, env_bis[0][index], i);
	return (tmp);
}

int		ft_pwd_n_oldpwd_bis(char ***env_bis, char *path)
{
	char	*tmp;

	tmp = ft_oldpwd_or_add(env_bis);
	*env_bis = ft_setenv("OLDPWD", tmp, *env_bis);
	free(tmp);
	*env_bis = ft_setenv("PWD", path, *env_bis);
	return (0);
}

int		ft_pwd_n_oldpwd(char ***env_bis)
{
	char	*tmp;
	char	str[1024];

	getcwd(str, sizeof(str));
	tmp = ft_oldpwd_or_add(env_bis);
	*env_bis = ft_setenv("OLDPWD", tmp, *env_bis);
	free(tmp);
	*env_bis = ft_setenv("PWD", str, *env_bis);
	return (0);
}

int		ft_add_pwd_n_oldpwd(char ***env_bis, char *av, int flag)
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
