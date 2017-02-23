/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:24:08 by stvalett          #+#    #+#             */
/*   Updated: 2017/02/22 11:24:09 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_setenv(const char *line, const char *value, char **env)
{
  char	*path;
  int	len;
  int	i;

  len = (ft_strlen(line) + 1) + (ft_strlen(value) + 1);
  if ((path = (char *)malloc(sizeof(*path) * len)) == NULL)
    return (NULL);
  ft_strcpy(path, line);
  ft_strcat(path, "=");
  ft_strcat(path, value);
  i = ft_get_env(path, env);
  if (i >= 0)
  {
    env[i] = path;
  }
  return (env);
}

int	ft_get_env(char *line, char **env)
{
  int 	i;
  char	*path;

  if ((path = (char *)malloc(sizeof(*path) * ft_strlen(line))) == NULL)
    return (-1);
  ft_strcpy(path, line);
  //ft_strcat(path, "=");
  i = 0;
  while (env[i])
  {
    if ((ft_strncmp(env[i], path, ft_strlen(path))) == 0)
    {
      free(path);
      return (i);
    }
    i++;
  }
  free(path);
  return (-1);
}
