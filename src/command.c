/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 10:07:55 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/31 10:30:21 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	int		ft_cmd_basic(char **av, char ***env_bis, char *line)
{
	if (*av == NULL)
		return (1);
	if ((ft_strcmp(av[0], "exit")) == 0)
		exit(0);
	else if ((ft_strcmp(av[0], "cd")) == 0)
		return (ft_cmd_cd(av, env_bis));
	else if (ft_strcmp(av[0], "echo") == 0
			|| ft_strcmp(av[0], "\"echo\"") == 0
			|| ft_strcmp(av[0], "\'echo\'") == 0)
		return (ft_cmd_echo(av, *env_bis));
	else if (ft_strcmp(av[0], "env") == 0 || ft_strcmp(av[0], "ENV") == 0
			|| ft_strcmp(av[0], "\"env\"") == 0
			|| ft_strcmp(av[0], "\'env\"") == 0)
		return (ft_cmd_env(av, *env_bis, line));
	else if ((ft_strcmp(av[0], "setenv")) == 0)
		return (ft_cmd_setenv(av, env_bis));
	else if ((ft_strcmp(av[0], "unsetenv")) == 0)
		return (ft_cmd_unsetenv(av, env_bis));
	return (0);
}

static	void	ft_cmd_exec_bis(char **av, char **env_bis, char *line)
{
	if ((ft_cmd_execve(av, env_bis, line, 0)) == 0)
	{
		ft_free(av, 0);
		exit(1);
	}
	exit(0);
}

char			*ft_get_home(char ***env_bis)
{
	int		i;
	int		flag;
	char	*path;

	i = 0;
	flag = 0;
	if ((i = ft_getenv("HOME", *env_bis)) >= 0)
	{
		flag = 1;
		path = ft_oldpwd_or_home(env_bis, flag);
		return (path);
	}
	return (NULL);
}

int				ft_start_exec(char *line, char ***env_bis)
{
	char	**av;
	pid_t	pid;

	if ((av = ft_strsplit(line, ' ')) != NULL)
	{
		if ((ft_cmd_basic(av, env_bis, line)) == 0)
		{
			pid = fork();
			if (pid > 0)
				waitpid(pid, NULL, 0);
			if (pid == 0)
				ft_cmd_exec_bis(av, *env_bis, line);
			else
			{
				ft_free(av, 0);
				return (pid);
			}
		}
		ft_free(av, 0);
	}
	return (1);
}
