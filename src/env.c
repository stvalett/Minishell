/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:24:08 by stvalett          #+#    #+#             */
/*   Updated: 2017/02/28 10:24:47 by stvalett         ###   ########.fr       */
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

char	**ft_unsetenv(const char *line, const char *value, char **env)
{
	char	*path;
	char	**tmp;
	int		len;
	int		i;
	int		count;
	int		j;

	len = ft_strlen(line) + ft_strlen(line);
	if ((path = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	ft_strcpy(path, line);
	ft_strcat(path, "=");
	ft_strcat(path, value);
	i = 0;
	j = 0;
	count = ft_count_env(env);
	ft_putendl(line);
	sleep(2);
	if ((tmp = (char **)malloc(sizeof(char *) * count + 1)) == NULL)
		return (NULL);
	while (i < count)
	{
		if ((ft_strncmp(env[i], path, ft_strlen(path))) == 0)
			;
		else
		{
			tmp[j] = ft_unsetenv_bis(env[i]);
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	ft_free(env, 1);
	return (tmp);
}

char	**ft_setenv(const char *line, const char *value, char **env_bis)
{
	char	*path;
	int	len;
	int	i;

	len = (ft_strlen(line) + 1) + (ft_strlen(value) + 1);
	if ((path = (char *)malloc(sizeof(char) * len)) == NULL)
		return (NULL);
	ft_strcpy(path, line);
	ft_strcat(path, "=");
	ft_strcat(path, value);
	i = ft_get_env(path, env_bis);
	if (i >= 0)
		env_bis[i] = path;
	else
		return (ft_add_env(line, value, env_bis));
	return (env_bis);
}

int	ft_get_env(char *line, char **env)
{
	int 	i;
	char	*path;

	if ((path = (char *)malloc(sizeof(*path) * ft_strlen(line) + 1)) == NULL)
		return (-1);
	//ft_strcat(path, "=");
	i = -1;
	while (line[++i])
		if (line[i] != '=')
			path[i] = line[i];
	i = -1;
	while (env[++i])
		if ((ft_strncmp(env[i], path, ft_strlen(path))) == 0)
		{
			free(path);
			return (i);
		}
	free(path);
	return (-1);
}
