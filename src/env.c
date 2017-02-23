/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:24:08 by stvalett          #+#    #+#             */
/*   Updated: 2017/02/23 16:40:15 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_unsetenv_bis(char *str)
{
	int 	i;
	char	*tmp;

	if ((tmp = (char *)malloc(sizeof(char) * ft_strlen(str) + 1)) == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	**ft_unsetenv(const char *line, const char *value, char ***env)
{
	char	*path;
	char	**tmp;
	int		len;
	int		i;
	int		count;
	int		j;

	len = (ft_strlen(line) + 1) + (ft_strlen(line) + 1);
	if ((path = (char *)malloc(sizeof(*path) * len)) == NULL)
		return (NULL);
	ft_strcpy(path, line);
	ft_strcat(path, "=");
	ft_strcat(path, value);
	i = 0;
	j = 0;
	count = ft_count_env(*env);
	if ((tmp = (char **)malloc(sizeof(char *) * count + 1)) == NULL)
		return (NULL);
	while (i < count)
	{
		if ((ft_strncmp(*env[i], path, ft_strlen(path))) == 0)
			;
		else
		{
			tmp[j] = ft_unsetenv_bis(*env[i]);
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	*env = tmp;
	ft_free(tmp, 0);
	return (*env);
}

char	**ft_setenv(const char *line, const char *value, char **env)
{
  char	*path;
  int	len;
  int	i;
  int	count;

  len = (ft_strlen(line) + 1) + (ft_strlen(value) + 1);
  if ((path = (char *)malloc(sizeof(*path) * len)) == NULL)
    return (NULL);
  ft_strcpy(path, line);
  ft_strcat(path, "=");
  ft_strcat(path, value);
  i = ft_get_env(path, env);
  if (i >= 0)
    env[i] = path;
  else
  {
	  count = ft_count_env(env);
	  env[count - 1] = path;
  }
  return (env);
}

int	ft_get_env(char *line, char **env)
{
  int 	i;
  char	*path;

  if ((path = (char *)malloc(sizeof(*path) * ft_strlen(line) + 1)) == NULL)
    return (-1);
  //ft_strcat(path, "=");
  i = 0;
  while (line[i])
  {
	  if (line[i] == '=')
		  ;
	  else
		  path[i] = line[i];
	  i++;
  }
  i = 0;
  while (env[i])
  {
    if ((ft_strnstr(env[i], path, ft_strlen(path))) != 0)
    {
      free(path);
      return (i);
    }
    i++;
  }
  free(path);
  return (-1);
}
