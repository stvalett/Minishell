/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:23:45 by stvalett          #+#    #+#             */
/*   Updated: 2017/02/22 11:49:29 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_cmd_basic(char **av, char **env)
{

	env = (char **)env;
	if ((ft_strcmp(av[0], "exit")) == 0)
		return (1);
	// return (ft_cmd_exit());
	else if ((ft_strcmp(av[0], "cd")) == 0)
		return (1);
	// return (ft_cmd_cd());
	else if ((ft_strcmp(av[0], "echo")) == 0)
		return (1);
	// return (ft_cmd_echo());
	else if (ft_strcmp(av[0], "env") == 0 || ft_strcmp(av[0], "ENV") == 0)
		return (ft_cmd_env(av, env));
	else if ((ft_strcmp(av[0], "setenv")) == 0)
		return (1);
	// return (ft_cmd_setenv());
	else if ((ft_strcmp(av[0], "unsetenv")) == 0)
		return (1);
	// return (ft_cmd_unsetenv());
	return (0);
}

static char	*ft_get_path_try(char *av, char *dir)
{
	char	*path;
	int	len_max;

	len_max = ((ft_strlen(av) + 1) + (ft_strlen(dir) + 1));
	if ((path = (char *)malloc(sizeof(*path) * len_max)) == NULL)
		return (NULL);
	ft_strcpy(path, dir);
	ft_strcat(path, "/");
	ft_strcat(path, av);
	if (access(path, X_OK) == 0)
		return (path);
	free(path);
	path = NULL;
	return (path);
}

/*static char	*ft_get_home(char *av, char **env)
  {
  int i;

  i = 0;
  if ((i = ft_get_env(av, env)) >= 0)
  return (env[i] + 5);
  return (NULL);
  }*/

static char	*ft_get_path(char *av, char **env)
{
	char	*path;
	char	*tmp;
	char	**str;
	int	i;

	path = NULL;
	if ((i = ft_get_env("PATH", env)) >= 0)
		path = env[i] + 5;
	if (path != NULL && (str = ft_strsplit(path, ':')) != NULL)
	{
		i = 0;
		while (str[i])
		{
			if ((tmp = ft_get_path_try(av, str[i])) != NULL)
			{
				ft_free(str, 1);
				return (tmp);
			}
			i++;
		}
	}
	return (av);
}

static int	ft_cmd_exec_child(char **av, char **env)
{
	if ((execve(ft_get_path(av[0], env), av, env)) < 0)
	{
		ft_putstr_fd("Minishell: command not found: ", 2);
		ft_putendl_fd(av[0], 2);
		return (0);
	}
	return (1);
}

int	ft_cmd_exec(char *line, char **env)
{
	char	**av;
	pid_t	pid;

	if ((av = ft_get_av(line, env)) != NULL)
	{
		if ((ft_cmd_basic(av, env)) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				if ((ft_cmd_exec_child(av, env)) == 0)
				{
					ft_free(av, 0);
					exit(0);
				}
				exit(1);
			}
			else
			{
				ft_free(av, 0);
				return (pid);
			}
		}
	}
	return (1);
}
