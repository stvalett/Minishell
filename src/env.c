/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:24:08 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/09 14:50:43 by stvalett         ###   ########.fr       */
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

char	**ft_unsetenv(const char *line, const char *value, char **env_bis)
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
    count = ft_count_env(env_bis);
    if ((tmp = (char **)malloc(sizeof(char *) * count + 1)) == NULL)
        return (NULL);
    while (i < count)
    {
        if ((ft_strncmp(env_bis[i], path, ft_strlen(path))) == 0)
            ;
        else
        {
            tmp[j] = ft_unsetenv_bis(env_bis[i]);
            j++;
        }
        i++;
    }
    tmp[j] = NULL;
    free(path);
    ft_free(env_bis, 0);
    return (tmp);
}

char	**ft_setenv(const char *line, const char *value, char **env_bis)
{
    char	*path;
    char    **tmp;
    int	    len;
    int     j;
    int	    i;

    len = ft_strlen(line) + ft_strlen(value);
    if ((path = (char *)malloc(sizeof(char) * len )) == NULL)
        return (NULL);
    ft_strcpy(path, line);
    ft_strcat(path, "=");
    ft_strcat(path, value);
    i = ft_get_env(path, env_bis);
    if (i >= 0)
    {
        if ((tmp = (char **)malloc(sizeof(char *) * ft_count_env(env_bis) + 1)) == NULL)
            return (NULL);
        j = 0;
        while (env_bis[j])
        {
            if (j == i)
            {
                if ((tmp[j] = (char *)malloc(sizeof(char) * (ft_strlen(path) + 1))) == NULL)
                    return (NULL);
                ft_strcpy(tmp[j], path);
            }
            else
            {
                if ((tmp[j] = (char *)malloc(sizeof(char) * (ft_strlen(env_bis[j]) + 1))) == NULL)
                    return (NULL);
                ft_strcpy(tmp[j], env_bis[j]);
            }
            j++;
        }
        tmp[j] = NULL;
        ft_free(env_bis, 0);
        free(path);
        return (tmp);
    }
    free(path);
    return (ft_add_env(line, value, env_bis));
}

int	ft_get_env(char *line, char **env_bis)
{
    int 	i;
    int		j;
    char	*path;
    char	*tmp;

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
    i = -1;
    while (env_bis[++i])
    {
        tmp = ft_get_env_bis(env_bis[i]);
        if ((ft_strcmp(tmp, path)) == 0)
        {
            free(path);
            free(tmp);
            return (i);
        }
		if (tmp)
			free(tmp);
    }
    free(path);
    return (-1);
}
