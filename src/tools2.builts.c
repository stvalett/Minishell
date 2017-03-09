/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.builts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 09:44:39 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/09 14:58:37 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_switch_pwd(char ***env_bis)
{
	char	*str;
	char	*tmp;

	str = ft_oldpwd(env_bis);
	tmp = ft_egal(env_bis, 0);
	*env_bis = ft_setenv("OLDPWD", str, *env_bis);
	free(str);
	*env_bis = ft_setenv("PWD", tmp, *env_bis);
	free(tmp);
}

char    *ft_add_pwd(char ***env_bis, char *av)
{
    int     index;
    int     i;
    int     j;
    char    *tmp;

    index = ft_get_env("PWD", *env_bis);
    if ((tmp = (char *)malloc(sizeof(char)
                    * (ft_strlen(env_bis[0][index]) + ft_strlen(av) + 1))) == NULL)
        return (NULL);
    i = 0;
    while (env_bis[0][index][i] != '=')
        i++;
    i++;
    j = 0;
    while (env_bis[0][index][i])
    {
        tmp[j] = env_bis[0][index][i];
        j++;
        i++;
    }
    tmp[j] = '\0';
    ft_strcat(tmp, "/");
    ft_strcat(tmp, av);
    return (tmp);
}

char	*ft_egal(char ***env_bis, int flag)
{
	char	*str;
	int		index;
	int		i;
	int		j;

	if (flag == 0)
		index = ft_get_env("OLDPWD", *env_bis);
	else
		index = ft_get_env("HOME", *env_bis);
	if ((str = (char *)malloc(sizeof(char) * (ft_strlen(env_bis[0][index]) + 1))) == NULL)
		return (NULL);
	i = 0;
	while (env_bis[0][index][i] != '=')
		i++;
	i++;
	j = 0;
	while (env_bis[0][index][i])
	{
		str[j] = env_bis[0][index][i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}
