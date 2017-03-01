/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:24:37 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/01 17:24:21 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_get_replace(char **av, char **env)
{
  int	i;
  int	len;
  int	size_total;
  char	*str;

  len = ft_strlen((*av) + 1);
  if ((i = ft_get_env((*av) + 1, env)) > 0)
  {
    size_total = ft_strlen(env[i] + len);
    if ((str = (char *)malloc(sizeof(*str) * size_total + 1)) == NULL)
      exit(1);
    ft_strcpy(str, env[i] + len);
    free(*av);
    *av = str;
    free(str);
  }
}

char	**ft_get_av(char *line, char **env_bis)
{
  char	**av;
  int	i;

  av = ft_strsplit(line, ' ');
  if (av == NULL)
  {
    ft_putendl_fd("av == NULL", 2);
    ft_free(av, 0);
    return (NULL);
  }
  else
  {
    i = -1;
    while (av[++i])
      if (av[i][0] == '~' && ft_strlen(av[i]) > 0)
	ft_get_replace(&av[i], env_bis);
  }
  return (av);
}
