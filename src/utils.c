/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 10:38:53 by stvalett          #+#    #+#             */
/*   Updated: 2017/02/24 17:15:32 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_print_no_dollar(char *av)
{
  int 	i;
  int	j;
  char	*tmp;

  if ((tmp = (char *)malloc(sizeof(char) * ft_strlen(av) + 1)) == NULL)
    return ;
  j = 0;
  i = -1;
  while (av[++i])
  {
    if (av[i] != '$' && av[i] != '"' && ft_strlen(av) > 0)
    {
      tmp[j] = av[i];
      j++;
    }
    tmp[j] = '\0';
  ft_putstr(tmp);
  write(1, " ", 1);
  }
  free(tmp);
  write(1, "\n", 1);
}

int	ft_check_dollar(char **av)
{
  int count;
  int i;

  i = -1;
  while (av[++i])
    if ((ft_strchr(av[i], '$')) != NULL)
      count++;
  return (count);
}

int	ft_is_dollar(char **av, char **env_bis)
{
  int 	i;
  int	k;
  int	j;
  char	*tmp;

  i = 0;
  while (av[++i])
    if (av[i][0] == '$' && av[i][1] != '\0')
    {
      if ((tmp = (char *)malloc(sizeof(char) * ft_strlen(av[i]))) == NULL)
	return (-1);
      k = -1;
      j = 0;
      while (av[i][++k])
	if (av[i][k] != '$')
	{
	  tmp[j] = av[i][k];
	  j++;
	}
      j = -1;
      while (env_bis[++j])
	if ((ft_strncmp(tmp, env_bis[j], ft_strlen(tmp))) == 0)
	{
	  ft_putendl(env_bis[j]);
	  free(tmp);
	  return (1);
	}
    }
    else
      ft_print_no_dollar(av[i]);
  return (0);
}

char	**ft_cpy_env(char **env, int len, char *path)
{
  char		**tmp;
  int			count;
  int			i;
  static int	len_bis = 0;

  len_bis += len;
  count = ft_count_env(env);
  if ((tmp = (char **)malloc(sizeof(char *) * (count + len_bis + 1))) == NULL)
    return (NULL);
  i = -1;
  while (++i < count)
  {
    if ((tmp[i] = (char *)malloc(sizeof(char) * (ft_strlen(env[i]) + 1))) == NULL)
      return (NULL);
    tmp[i] = ft_strcpy(tmp[i], env[i]);
  }
  if (path == NULL)
  {
    tmp[i] = NULL;
    return (tmp);
  }
  if ((tmp[i] = (char *)malloc(sizeof(char) * (ft_strlen(path) + 1))) == NULL)
    return (NULL);
  tmp[i] = ft_strcpy(tmp[i], path);
  tmp[i + 1] = NULL;
  return (tmp);
}

char	**ft_add_env(const char *line, const char *value, char **env_bis)
{
  char	**tmp;
  char	*path;
  int		len;

  len = ft_strlen(line) + ft_strlen(value);
  if ((path = (char *)malloc(sizeof(char) * len + 1)) == NULL)
    return (NULL);
  ft_strcpy(path, line);
  ft_strcat(path, "=");
  ft_strcat(path, value);
  tmp = ft_cpy_env(env_bis, 1, path);
  free(path);
  ft_free(env_bis, 1);
  return (tmp);
}
