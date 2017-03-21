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

	str = ft_oldpwd_or_add(env_bis, NULL, 0);
	tmp = ft_egal(env_bis, 0);
	*env_bis = ft_setenv("OLDPWD", str, *env_bis);
	free(str);
	*env_bis = ft_setenv("PWD", tmp, *env_bis);
	free(tmp);
}

char	*ft_egal(char ***env_bis, int flag)
{
	char	*str;
	int		index;
	int		i;

	if (flag == 0)
		index = ft_get_env("OLDPWD", *env_bis);
	else
		index = ft_get_env("HOME", *env_bis);
	if ((str = (char *)malloc(sizeof(char) * (ft_strlen(env_bis[0][index]) + 1))) == NULL)
		return (NULL);
	i = 0;
	while (env_bis[0][index][i] != '=' && env_bis[0][index][i])
		i++;
	i++;
    ft_at_strcpy(str, env_bis[0][index], i);
	return (str);
}
