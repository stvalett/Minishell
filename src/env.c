/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:24:08 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/30 15:32:03 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	char	**ft_add_env(char *line, char *value, char **env_bis)
{
	char	**tmp;
	char	*path;

	path = ft_getpath(line, value);
	tmp = ft_cpy_env(env_bis, 1, path);
	free(path);
	ft_free(env_bis, 0);
	return (tmp);
}

char			**ft_cpy_env(char **env_bis, int len, char *path)
{
	char		**tmp;
	int			count;
	int			i;
	static int	len_bis;

	len_bis += len;
	count = ft_count_av(env_bis);
	if ((tmp = (char **)malloc(sizeof(char *) * (count + len_bis + 1))) == NULL)
		return (NULL);
	i = -1;
	while (++i < count)
		tmp[i] = ft_strdup(env_bis[i]);
	if (path == NULL)
		tmp[i] = NULL;
	else
	{
		tmp[i] = ft_strdup(path);
		tmp[i + 1] = NULL;
	}
	return (tmp);
}

char			**ft_setenv(const char *line, const char *value, char **env_bis)
{
	char	*path;
	char	**tmp;
	int		j;
	int		index;

	path = ft_getpath(line, value);
	index = ft_getenv(path, env_bis);
	if (index >= 0)
	{
		if ((tmp = (char **)malloc(sizeof(char *)
						* ft_count_av(env_bis) + 1)) == NULL)
			return (NULL);
		j = -1;
		while (env_bis[++j])
			if (j == index)
				tmp[j] = ft_strdup(path);
			else
				tmp[j] = ft_strdup(env_bis[j]);
		tmp[j] = NULL;
		ft_free(env_bis, 0);
		free(path);
		return (tmp);
	}
	free(path);
	return (ft_add_env((char *)line, (char *)value, env_bis));
}

char			**ft_unsetenv(char *line, char *value, char **env_bis)
{
	char	*path;
	char	**tmp;
	int		i;
	int		count;
	int		j;

	path = ft_getpath(line, value);
	count = ft_count_av(env_bis);
	if ((tmp = (char **)malloc(sizeof(char *) * count + 1)) == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < count)
		if ((ft_strncmp(env_bis[i], path, ft_strlen(path))) == 0)
			;
		else
		{
			tmp[j] = ft_strdup(env_bis[i]);
			j++;
		}
	tmp[j] = NULL;
	free(path);
	ft_free(env_bis, 0);
	return (tmp);
}
