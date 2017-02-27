/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 10:38:53 by stvalett          #+#    #+#             */
/*   Updated: 2017/02/27 17:48:00 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*char	*ft_str_without_cara(char *tmp)*/
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
