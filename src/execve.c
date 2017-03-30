/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 13:19:07 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/29 16:20:15 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static  char    *ft_get_path_try(char *av, char *dir)
{
	char	*path;
	int		len_max;

	len_max = ((ft_strlen(av) + 1) + (ft_strlen(dir) + 1));
	if ((path = (char *)malloc(sizeof(*path) * len_max)) == NULL)
		return (NULL);
	ft_strcpy(path, dir);
	ft_strcat(path, "/");
	ft_strcat(path, av);
	if (access(path, X_OK) == 0)
		return (path);
	free(path);
	path = NULL;
	return (path);
}

static  char    *ft_get_path(char *av, char **env)
{
	char	*path;
	char	*tmp;
	char	**str;
	int		i;

	path = NULL;
	if ((i = ft_getenv("PATH", env)) >= 0)
		path = env[i] + 5;
	if (path != NULL && (str = ft_strsplit(path, ':')) != NULL)
	{
		i = -1;
		while (str[++i])
			if ((tmp = ft_get_path_try(av, str[i])) != NULL)
			{
				ft_free(str, 1);
				return (tmp);
			}
	}
	return (av);
}

static	char	*ft_move_to_index_bis(char *line)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if ((str = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1))) == NULL)
		return (NULL);
	while (line[i] != '-' && line[i])
		i++;
	i += 2;
	if (line[i] == ' ')
		i++;
	if (line[i] == '"' || line[i] == '\'')
		ft_at_strcpy(str, line, i);
	else
	{
		while ((line[i] != ' ' || line[i] != '\t') && line[i])
			str[j++] = line[i++];
		str[j] = '\0';
	}
	return (str);
}

static  char    *ft_move_to_index(char  *line, char **av)
{
	char    *str;
	int     i;
	int     j;

	if ((str = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1))) == NULL)
		return (NULL);
	if (ft_strcmp(av[1], "-i") == 0)
		str = ft_move_to_index_bis(line);
	else
	{
		i = 0;
		j = 0;
		while (line[i] != ' ' && line[i])
			i++;
		i++;
		while (line[i])
			str[j++] = line[i++];
		str[j] = '\0';
	}
	return (str);
}

int		ft_cmd_execve(char **av, char **env_bis, char *line, int index)
{
	char	**tab;
    char    **tmp;
	char    *str;
	int     ret;

	ret = 0;
	str = (index >= 1) ? ft_move_to_index(line, av) : NULL;
    tmp = (av[1] && ft_strcmp(av[1], "-i") == 0) ? NULL : env_bis;
	if ((execve(ft_get_path(av[index], env_bis), av + index, tmp)) == -1)
	{
		tab = (index >= 1) ? ft_parse_av(str, av, env_bis, &ret) :
			ft_parse_av(line, av, env_bis, &ret);
		if (str)
			free(str);
		if (tab)
			return (ft_error_env_2(tab, index, ret));
	}
	return (1);
}
