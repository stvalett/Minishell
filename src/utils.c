/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 10:38:53 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/03 12:01:39 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_env_without_bis(char **env_bis, int index)
{
	char	*tmp;
	int	i;
	int	j;

	if ((tmp = (char*)malloc(sizeof(char) * ft_strlen(env_bis[index]) + 1)) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (env_bis[index][i] != '=')
		i++;
	i++;
	while (env_bis[index][i])
	{
		tmp[j] = env_bis[index][i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

void	ft_env_without(char **av, char **env_bis)
{
	char	*tmp;
	int		i;
	int		index;

	i = 0;
	index = 0;
	while (av[++i])
	{
		tmp = NULL;
		if (ft_print_one_dollar(av[i]) == 1)
			ft_putstr(av[i]);
		if ((ft_strchr(av[i], '$')) == NULL)
			ft_putstr(av[i]);
		if ((ft_strchr(av[i], '$')) != NULL)
		{
			tmp = ft_strcpy_cara(av[i]);
			/*	if ((ft_strcmp(tmp, "$")) == 0)
				{
				free(tmp);
				tmp = NULL;
				}
				else*/
			index = ft_get_env(tmp, env_bis);
		}
		if (index >= 0 && tmp != NULL)
		{
			tmp = ft_env_without_bis(env_bis, index);
			ft_putstr(tmp);
			free(tmp);
		}
		ft_putchar(' ');
	}
}

char	*ft_strcpy_cara(char *av)
{
	int 	i;
	int	j;
	char	*tmp;

	if ((tmp = (char *)malloc(sizeof(char) * ft_strlen(av) + 1)) == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (av[++i])
	{
		if (av[i] != '$')
		{
			tmp[j] = av[i];
			j++;
		}
	}
	tmp[j] = '\0';
	return (tmp);
}

char	**ft_cpy_env(char **env_bis, int len, char *path)
{
	char		**tmp;
	int			count;
	int			i;
	static int	len_bis = 0;

	len_bis += len;
	count = ft_count_env(env_bis);
	if ((tmp = (char **)malloc(sizeof(char *) * (count + len_bis + 1))) == NULL)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		if ((tmp[i] = (char *)malloc(sizeof(char) * (ft_strlen(env_bis[i]) + 1))) == NULL)
			return (NULL);
		tmp[i] = ft_strcpy(tmp[i], env_bis[i]);
	}
	if (path == NULL)
		tmp[i] = NULL;
	else
	{
		if ((tmp[i] = (char *)malloc(sizeof(char) * (ft_strlen(path) + 1))) == NULL)
			return (NULL);
		tmp[i] = ft_strcpy(tmp[i], path);
		tmp[i + 1] = NULL;
	}
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
	ft_free(env_bis, 0);
	return (tmp);
}
