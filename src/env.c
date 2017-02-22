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

int	ft_get_env(char *line, char **env)
{
  int 	i;
  char	*path;

  if ((path = (char *)malloc(sizeof(*path) * ft_strlen(line))) == NULL)
    return (-1);
  ft_strcpy(path, line);
  ft_strcat(path, "=");
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
  return (0);
}
