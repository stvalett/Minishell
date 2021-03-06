/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 15:05:15 by stvalett          #+#    #+#             */
/*   Updated: 2017/04/03 11:23:39 by stvalett         ###   ########.fr       */
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
		else
			ft_putchar('\n');
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
	char			*path;

	if (av[1] != NULL)
		ft_parse_cd(env_bis, av[1]);
	else
	{
		if ((path = ft_get_home(env_bis)) != NULL && chdir(path) < 0)
			ft_error_env(av[1], 1);
		if (path != NULL)
		{
			ft_pwd_n_oldpwd(env_bis, path, 1);
			free(path);
		}
		else
		{
			chdir("/Users/stvalett");
			ft_pwd_n_oldpwd(env_bis, "/Users/stvalett", 1);
		}
	}
	return (1);
}

int	ft_cmd_env(char **av, char **env_bis, char *line)
{
	if (av[1] != NULL)
	{
		if (ft_check_env(av, env_bis, line) == 1)
			return (1);
	}
	else
		ft_print_env(env_bis, 0);
	return (1);
}
