/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 11:17:44 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/31 11:08:18 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	char	*ft_get_env_bis(char *av)
{
	char	*tmp;
	int		i;
	int		j;

	if ((tmp = (char *)malloc(sizeof(char) * ft_strlen(av) + 1)) == NULL)
		return (NULL);
	i = 0;
	if (av[i] == '=')
	{
		while (av[i] == '=' && av[i])
			i++;
		i++;
	}
	j = 0;
	while (av[i] != '=' && av[i])
		tmp[j++] = av[i++];
	tmp[j] = '\0';
	return (tmp);
}

static	int		ft_getenv2(char **env_bis, char *path, int *i)
{
	char	*tmp;

	*i = 0;
	while (env_bis[*i])
	{
		tmp = ft_get_env_bis(env_bis[*i]);
		if ((ft_strcmp(tmp, path)) == 0)
		{
			free(path);
			free(tmp);
			return (*i);
		}
		if (tmp)
			free(tmp);
		*i = *i + 1;
	}
	return (-1);
}

int				ft_getenv(char *line, char **env_bis)
{
	int		i;
	int		j;
	char	*path;

	if ((path = (char *)malloc(sizeof(*path) * ft_strlen(line) + 1)) == NULL)
		return (-1);
	i = -1;
	j = 0;
	while (line[++i])
	{
		if (line[i] == '=')
			break ;
		else
			path[j] = line[i];
		j++;
	}
	path[j] = '\0';
	if (ft_getenv2(env_bis, path, &i) == -1)
	{
		free(path);
		return (-1);
	}
	else
		return (i);
}

int				ft_tool_parse_env(char **av, char **cpy_env)
{
	char	*str;
	char	**tab_tmp;
	int		flag;

	flag = 0;
	str = ft_strtrim2(av[1], '"', '\'');
	if ((tab_tmp = (char **)malloc(sizeof(char *) * 3)) == NULL)
		exit(1);
	tab_tmp[0] = ft_strdup("");
	tab_tmp[1] = ft_strdup(str);
	tab_tmp[2] = NULL;
	free(str);
	flag = 1;
	if (ft_is_here(av[1], '=', 1) == 1 && av[1][1] == '$')
		return (ft_parse_env1(tab_tmp, cpy_env, flag));
	else
	{
		if (ft_is_here(av[1], '=', 1) == 1)
			return (ft_parse_env2(tab_tmp, cpy_env, flag));
	}
	return (ft_free(cpy_env, 0));
}

void			ft_print_env(char **env_bis, int flag)
{
	int	i;

	i = 0;
	if (flag == 1)
		i = 1;
	while (env_bis[i])
	{
		if (flag == 1)
		{
			ft_putstr(env_bis[i]);
			ft_putchar(' ');
		}
		else
			ft_putendl(env_bis[i]);
		i++;
	}
	if (flag == 1)
		ft_putchar('\n');
}
