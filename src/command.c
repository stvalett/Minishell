/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:23:52 by stvalett          #+#    #+#             */
/*   Updated: 2017/02/24 17:08:14 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cmd_echo(char **av, char **env_bis)
{
  char	*tmp;
  int 	i;

  if (av[0] != NULL)
  {
    if (av[1] != NULL)
    {
      i = 0;
      if (ft_check_dollar(av) != 0)
      {
	ft_is_dollar(av, env_bis);
	return (1);
      }
      else
      {
	while (av[++i])
	{
	  tmp = ft_no_metachr(av[i]);
	  ft_putstr(tmp);
	  free(tmp);
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
