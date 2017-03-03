/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:23:52 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/03 13:42:04 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cmd_echo(char **av, char **env_bis)
{
	int 	i;
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
			{
				i = 0;
				while (av[++i])
				{
					ft_putstr(av[i]);
					ft_putchar(' ');
				}
				ft_putchar('\n');
			}
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
		ft_putendl_fd("Error too few argument", 2);
	return (1);
}

int	ft_cmd_setenv(char **av, char ***env)
{
	if (av[1] != NULL)
	{
		if (av[2] != NULL)
			*env = ft_setenv(av[1], av[2], *env);
		else
			*env = ft_setenv(av[1], "", *env);
	}
	else
		ft_putendl_fd("Error too few argument", 2);
	return (1);
}

int	ft_cmd_cd(char **av, char **env)
{
	char	*path;

	if (av[1] != NULL)
	{
		path = av[1];
		if (chdir(path) < 0)
		{
			ft_putstr_fd("cd: No such file or directory: ", 2);
			ft_putstr_fd(av[1], 2);
		}
	}
	else
	{
		if ((path = ft_get_home(env)) != NULL && chdir(path) < 0)
		{
			ft_putstr_fd("cd: No such file or directory: ", 2);
			ft_putstr_fd(av[1], 2);
		}
	}
	env = ft_setenv("PWD", path, env);
	return (1);
}

int	ft_cmd_env(char **av, char ***env_bis)
{
	if (av[1] != NULL)
		ft_putendl_fd("Error env", 2);
	else
		ft_print_env(*env_bis);
	return (1);
}
