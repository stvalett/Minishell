/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 11:17:44 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/10 12:39:40 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char *ft_get_env_bis(char *av)
{
    char	*tmp;
    int		i;
    int		j;

    if ((tmp = (char *)malloc(sizeof(char) * ft_strlen(av) + 1)) == NULL)
        return (NULL);
    i = 0;
    if (av[i] == '=')
    {
        while (av[i] == '=')
            i++;
        i++;
    }
    j = 0;
    while (av[i] != '=')
    {
        tmp[j] = av[i];
        j++;
        i++;
    }
    tmp[j] = '\0';
    return (tmp);
}

static int	ft_getenv2(char **env_bis, char *path, int *i)
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

static char	*ft_unsetenv_bis(char *str)
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

char	**ft_unsetenv(const char *line, const char *value, char **env_bis)
{
    char	*path;
    char	**tmp;
    int		i;
    int		count;
    int		j;

	path = ft_getpath(line, value);
    count = ft_count_env(env_bis);
    if ((tmp = (char **)malloc(sizeof(char *) * count + 1)) == NULL)
        return (NULL);
    i = -1;
    j = 0;
    while (++i < count)
        if ((ft_strncmp(env_bis[i], path, ft_strlen(path))) == 0)
            ;
        else
        {
            tmp[j] = ft_unsetenv_bis(env_bis[i]);
            j++;
        }
    tmp[j] = NULL;
    free(path);
    ft_free(env_bis, 0);
    return (tmp);
}

int	ft_get_env(char *line, char **env_bis)
{
    int 	i;
    int		j;
    char	*path;

    if ((path = (char *)malloc(sizeof(*path) * ft_strlen(line) + 1)) == NULL)
        return (-1);
    i = -1;
    j = 0;
    while (line[++i])
    {
        if (line[i] == '=')
            break;
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
