/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:23:52 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/24 17:01:29 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cmd_echo(char **av, char **env_bis)
{
	int	flag;

	flag = 0;
	if (av[0] != NULL)
	{
		if (av[1] != NULL)
		{
			ft_check_dollar_n_acco(av, &flag);
			if (flag == 1)
				ft_print_dollar(av, env_bis);
			else if (flag == 2)
				ft_print_dollar_n_acco(av, env_bis, flag);
			else if (flag == 3)
				ft_print_acco(av, flag);
			else
				ft_print_env(av, 1);
		}
	}
	return (1);
}

int	ft_cmd_unsetenv(char **av, char ***env)
{
	if (av[1] != NULL)
	{
		if (av[2] != NULL)
			*env = ft_unsetenv(av[1], av[2], *env);
		else
			*env = ft_unsetenv(av[1], "", *env);
	}
	else
		ft_putendl_fd("setenv: Too many arguments", 2);
	return (1);
}

int	ft_cmd_setenv(char **av, char ***env_bis)
{
	if (ft_check_setenv(av, env_bis) == 0)
	{
		if (av[1] != NULL)
		{
			if (av[2] != NULL)
				*env_bis = ft_setenv(av[1], av[2], *env_bis);
			else
				*env_bis = ft_setenv(av[1], "", *env_bis);
		}
	}
	return (1);
}

int	ft_cmd_cd(char **av, char ***env_bis)
{
	char		*path;
	char		*tmp;
	int			flag;

	flag = 0;
	if (av[1] != NULL)
	{
		path = av[1];
		if ((ft_strncmp(path, "-", 1)) == 0)
		{
			tmp = ft_oldpwd_or_home(env_bis, 0);
			if (chdir(tmp) < 0)
				ft_print_error(av[1]);
			free(tmp);
		}
		else
		{
			if (chdir(path) < 0)
			{
				flag = 1;
				ft_print_error(av[1]);
			}
		}
		if ((ft_strncmp(av[1], "..", ft_strlen(av[1]))) == 0)
			ft_pwd_n_oldpwd(env_bis);
		else
			ft_add_pwd_n_oldpwd(env_bis, av[1], flag);
	}
	else
	{
		if ((path = ft_get_home(env_bis)) != NULL && chdir(path) < 0)
			ft_print_error(av[1]);
		ft_pwd_n_oldpwd_bis(env_bis, path);
		free(path);
	}
	return (1);
}

int	ft_cmd_env(char **av, char ***env_bis)
{
	if (av[1] != NULL)
	{
		if (ft_strncmp(av[1], "-i", 2) == 0)
			return (1);
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	else
		ft_print_env(*env_bis, 0);
	return (1);
}
